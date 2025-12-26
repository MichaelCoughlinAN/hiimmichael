Function GetPowershellReady {
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
    $saved = $global:ErrorActionPreference
    $global:ErrorActionPreference = 'stop'

    $desiredVersion = "3.6.0"
    $installedModules = Get-Module -ListAvailable -Name ExchangeOnlineManagement

    foreach ($module in $installedModules) {
        if ($module.Version -ne $desiredVersion) {
            Write-Host "Uninstalling ExchangeOnlineManagement version $($module.Version)"
            $null = Uninstall-Module -Name $module.Name -RequiredVersion $module.Version -Force -ErrorAction SilentlyContinue
        }
    }

    if (-not ($installedModules | Where-Object { $_.Version -eq $desiredVersion })) {
        Write-Host "Installing ExchangeOnlineManagement version $desiredVersion"
        Install-Module -Name ExchangeOnlineManagement -RequiredVersion $desiredVersion -Force
    }

    Install-PackageProvider NuGet -Confirm:$false -Force -WarningAction SilentlyContinue

    try { Get-InstalledModule -Name MSOnline } catch {
        Write-Host "Installing Microsoft Online module"
        Install-Module -Name MSOnline -Confirm:$false -Force -WarningAction SilentlyContinue
    }

    try { Get-InstalledModule -Name AzureAD } catch {
        Write-Host "Installing Azure AD module"
        Install-Module -Name AzureAD -Confirm:$false -Force -WarningAction SilentlyContinue
    }
}

Function GetAdminUser {
    Write-Host "Click any key, then enter your Exchange credentials"
    $x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyUp,AllowCtrlC")
    $AdminUserName = $env:UserName + "@<REDACTED_DOMAIN>"
    $UserCredential = Get-Credential -Credential $AdminUserName

    try {
        $session = New-PSSession -ConfigurationName Microsoft.Exchange -ConnectionUri <REDACTED_INTERNAL_URI> -Authentication Kerberos -Credential $UserCredential
    } catch {
        Write-Host "Incorrect password" -ForegroundColor Red
        Write-Host -NoNewLine 'Press any key to try again...'
        $null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')
        $UserCredential = GetAdminUser
    }

    return $UserCredential
}

Function Get-NewAccessToken {
    $clientId     = "<REDACTED_CLIENT_ID>"
    $clientSecret = "<REDACTED_CLIENT_SECRET>"
    $tenantId     = "<REDACTED_TENANT_ID>"
    $tokenEndpoint = "https://login.microsoftonline.com/<TENANT_ID>/oauth2/v2.0/token"

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

Function CheckServer {
    Write-Host "Click any key, then enter your Exchange credentials"
    $x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyUp,AllowCtrlC")
    Write-Host "Logging into Exchange Online"
    try {
        $void = Connect-ExchangeOnline -Credential $UserCredential -WarningAction SilentlyContinue -ShowBanner:$False -ErrorAction SilentlyContinue
    } catch {
        Write-Warning "Password was incorrect!"
        Write-Host -NoNewLine 'Press any key to log in again...'
        $null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')
        Main
    }
}

Function destination {
    try {
        $uri = "https://graph.microsoft.com/v1.0/users"
        $accessToken = Get-NewAccessToken

        $headers = @{
            "Authorization" = "Bearer $accessToken"
            "Content-Type"  = "application/json"
        }

        $AllResults = @()

        do {
            $response = Invoke-RestMethod -Uri $uri -Headers $headers -Method Get

            foreach ($user in $response.value) {
                $email = if ($user.mail) { $user.mail } else { $user.userPrincipalName }

                try {
                    Write-Host "`nLooking for $email on Exchange Online" -ForegroundColor Cyan
                    $void = Get-Mailbox -Identity $email -ErrorAction Stop

                    $stats = Get-EXOMailboxStatistics -Identity $email
                    $sizeMB = [math]::Round(($stats.TotalItemSize.ToString().Split("(")[1].Split(" ")[0].Replace(",", "") / 1GB), 2)

                    $mailbox = Get-Mailbox $email
                    $ProhibitSendGB = [math]::Round(($mailbox.ProhibitSendQuota.ToString().Split("(")[1].Split(" ")[0].Replace(",", "") / 1GB), 2)
                    $IssueWarningGB = [math]::Round(($mailbox.IssueWarningQuota.ToString().Split("(")[1].Split(" ")[0].Replace(",", "") / 1GB), 2)

                    $PercentageUsed = [math]::Round(($sizeMB / $ProhibitSendGB * 100), 2)

                    Write-Host "Email: $email"
                    Write-Host "Mailbox Size: $sizeMB GB"
                    Write-Host "Prohibit Send Quota: $ProhibitSendGB GB"
                    Write-Host "Issue Warning Quota: $IssueWarningGB GB"
                    Write-Host "Percent Used: $PercentageUsed%" -ForegroundColor Green

                    $AllResults += [PSCustomObject]@{
                        Email               = $email
                        MailboxSizeGB       = $sizeMB
                        ProhibitSendQuotaGB = $ProhibitSendGB
                        IssueWarningQuotaGB = $IssueWarningGB
                        PercentUsed         = $PercentageUsed
                    }
                } catch {
                    Write-Warning "Mailbox not found for $email"
                }
            }

            $uri = $response.'@odata.nextLink'
        } while ($uri)

        $AllResults | Export-Csv -Path "MailboxStats.csv" -NoTypeInformation
        Write-Host "`nExport complete. Results saved to MailboxStats.csv" -ForegroundColor Yellow
    } catch {
        Write-Error "An error occurred: $_"
    }
}

Function Main {
    GetPowershellReady
    $global:UserCredential = GetAdminUser
    CheckServer
    cls
    destination
}

Main
