echo on
@rem サンプルの各フォルダにtkEngineへのシンボリックリンクを作成する。
@set CURRENT_DIR=%~dp0

pushd %CURRENT_DIR%
@rem GameTemplateにシンボリックリンクを作成する。
mklink /D %CURRENT_DIR%\GameTemplate\tkEngine %CURRENT_DIR%\tkEngine
mklink /D %CURRENT_DIR%\GameTemplate\tkTools %CURRENT_DIR%\tkTools

@call .\Sample\setup.bat

@popd
@echo "セットアップ終了"

@pause