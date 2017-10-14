@echo off
@rem サンプルの各フォルダにtkEngineへのシンボリックリンクを作成する。
@setlocal
@set CURRENT_DIR=%~dp0

pushd %CURRENT_DIR%
@rem GameTemplateにシンボリックリンクを作成する。
@mklink /D %CURRENT_DIR%\GameTemplate\tkEngine %CURRENT_DIR%\tkEngine
@mklink /D %CURRENT_DIR%\GameTemplate\tkTools %CURRENT_DIR%\tkTools

@call .\Sample\setup.bat

@rem maxScriptをコピー
@copy %CURRENT_DIR%tkTools\3dsMaxScripts\tkExporter.ms "c:\Program Files\Autodesk\3ds Max 2015\scripts\"
@copy %CURRENT_DIR%tkTools\3dsMaxScripts\tkExporter.ms "c:\Program Files\Autodesk\3ds Max 2016\scripts\"
@copy %CURRENT_DIR%tkTools\3dsMaxScripts\tkExporter.ms "c:\Program Files\Autodesk\3ds Max 2017\scripts\"



@popd
@echo セットアップ終了

@pause