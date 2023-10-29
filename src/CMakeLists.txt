target_sources(${PROJECT_NAME}
        PRIVATE
        PluginProcessor.cpp
        PluginEditor.cpp
)

add_subdirectory(state)
add_subdirectory(synth)
add_subdirectory(gui)