# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/syjgin/projects/helloUrho/Source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/syjgin/projects/helloUrho/build-Source-Desktop-Default

# Include any dependencies generated for this target.
include CMakeFiles/disconnect.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/disconnect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/disconnect.dir/flags.make

CMakeFiles/disconnect.dir/mainApp.cpp.o: CMakeFiles/disconnect.dir/flags.make
CMakeFiles/disconnect.dir/mainApp.cpp.o: /home/syjgin/projects/helloUrho/Source/mainApp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/syjgin/projects/helloUrho/build-Source-Desktop-Default/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/disconnect.dir/mainApp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/disconnect.dir/mainApp.cpp.o -c /home/syjgin/projects/helloUrho/Source/mainApp.cpp

CMakeFiles/disconnect.dir/mainApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/disconnect.dir/mainApp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/syjgin/projects/helloUrho/Source/mainApp.cpp > CMakeFiles/disconnect.dir/mainApp.cpp.i

CMakeFiles/disconnect.dir/mainApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/disconnect.dir/mainApp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/syjgin/projects/helloUrho/Source/mainApp.cpp -o CMakeFiles/disconnect.dir/mainApp.cpp.s

CMakeFiles/disconnect.dir/mainApp.cpp.o.requires:
.PHONY : CMakeFiles/disconnect.dir/mainApp.cpp.o.requires

CMakeFiles/disconnect.dir/mainApp.cpp.o.provides: CMakeFiles/disconnect.dir/mainApp.cpp.o.requires
	$(MAKE) -f CMakeFiles/disconnect.dir/build.make CMakeFiles/disconnect.dir/mainApp.cpp.o.provides.build
.PHONY : CMakeFiles/disconnect.dir/mainApp.cpp.o.provides

CMakeFiles/disconnect.dir/mainApp.cpp.o.provides.build: CMakeFiles/disconnect.dir/mainApp.cpp.o

# Object files for target disconnect
disconnect_OBJECTS = \
"CMakeFiles/disconnect.dir/mainApp.cpp.o"

# External object files for target disconnect
disconnect_EXTERNAL_OBJECTS =

/home/syjgin/projects/helloUrho/Bin/disconnect: CMakeFiles/disconnect.dir/mainApp.cpp.o
/home/syjgin/projects/helloUrho/Bin/disconnect: CMakeFiles/disconnect.dir/build.make
/home/syjgin/projects/helloUrho/Bin/disconnect: /home/syjgin/projects/Urho3D-1.32/Lib/libUrho3D.a
/home/syjgin/projects/helloUrho/Bin/disconnect: CMakeFiles/disconnect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/syjgin/projects/helloUrho/Bin/disconnect"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/disconnect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/disconnect.dir/build: /home/syjgin/projects/helloUrho/Bin/disconnect
.PHONY : CMakeFiles/disconnect.dir/build

CMakeFiles/disconnect.dir/requires: CMakeFiles/disconnect.dir/mainApp.cpp.o.requires
.PHONY : CMakeFiles/disconnect.dir/requires

CMakeFiles/disconnect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/disconnect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/disconnect.dir/clean

CMakeFiles/disconnect.dir/depend:
	cd /home/syjgin/projects/helloUrho/build-Source-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/syjgin/projects/helloUrho/Source /home/syjgin/projects/helloUrho/Source /home/syjgin/projects/helloUrho/build-Source-Desktop-Default /home/syjgin/projects/helloUrho/build-Source-Desktop-Default /home/syjgin/projects/helloUrho/build-Source-Desktop-Default/CMakeFiles/disconnect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/disconnect.dir/depend

