cmake_minimum_required(VERSION 3.18)
project(BassCheeser VERSION 0.1.0)

# Optionally allow the user to set JUCE tag externally
if(NOT DEFINED JUCE_TAG)
    set(JUCE_TAG 7.0.11)
endif()

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG ${JUCE_TAG}
)

FetchContent_MakeAvailable(JUCE)

set(VST3_OUTPUT_DIR
    "${CMAKE_SOURCE_DIR}/VST3"
    CACHE PATH "Directory where the built VST3 will be copied"
)

juce_add_plugin(
    BassCheeser
    COMPANY_NAME "BassCheeser"
    BUNDLE_ID com.basscheeser.plugin
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE BsCh
    PLUGIN_CODE Bchz
    FORMATS VST3 Standalone
    PRODUCT_NAME "BassCheeser"
    VST3_COPY_DIR "${VST3_OUTPUT_DIR}"
)

if (NOT MSVC)
    target_compile_options(BassCheeser PRIVATE -Wno-format-truncation)
endif()

target_sources(BassCheeser
    PRIVATE
        source/PluginProcessor.cpp
        source/PluginProcessor.h
        source/PluginEditor.cpp
        source/PluginEditor.h
)

target_compile_definitions(BassCheeser
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

juce_generate_juce_header(BassCheeser)

target_link_libraries(BassCheeser
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_gui_basics
        juce::juce_gui_extra
)
