Dropdash For All - Android Installation Guide
=============================================

This package contains the compiled Android libraries for the Dropdash For All mod.
This mod adds drop dash functionality to all characters in Sonic Mania Plus.

IMPORTANT: This mod supports Android 5 (SDK 17) and higher only. Do not use on Android versions lower than 5.

WHAT'S IN THIS PACKAGE
======================
This folder contains native libraries for different Android CPU architectures:
- arm64-v8a/: For 64-bit ARM devices (most modern Android phones)
- armeabi-v7a/: For 32-bit ARM devices (older Android phones)
- x86/: For some Android emulators and rare x86 devices
- x86_64/: For 64-bit x86 Android emulators

INSTALLATION INSTRUCTIONS
========================
1. You need the "DropdashForAll" mod folder (containing mod.ini)
   - If you don't have it, extract it from the Windows package or source code

2. Decompile your Sonic Mania Plus APK file using an APK decompiler tool
   - Tools like APK Editor Studio, Jadx, or Android Studio can be used

3. Locate the "lib" folder in your decompiled APK

4. Copy ALL the folders from "mod_lib" folder of package (arm64-v8a, armeabi-v7a, x86, x86_64)
   into the APK's "lib" folder
   - Each folder should contain a file called "libDropdashForAll.so"

5. Recompile the APK using the same tool you used to decompile it

6. Install the modified APK on your Android device

7. After installation, navigate to your game's "Mods" folder
   - Usually located at: RSDK/V5/Mods
   - Or: RSDK/mania/Mods

8. Copy the "DropdashForAll" folder (containing mod.ini) into the Mods folder

9. Launch the game, go to Mod Options, and enable the "Dropdash For All" mod

TROUBLESHOOTING
---------------
- If the mod doesn't appear in-game, check that you copied both the .so files to the APK and the mod folder to the Mods directory
- Make sure you're using Sonic Mania Plus (not the original Sonic Mania)
- If you get crashes, ensure your Android version is 5.0 or higher
- If the mod doesn't work, check that the mod.ini file is present in the DropdashForAll folder
- Only install the CPU architecture folders that match your device if you're trying to save space:
  * Most modern devices use arm64-v8a
  * Older devices may use armeabi-v7a
 * x86 and x86_64 are mostly for emulators

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
- If the mod doesn't appear in-game, check that you copied both the compiled library file and the mod folder in correct locations
- If you get crashes, ensure your Android version is 5.0 or higher (for Android builds) and clear the cache of the game
- If the mod doesn't work, check that the mod.ini file is present in the DropdashForAll folder

ABOUT THE MOD
=============
This mod enables the drop dash ability for all characters in Sonic Mania Plus:
- Tails, Knuckles, Mighty, and Ray can now perform drop dashes
- Mighty also has a special hammer drop dash when enabled
- All characters now have the same ground mobility as Sonic!

Enjoy your enhanced Sonic Mania Plus experience!
