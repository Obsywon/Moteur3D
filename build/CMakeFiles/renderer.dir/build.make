# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/build

# Include any dependencies generated for this target.
include CMakeFiles/renderer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/renderer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/renderer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/renderer.dir/flags.make

CMakeFiles/renderer.dir/main.cpp.o: CMakeFiles/renderer.dir/flags.make
CMakeFiles/renderer.dir/main.cpp.o: ../main.cpp
CMakeFiles/renderer.dir/main.cpp.o: CMakeFiles/renderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/renderer.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/renderer.dir/main.cpp.o -MF CMakeFiles/renderer.dir/main.cpp.o.d -o CMakeFiles/renderer.dir/main.cpp.o -c /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/main.cpp

CMakeFiles/renderer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/renderer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/main.cpp > CMakeFiles/renderer.dir/main.cpp.i

CMakeFiles/renderer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/renderer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/main.cpp -o CMakeFiles/renderer.dir/main.cpp.s

# Object files for target renderer
renderer_OBJECTS = \
"CMakeFiles/renderer.dir/main.cpp.o"

# External object files for target renderer
renderer_EXTERNAL_OBJECTS =

renderer: CMakeFiles/renderer.dir/main.cpp.o
renderer: CMakeFiles/renderer.dir/build.make
renderer: CMakeFiles/renderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable renderer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/renderer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/renderer.dir/build: renderer
.PHONY : CMakeFiles/renderer.dir/build

CMakeFiles/renderer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/renderer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/renderer.dir/clean

CMakeFiles/renderer.dir/depend:
	cd /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/build /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/build /home/guy/Documents/Semestre_8/Moteur_3D/project_renderer/build/CMakeFiles/renderer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/renderer.dir/depend

