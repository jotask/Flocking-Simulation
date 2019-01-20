
# Add local repository for FindXXX.cmake modules.
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/flocking_simulation/CMake/" ${CMAKE_MODULE_PATH})

option(FORCE_DOWNLOAD_GLFW "Force linking to a downloaded version of GLFW" ON)
find_package(GLFW)

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

IF(GLFW_FOUND)

    file(GLOB_RECURSE FlockingSimulation_SRC
    "src/*.hpp"
    "src/*.cpp"
    )

    include_directories(../submodules/Horde3D/Horde3D/Bindings/C++)

    include_directories(${GLFW_INCLUDE_DIR})

    include_directories(${GLM_INCLUDE_DIRS})

    include_directories(FlockingSimulation_SRC)

    add_executable(FlockingSimulation WIN32 MACOSX_BUNDLE ${FlockingSimulation_SRC})

    target_link_libraries(FlockingSimulation Horde3D Horde3DUtils ${GLFW_LIBRARIES})

    add_dependencies(FlockingSimulation project_glfw)

    # set the project as console application
    set_target_properties(FlockingSimulation PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(FlockingSimulation PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
    set_target_properties(FlockingSimulation PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
    set_target_properties(FlockingSimulation PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
    set_target_properties(FlockingSimulation PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    set_target_properties(FlockingSimulation PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
    
ENDIF(GLFW_FOUND)


