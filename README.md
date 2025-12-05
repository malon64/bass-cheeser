# Bass Cheeser

A custom bass distortion plugin in the making. This initial drop sets up a JUCE-based VST3/Standalone project with a single output gain control so we can verify the toolchain and audio plumbing before adding the fun visuals and distortion stages.

## Prerequisites
- CMake 3.18+
- A C++20 compiler (Clang, GCC, or MSVC)
- JUCE is fetched automatically at configure time (default tag 7.0.11). You can override with `-DJUCE_TAG=...`.
- For VST3 builds, install the VST3 SDK (JUCE will fetch it as part of its dependencies) and ensure your DAW can load local builds.

## Configure and build
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

After building, JUCE will copy the VST3/standalone targets into your system's default plugin folders (depends on platform). Standalone binaries live in `build/BassCheeser_artefacts`.

### Custom VST3 output location
You can direct the VST3 bundle to a specific folder by setting `VST3_OUTPUT_DIR`.
- Via command line: `cmake -S . -B out/build/win -DVST3_OUTPUT_DIR="D:/Plugins/BassCheeser"`
- Via `CMakePresets.json`, add a preset with `cacheVariables`:
  ```json
  {
    "version": 3,
    "configurePresets": [
      {
        "name": "win-release",
        "generator": "Ninja",
        "binaryDir": "out/build/win",
        "cacheVariables": {
          "CMAKE_BUILD_TYPE": "Release",
          "VST3_OUTPUT_DIR": "${sourceDir}/VST3"
        }
      }
    ]
  }
  ```
Then configure/build using that preset: `cmake --preset win-release && cmake --build --preset win-release`.

## Running the standalone app
```bash
./build/BassCheeser_artefacts/Release/Standalone/BassCheeser
```

## Next steps
- Add the distortion core (waveshaping/saturation tuned for bass).
- Craft a bespoke UI (think Dada Life energy) with custom graphics/animations.
- Expose drive, tone, mix, and limiter controls.
- Add automated tests for DSP blocks once they exist (e.g., unit tests on the waveshaper transfer function).
