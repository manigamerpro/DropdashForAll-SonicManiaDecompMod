Dropdash For All - Mod Building & Installation Guide

This package contains the source code for the Dropdash For All mod, which adds drop dash functionality to all characters in Sonic Mania Plus.

ABOUT THE MOD
This mod enables the drop dash ability for all characters in Sonic Mania Plus:
- Tails, Knuckles, Mighty, and Ray can now perform drop dashes
- Mighty also has a special hammer drop dash when enabled
- All characters now have the same ground mobility as Sonic!

GETTING THE SOURCE CODE
This package contains all necessary source files to build the mod for both Windows and Android:
- jni/: Contains the main source code files (dllmain.c, Player.h, ModConfig.h)
- DropdashForAll/: Contains the mod configuration file (mod.ini)
- Builds/: Where compiled files will be placed after building
- DropdashForAll_CompileScript.bat: Script to build the mod

PREREQUISITES
Before building this mod, you need to set up the GameAPI:

IMPORTANT: GameAPI Setup
------------------------
The GameAPI is required for building this mod but you must obtain it separately from the official RSDK Modding sources.

1. Download the GameAPI from the official RSDK Modding repository
2. Extract the GameAPI folder from the downloaded archive
3. Place the GameAPI folder in the following location:
   DropdashForAll_SourceCode\jni\

Your folder structure should look like this when done correctly:
DropdashForAll_SourceCode\jni\GameAPI\C\GameAPI\Game.c
DropdashForAll_SourceCode\jni\GameAPI\C\GameAPI\Game.h
(And other GameAPI files...)

BUILDING THE MOD
----------------
1. Make sure you have CMake, Ninja (or Visual Studio), and Android NDK installed on your computer
2. Double-click on "DropdashForAll_CompileScript.bat" to run the build script
3. Choose an option from the menu:
   - Option 1: Build for Windows (creates Windows DLL in Builds\Windows folder)
   - Option 2: Build for Android (creates Android libraries in Builds\Android folder)
   - Option 3: Clean Windows Build (removes Windows build files and cache)
   - Option 4: Clean Android Build (removes Android build files and cache)
   - Option 5: Exit this program
4. After building, find your compiled files in the Builds\Windows or Builds\Android folder

WHAT'S BUILT
Windows Build:
- Creates a DropdashForAll.dll file in Builds\Windows
- This is the compiled mod library for Windows

Android Build:
- Creates libDropdashForAll.so files in Builds\Android for different architectures:
  * arm64-v8a: For 64-bit ARM devices (most modern Android phones)
  * armeabi-v7a: For 32-bit ARM devices (older Android phones)
  * x86: For some Android emulators and rare x86 devices
  * x86_64: For 64-bit x86 Android emulators

INSTALLATION INSTRUCTIONS

Windows Installation:
---------------------
1. Build the mod for Windows using the compile script
2. You should have a "DropdashForAll" folder containing mod.ini (this is essential for the mod to work)
3. Copy the entire "DropdashForAll" folder to your game's "Mods" folder
4. Copy the compiled "DropdashForAll.dll" file from Builds\Windows folder and place it inside the "DropdashForAll" folder which you copied to game's Mods folder (next to mod.ini)
5. Enable the mod and enjoy! You can also configure the mod from the modSettings.ini which you can find in game's mod folder next to mod.ini too!

Android Installation:
---------------------
Note: This mod supports Android 5 (SDK 17) and higher only. Do not use on Android versions lower than 5.

1. Build the mod for Android using the compile script
2. Decompile your Sonic Mania Plus APK file using an APK decompiler tool
   - Tools like APK Editor Studio, Jadx, or Android Studio can be used
3. Locate the "lib" folder in your decompiled APK
4. Copy ALL the architecture folders from Builds\Android\lib\ to your APK's "lib" folder
   - Each folder should contain a file called "libDropdashForAll.so"
5. Recompile the APK using the same tool you used to decompile it
6. Install the modified APK on your Android device
7. After installation, navigate to your game's "Mods" folder
   - Usually located at: RSDK/V5/Mods
   - Or: RSDK/mania/Mods
8. Copy the "DropdashForAll" folder (containing mod.ini) into the Mods folder
9. Launch the game, go to Mod Options, and enable the "DropdashForAll" mod

CONFIGURATION
=============
After first run, a modSettings.ini file will be created in the mod folder.
You can edit this file to enable/disable dropdash for specific characters:
- EnableDropdashTails
- EnableDropdashKnuckles
- EnableDropdashMighty
- EnableDropdashRay
- MightyHammerDash

TROUBLESHOOTING
---------------
- If you get "GameAPI not found" errors, make sure you placed the GameAPI folder in the correct location
- Make sure all required build tools are installed and in your system PATH
- For Windows builds, ensure CMake and Ninja/Visual Studio are properly installed
- For Android builds, ensure Android NDK is properly installed and configured
- If the mod doesn't appear in-game, check that you copied both the compiled library file and the mod folder in correct locations
- If you get crashes, ensure your Android version is 5.0 or higher (for Android builds) and clear the cache of the game
- If the mod doesn't work, check that the mod.ini file is present in the DropdashForAll folder

Linux Support:
--------------
Linux is not officially supported. You will need to compile for Linux yourself.

Note: The GameAPI is required for building this mod but you must obtain it separately from the official RSDK Modding sources.
