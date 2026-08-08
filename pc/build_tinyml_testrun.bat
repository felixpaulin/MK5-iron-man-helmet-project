@echo off
setlocal

echo ==========================================
echo JARVIS TinyML Desktop Model Test
echo ==========================================
echo.

REM Move to the pc folder where this script lives
cd /d "%~dp0"

REM Check for MinGW
where mingw32-make >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: mingw32-make was not found.
    echo.
    echo Edge Impulse's official Windows desktop
    echo build requires MinGW-W64.
    echo.
    echo Your normal JARVIS build uses Visual Studio,
    echo so your existing build.bat is unaffected.
    echo.
    pause
    exit /b 1
)

where gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: gcc was not found.
    echo.
    echo Please make sure MinGW-W64 is installed
    echo and available in PATH.
    echo.
    pause
    exit /b 1
)

echo MinGW found.
echo.
echo Building TinyML model test...
echo.

REM Build the Edge Impulse desktop test
mingw32-make ^
    CC=gcc ^
    CXX=g++ ^
    CXXSOURCES=TinyMLModelTest.cpp ^
    -j

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ==========================================
    echo TinyML BUILD FAILED
    echo ==========================================
    echo.
    pause
    exit /b 1
)

echo.
echo ==========================================
echo TinyML BUILD SUCCESSFUL
echo ==========================================
echo.

if exist app.exe (
    echo Running TinyML test...
    echo.
    app.exe
) else if exist build\app.exe (
    echo Running TinyML test...
    echo.
    build\app.exe
) else (
    echo ERROR: Could not find the generated executable.
)

echo.
pause