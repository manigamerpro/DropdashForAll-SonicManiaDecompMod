@echo off
title DropdashForAll Compiler

echo.
echo ====================================
echo Welcome to DropdashForAll Compiler
echo ====================================
echo This tool helps you build the mod for Windows or Android
echo NOTE: You need to have CMake, Ninja (or Visual Studio), and Android NDK installed
echo.

:menu
echo.
echo ================================
echo MAIN MENU - Choose an option:
echo ================================
echo 1. Build for Windows (Creates Windows DLL in Builds\Windows folder)
echo 2. Build for Android (Creates Android libraries in Builds\Android folder)
echo 3. Clean Windows Build (Removes Windows build files and cache)
echo 4. Clean Android Build (Removes Android build files and cache)
echo 5. Exit this program
echo.
set /p choice="Enter your choice number (1-5): "

if "%choice%"=="1" goto windows
if "%choice%"=="2" goto android
if "%choice%"=="3" goto clean_windows
if "%choice%"=="4" goto clean_android
if "%choice%"=="5" goto exit
echo Invalid choice, please try again.
goto menu

:windows
echo.
echo ====================================
echo BUILDING FOR WINDOWS
echo ====================================
echo This will create a Windows DLL file for the mod
echo Please wait, this may take a few minutes...
setlocal ENABLEDELAYEDEXPANSION
set BUILD_DIR=%~dp0\jni\build

echo Cleaning previous build files...
if exist "!BUILD_DIR!" rmdir /s /q "!BUILD_DIR!"
mkdir "!BUILD_DIR!"

echo Configuring build with CMake...
cmake -S "%~dp0\jni" -B "!BUILD_DIR!" -G Ninja -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 (
    echo Ninja generator not found, trying with default generator...
    cmake -S "%~dp0\jni" -B "!BUILD_DIR!" -DCMAKE_BUILD_TYPE=Release
    if errorlevel 1 (
        echo CMake configuration failed with all generators
        echo Make sure you have CMake installed properly
        pause
        exit /b 1
    )
)

REM Build the target
echo Building the mod DLL...
cmake --build "!BUILD_DIR!" --config Release
if errorlevel 1 (
    echo Build failed
    echo Check that you have the required build tools installed
    pause
    exit /b 1
)

echo Windows compilation completed successfully!

if not exist "%~dp0\Builds\Windows" mkdir "%~dp0\Builds\Windows" >nul 2>&1

set "DLL_SRC="
for /f "usebackq" %%f in (`dir /b /s "%~dp0\jni\build\*.dll" 2^>nul`) do (
    if "%%f" neq "" (
        set "DLL_SRC=%%f"
        goto :found_dll
    )
)

:found_dll
if defined DLL_SRC (
    for %%f in ("!DLL_SRC!") do (
        set "DLL_NAME=%%~nxf"
        if "!DLL_NAME:~0,3!" == "lib" (
            set "NEW_NAME=!DLL_NAME:~3!"
            copy "!DLL_SRC!" "%~dp0\Builds\Windows\!NEW_NAME!" >nul
            echo DLL copied to Builds/Windows\!NEW_NAME!
        ) else (
            copy "!DLL_SRC!" "%~dp0\Builds\Windows\!DLL_NAME!" >nul
            echo DLL copied to Builds/Windows\!DLL_NAME!
        )
    )
) else (
    echo Warning: No DLL found to copy
)

echo.
echo Windows build complete! Find your file in: Builds\Windows folder
pause
endlocal
goto menu

:clean_windows
echo.
echo ====================================
echo CLEANING WINDOWS BUILD FILES
echo ====================================
echo Removing all Windows build files and cache...
if exist "%~dp0\jni\build" rmdir /s /q "%~dp0\jni\build" >nul 2>&1
if exist "%~dp0\jni\CMakeCache.txt" del /f /q "%~dp0\jni\CMakeCache.txt" >nul 2>&1
if exist "%~dp0\jni\CMakeFiles" rmdir /s /q "%~dp0\jni\CMakeFiles" >nul 2>&1
if exist "%~dp0\Builds\Windows" rmdir /s /q "%~dp0\Builds\Windows" >nul 2>&1
echo Windows build files cleaned successfully!
echo.
pause
goto menu

:clean_android
echo.
echo ====================================
echo CLEANING ANDROID BUILD FILES
echo ====================================
echo Removing all Android build files and cache...
if exist "%~dp0\obj" rmdir /s /q "%~dp0\obj"
if exist "%~dp0\libs" rmdir /s /q "%~dp0\libs"
if exist "%~dp0\Builds\Android" rmdir /s /q "%~dp0\Builds\Android" >nul 2>&1
echo Android build files cleaned successfully!
echo.
pause
goto menu

:android
echo.
echo ====================================
echo BUILDING FOR ANDROID
echo ====================================
echo This will create Android libraries for the mod
echo Please wait, this may take several minutes...
cd /d "%~dp0"

echo Cleaning previous build files...
if exist "obj" rmdir /s /q "obj"
if exist "libs" rmdir /s /q "libs"

cd jni
echo Building with Android NDK...
call ndk-build
if errorlevel 1 (
    echo Android build failed
    echo Make sure you have Android NDK installed and configured properly
    pause
    exit /b 1
)
echo Android compilation completed successfully!

if not exist "%~dp0\Builds\Android" mkdir "%~dp0\Builds\Android" >nul 2>&1

if exist "%~dp0\libs" (
    xcopy /e /i /y "%~dp0\libs" "%~dp0\Builds\Android" >nul
    echo Android libraries copied to Builds/Android
) else (
    echo Warning: No Android libs found to copy
)

echo.
echo Android build complete! Find your files in: Builds\Android folder
pause
goto menu

:exit
echo.
echo Exiting...
exit /b 0