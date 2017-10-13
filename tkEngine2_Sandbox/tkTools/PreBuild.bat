rem Visual studioのビルドのプレビルドステップのバッチファイル。
pushd ..\\Game\\Resource\\
rem ddsファイルをResourceの下にコピー。

mkDir .\\modelData > NUL 2>&1
if errorlevel 1 goto NEXT1
:NEXT1

mkDir .\\sprite > NUL 2>&1
if errorlevel 1 goto NEXT2
:NEXT2
popd
exit 0
