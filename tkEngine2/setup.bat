echo on
@rem サンプルの各フォルダにtkEngineへのシンボリックリンクを作成する。
@set CURRENT_DIR=%~dp0

pushd %CURRENT_DIR%
@rem GameTemplateにシンボリックリンクを作成する。
mklink /D .\GameTemplate\tkEngine .\tkEngine
mklink /D .\GameTemplate\tkTools .\tkTools

@call .\Sample\setup.bat

@popd
@echo "セットアップ終了"

@pause