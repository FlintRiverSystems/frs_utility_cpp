

echo "testing..."

cd unit_tests\build

Release\frs_utility_cpp_tests.exe

set RESULT=%ERRORLEVEL%

cd ..

exit /b %RESULT%

