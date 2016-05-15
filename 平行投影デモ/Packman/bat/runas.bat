@echo off
:RUNAS
whoami /PRIV | FIND "SeLoadDriverPrivilege" > NUL
IF not errorlevel 1 GOTO START
ECHO 処理を続行するには管理者権限が必要です。
ECHO 管理者モードで再起動します
START cmd.lnk /K "%0" %~d0 %~p0
exit
:START
CD /D %1\%2
