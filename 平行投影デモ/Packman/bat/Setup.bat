call runas.bat

rem presetshaderをシンボリックリンク
SET TK_ENGINE_DIR=..\..\tkEngine
mklink /D ..\Assets\presetshader %TK_ENGINE_DIR%\presetShader

pause 