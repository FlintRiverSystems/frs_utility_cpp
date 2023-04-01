
echo "building library ..."

echo FRSTPSRC: %FRSTPSRC%

mkdir build
cd build
cmake -A x64 ..
cmake --build . --config Release

set RESULT=%ERRORLEVEL%

cd ..

exit /b %RESULT%
