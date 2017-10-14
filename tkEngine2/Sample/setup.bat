rem サンプルの各フォルダにtkEngineへのシンボリックリンクを作成する。
for /d %%a in (.\*) do (call :makeSymbolicLink "%%a")

goto end
:makeSymbolicLink
if %~1==.\tkEngine goto end_makeSymbolicLink
set CURRENT_DIR=%~dp0
set SAMPLE_FOLDER=%~1
pushd %~1

powershell.exe -Command Start-Process -FilePath "cmd" -ArgumentList "/c","mklink", "/D", "%CURRENT_DIR%\%SAMPLE_FOLDER%\tkEngine","%CURRENT_DIR%\tkEngine" -Verb Runas

popd
:end_makeSymbolicLink
exit /b

:end
pause