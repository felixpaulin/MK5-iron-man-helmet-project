@echo off

echo ==========================================
echo MK5 TinyML Desktop Application
echo Build Script
echo ==========================================
echo.

REM Move to this script's folder
cd /d "%~dp0"

REM Load the Visual Studio Build Tools environment
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2026\BuildTools\Common7\Tools\VsDevCmd.bat"

echo.
echo Compiling...
echo.

cl /EHsc /std:c++17 ^
TinyMLListener.cpp ^
SerialPort.cpp ^
AudioCapture.cpp ^
/Fe:TinyMLListener.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ==========================================
    echo Build Successful!
    echo ==========================================
) else (
    echo.
    echo ==========================================
    echo Build Failed!
    echo ==========================================
)

pause