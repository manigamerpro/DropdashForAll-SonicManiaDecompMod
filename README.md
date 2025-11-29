# Dropdash For All - Sonic Mania Decompilation Mod

[![License](https://img.shields.io/badge/license-Custom-orange.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Sonic%20Mania%20Plus-orange.svg)]()
[![Version](https://img.shields.io/badge/version-1.0-brightgreen.svg)]()
[![Gamebanana](https://img.shields.io/badge/Gamebanana-Page-orange.svg)](https://gamebanana.com/mods/636552)

> A mod that adds drop dash functionality to all characters in Sonic Mania Plus, making gameplay more consistent across all playable characters.

## 🎮 About the Mod

This mod enables the drop dash ability for all characters in Sonic Mania Plus:
- Tails, Knuckles, Mighty, and Ray can now perform drop dashes
- Mighty also has a special hammer drop dash when enabled
- All characters now have the same ground mobility as Sonic!

## ✨ Features

- **Universal Drop Dash**: All characters can perform the drop dash move by holding down and jump buttons after jumping!
- **Configurable**: Enable/disable dropdash for specific characters
- **Cross-Platform**: Works on both Windows and Android
- **Sonic Mania Decompilation**: Compatible with the decompilation of the game

## 📋 Prerequisites

Before building this mod, you need to set up the GameAPI:

### GameAPI Setup
The GameAPI is required for building this mod but you must obtain it separately from the official RSDK Modding sources.

1. Download the GameAPI from the official RSDK Modding repository
2. Extract the GameAPI folder from the downloaded archive
3. Place the GameAPI folder in the following location:
   `DropdashForAll_SourceCode\jni\`

Your folder structure should look like this when done correctly:
```
DropdashForAll_SourceCode\jni\GameAPI\C\GameAPI\Game.c
DropdashForAll_SourceCode\jni\GameAPI\C\GameAPI\Game.h
(And other GameAPI files...)
```

## 🛠️ Building the Mod

### Requirements
- CMake
- Ninja (or Visual Studio)
- Android NDK (for Android builds)

### Build Process
1. Make sure you have all required tools installed
2. Double-click on `DropdashForAll_CompileScript.bat` to run the build script
3. Choose an option from the menu:
   - Option 1: Build for Windows (creates Windows DLL in Builds\Windows folder)
   - Option 2: Build for Android (creates Android libraries in Builds\Android folder)
   - Option 3: Clean Windows Build (removes Windows build files and cache)
   - Option 4: Clean Android Build (removes Android build files and cache)
   - Option 5: Exit this program
4. After building, find your compiled files in the Builds\Windows or Builds\Android folder

## 📦 What's Built

### Windows Build:
- Creates a `DropdashForAll.dll` file in Builds\Windows
- This is the compiled mod library for Windows

### Android Build:
- Creates `libDropdashForAll.so` files in Builds\Android for different architectures:
  * `arm64-v8a`: For 64-bit ARM devices (most modern Android phones)
 * `armeabi-v7a`: For 32-bit ARM devices (older Android phones)
  * `x86`: For some Android emulators and rare x86 devices
 * `x86_64`: For 64-bit x86 Android emulators

## 🚀 Installation

### Windows Installation:
1. Build the mod for Windows using the compile script
2. You should have a "DropdashForAll" folder containing mod.ini (this is essential for the mod to work)
3. Copy the entire "DropdashForAll" folder to your game's "Mods" folder
4. Copy the compiled "DropdashForAll.dll" file from Builds\Windows folder and place it inside the "DropdashForAll" folder which you copied to game's Mods folder (next to mod.ini)
5. Enable the mod and enjoy! You can also configure the mod from the modSettings.ini which you can find in game's mod folder next to mod.ini too!

### Android Installation:
> ⚠️ Note: This mod supports Android 5 (SDK 17) and higher only. Do not use on Android versions lower than 5.

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

## ⚙️ Configuration

After first run, a `modSettings.ini` file will be created in the mod folder.
You can edit this file to enable/disable dropdash for specific characters:
- `EnableDropdashTails`
- `EnableDropdashKnuckles`
- `EnableDropdashMighty`
- `EnableDropdashRay`
- `MightyHammerDash`

## 📝 Usage Permissions

This project is free to use for personal purposes. If you wish to:
- Use this mod as a base for your own mod
- Include any part of this code in your own project
- Create derivative works based on this mod

You must:
1. Ask for permission first by contacting the me from the Gamebanana page of the mod
2. Keep your derivative project open source
3. Give appropriate credit to this project

## 🐛 Troubleshooting

- If you get "GameAPI not found" errors, make sure you placed the GameAPI folder in the correct location
- Make sure all required build tools are installed and in your system PATH
- For Windows builds, ensure CMake and Ninja/Visual Studio are properly installed
- For Android builds, ensure Android NDK is properly installed and configured
- If the mod doesn't appear in-game, check that you copied both the compiled library file and the mod folder in correct locations
- If you get crashes, ensure your Android version is 5.0 or higher (for Android builds) and clear the cache of the game
- If the mod doesn't work, check that the mod.ini file is present in the DropdashForAll folder

## 🤝 Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests for bug fixes or improvements.

## 🙏 Acknowledgements

- Thanks to the RSDK Modding community for the GameAPI and Decompilation of the game
- Sonic Mania Plus for being an amazing game to mod
- The modding community that made this possible
