REM Michael Coughlin
REM hiimmichael.com
REM 2019 

@ECHO OFF

if not "%1"=="am_admin" (powershell start -verb runas '%0' am_admin & exit)

SET /P MyPID=Please enter your PID:

IF "%MyPID%"=="" GOTO Error
  ECHO This %MyPID% PID will terminated
  GOTO End
:Error
  ECHO You did not enter PID
:End

pause

taskkill /PID %MyPID% /t
