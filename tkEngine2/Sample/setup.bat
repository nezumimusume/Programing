@rem サンプルの各フォルダにtkEngineへのシンボリックリンクを作成する。
@set CURRENT_DIR=%~dp0
@pushd %CURRENT_DIR%
@for /d %%a in (.\*) do (call :makeSymbolicLink "%%a")

@goto end
:makeSymbolicLink
@if %~1==.\tkEngine goto end_makeSymbolicLink
@set SAMPLE_FOLDER=%~1
@pushd %~1

mklink /D %CURRENT_DIR%\%SAMPLE_FOLDER%\tkEngine %CURRENT_DIR%\..\tkEngine
mklink /D %CURRENT_DIR%\%SAMPLE_FOLDER%\tkTools %CURRENT_DIR%\..\tkTools

@popd
:end_makeSymbolicLink
@exit /b

:end
@popd
