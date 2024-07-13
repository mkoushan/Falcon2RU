set(PROJECT_SOURCES
    main.cpp
)

add_executable(Falcon2RU
    ${PROJECT_SOURCES}
)

target_include_directories(Falcon2RU PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(Falcon2RU PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
