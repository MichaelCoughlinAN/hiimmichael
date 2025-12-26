# Example: Azure AD Sign-in Summary Script via Microsoft Graph API
# Description: Collects Azure AD sign-in logs using Microsoft Graph API and summarizes potential suspicious activity.
# Note: This script uses Microsoft Graph Beta endpoint. Intended for educational and reference use.

[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.SecurityProtocolType]::Tls12

# TODO: Move secrets to environment variables for secure usage
$clientId = "<YOUR_CLIENT_ID>"
$tenantId = "<YOUR_TENANT_ID>"
$clientSecret = "<YOUR_CLIENT_SECRET>" # Don't hardcode this in production

$tokenEndpoint = "https://login.microsoftonline.com/$tenantId/oauth2/v2.0/token"
$graphEndpointBeta = "https://graph.microsoft.com/beta"

$dateRanges = @(
    @{ start = "2025-05-21T00:00:00-05:00"; end = "2025-06-13T00:00:00-05:00" }
)

function Get-NewAccessToken {
    $body = @{
        client_id     = $clientId
        scope         = "https://graph.microsoft.com/.default"
        client_secret = $clientSecret
        grant_type    = "client_credentials"
    }

    try {
        $response = Invoke-RestMethod -Method Post -Uri $tokenEndpoint -ContentType "application/x-www-form-urlencoded" -Body $body -ErrorAction Stop
        Write-Host "Generated new access token"
        return $response.access_token
    } catch {
        Write-Output "Failed to get new access token. Error: $_"
        throw $_
    }
}

function Summarize-SignIns {
    param (
        [array]$signIns,
        [string]$tenantId
    )

    $summary = @{}
    $csvData = @()

    foreach ($signIn in $signIns) {
        $userId     = $signIn.userId
        $userType   = $signIn.userType
        $email      = $signIn.userPrincipalName
        $location   = "$($signIn.location.city),$($signIn.location.countryOrRegion)"
        $device     = "$($signIn.deviceDetail.operatingSystem) - $($signIn.deviceDetail.browser)"

        if (-not $summary.ContainsKey($userId)) {
            $summary[$userId] = @{
                name           = $signIn.userDisplayName
                email          = $email
                userType       = $userType
                logins         = 0
                failures       = 0
                suspicious     = 0
                lastLogin      = $null
            }
        }

        $isSuspicious = $false
        $reasons = @()

        if ($userType -ne "member") {
            $isSuspicious = $true
            $reasons += "GuestUser"
        }

        $summary[$userId].lastLogin = [datetime]::Parse($signIn.createdDateTime)

        if ($signIn.status.errorCode -eq 0) {
            $summary[$userId].logins++
        } else {
            $summary[$userId].failures++
        }

        if ($isSuspicious) {
            $summary[$userId].suspicious++
            $csvData += [PSCustomObject]@{
                SuspicionReasons     = ($reasons -join ", ")
                Date                 = $signIn.createdDateTime
                Name                 = $signIn.userDisplayName
                Email                = $email
                UserType             = $userType
                Location             = $location
                Device               = $device
                IPAddress            = $signIn.IPAddress    
                ConditionalAccess    = $signIn.conditionalAccessStatus
            }
        }
    }

    $csvData | Export-Csv -Path "SignInSummary.csv" -NoTypeInformation
    return $summary
}

function main {
    $accessToken = Get-NewAccessToken
    $jobs = @()

    foreach ($range in $dateRanges) {
        $job = Start-Job -ScriptBlock {
            param($token, $start, $end)

            function Get-AllSignIns {
                param (
                    [string]$accessToken,
                    [string]$startDate,
                    [string]$endDate
                )

                Add-Type -AssemblyName System.Net.Http
                $client = [System.Net.Http.HttpClient]::new()
                $client.DefaultRequestHeaders.Authorization = [System.Net.Http.Headers.AuthenticationHeaderValue]::new("Bearer", $accessToken)

                $url = "https://graph.microsoft.com/beta/auditLogs/signIns?`$filter=createdDateTime ge $startDate and createdDateTime le $endDate"
                $allSignIns = @()

                while ($url) {
                    $maxRetries = 5
                    $retryCount = 0
                    $success = $false

                    while (-not $success -and $retryCount -lt $maxRetries) {
                        try {
                            $response = $client.GetAsync($url).Result

                            if ($response.StatusCode -eq 429) {
                                $retryAfter = $response.Headers.RetryAfter.Delta.TotalSeconds
                                if (-not $retryAfter) { $retryAfter = [math]::Pow(2, $retryCount) }

                                Write-Host "Throttled. Waiting $retryAfter seconds before retrying..."
                                Start-Sleep -Seconds $retryAfter
                                $retryCount++
                                continue
                            }

                            if (-not $response.IsSuccessStatusCode) {
                                Write-Host "Request failed: $($response.StatusCode)"
                                break
                            }

                            $json = ($response.Content.ReadAsStringAsync().Result | ConvertFrom-Json)
                            $allSignIns += $json.value
                            $url = $json.'@odata.nextLink'
                            $success = $true
                        } catch {
                            Write-Host "HTTP error: $_"
                            Start-Sleep -Seconds ([math]::Pow(2, $retryCount))
                            $retryCount++
                        }
                    }

                    if (-not $success) {
                        Write-Host "Failed after $maxRetries attempts."
                        break
                    }
                }

                return $allSignIns
            }

            Get-AllSignIns -accessToken $token -startDate $start -endDate $end
        } -ArgumentList $accessToken, $range.start, $range.end

        $jobs += $job
    }

    Write-Host "Started $($jobs.Count) jobs..."

    $allResults = @()
    foreach ($job in $jobs) {
        $result = Receive-Job -Job $job -Wait
        $allResults += $result
        Remove-Job -Job $job
    }

    Write-Host "All jobs completed. Total sign-ins: $($allResults.Count)"
    $summary = Summarize-SignIns -signIns $allResults -tenantId $tenantId

    $summary | ConvertTo-Json -Depth 5 | Out-File "AllSignIns.json"
    Write-Host "Results saved."
}

main
