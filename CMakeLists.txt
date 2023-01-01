cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 90)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)


project(gl_loader VERSION 1.0)

#########################
# Directory definitions #
#########################
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/lib/glfw)
set(GL3W_DIR ${CMAKE_SOURCE_DIR}/lib/gl3w)
set(GL3W_GENERATE_DIR ${CMAKE_BINARY_DIR}/lib/gl3w)


###############
# Dependecies #
###############
find_package( OpenGL REQUIRED )
find_package( Python COMPONENTS Interpreter ) #Needed for gl3w download script


###################
#  GLFW and GL3W  #
###################

#Stop GLFW from generating docs, tests and examples
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

#Adding GLFW and GL3W sources to be built
add_subdirectory( ${GLFW_DIR} )
add_subdirectory( ${GL3W_DIR} )

#Handling Python and gl3w download
if(NOT Python_Interpreter_FOUND)
	message(FATAL_ERROR "Python could not be found! The compilation can not proceed without a Python interpreter! (gl3w will be missing)")
endif()

if (WIN32)
	#Apparently on windows despite having python3 installed it would not recognize python3 as a command, so only python should be run.
	message("Successfully found Python. Running download script for gl3w.")
	execute_process(COMMAND python gl3w_gen.py --root ${GL3W_GENERATE_DIR} WORKING_DIRECTORY ${GL3W_GENERATE_DIR})
#On linux the command does matter, thus it is tested which version to use.
elseif(${Python_VERSION} GREATER_EQUAL 3.0)
	message("Successfully found Python3. Running download script for gl3w.")
	execute_process(COMMAND python3 gl3w_gen.py --root ${GL3W_GENERATE_DIR} WORKING_DIRECTORY ${GL3W_GENERATE_DIR})
elseif(${Python_VERSION} LESS 3.0)
	message("Successfully found Python2. Running download script for gl3w.")
	execute_process(COMMAND python gl3w_gen.py --root ${GL3W_GENERATE_DIR} WORKING_DIRECTORY ${GL3W_GENERATE_DIR})
endif()


#######################
# Include directories #
#######################

include_directories( ${GLFW_DIR}/include )
include_directories( ${GL3W_GENERATE_DIR}/include )


###################
# Main executable #
###################

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
     	OpenGL::OpenGL
		glfw
		gl3w
)

