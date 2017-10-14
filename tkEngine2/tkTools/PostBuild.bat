rem Visual studioのビルドのポストビルドステップのバッチファイル。
pushd ..\\Game\\
rem ddsファイルをResourceの下にコピー。
xcopy /Y /D *.dds .\Resource\*

rem AssetsフォルダからResourceフォルダにごそっとコピー。
rem 画像ファイルとfbxはコピーされないよ！！！
xcopy /Y /D /I /S .\Assets .\Resource /EXCLUDE:..\tkTools\exlcude.txt
popd
