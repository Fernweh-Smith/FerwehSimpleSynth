CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

Project(Fernweh_Simple_Synth VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)



include(cmake/CPM.cmake)

CPMAddPackage(
        NAME JUCE
        VERSION 7.0.7
        GIT_TAG 7.0.7
        GITHUB_REPOSITORY juce-framework/JUCE
)

juce_add_plugin(${PROJECT_NAME}
        COMPANY_NAME Fernweh
        IS_SYNTH YES
        NEEDS_MIDI_INPUT YES
        COPY_PLUGIN_AFTER_BUILD YES
        PLUGIN_MANUFACTURER_CODE FAud
        PLUGIN_CODE FASS
        FORMATS AU VST3 Standalone
        PRODUCT_NAME "Simple Synth"
)
 target_sources(${PROJECT_NAME}
         PRIVATE
         src/PluginEditor.cpp
         src/PluginProcessor.cpp
         src/SimpleSynthSound.cpp
         src/SimpleSynthVoice.cpp
         src/SimpleSynthesiser.cpp
         src/ParameterListener.cpp
         src/PluginParameters.cpp
         src/WaveFunctions.cpp
 )

target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_utils
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)