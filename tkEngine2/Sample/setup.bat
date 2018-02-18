@rem サンプルの各フォルダにtkEngineへのシンボリックリンクを作成する。
@setlocal
@set CURRENT_DIR=%~dp0
@pushd "%CURRENT_DIR%

@for /d %%a in (.\*) do (call :makeSymbolicLink "%%a")
@goto end


:makeSymbolicLink
@set SAMPLE_FOLDER=%~1
@pushd %~1

@mklink /D "%CURRENT_DIR%\%SAMPLE_FOLDER%\tkEngine" "%CURRENT_DIR%\..\GameTemplate\tkEngine"
@mklink /D "%CURRENT_DIR%\%SAMPLE_FOLDER%\tkTools" "%CURRENT_DIR%\..\GameTemplate\tkTools"

@exit /b

:end
@popd
