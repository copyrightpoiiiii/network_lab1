# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zhangqi/CLionProjects/network_lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhangqi/CLionProjects/network_lab1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/network_lab1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/network_lab1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/network_lab1.dir/flags.make

CMakeFiles/network_lab1.dir/main.cpp.o: CMakeFiles/network_lab1.dir/flags.make
CMakeFiles/network_lab1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhangqi/CLionProjects/network_lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/network_lab1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/network_lab1.dir/main.cpp.o -c /Users/zhangqi/CLionProjects/network_lab1/main.cpp

CMakeFiles/network_lab1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/network_lab1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhangqi/CLionProjects/network_lab1/main.cpp > CMakeFiles/network_lab1.dir/main.cpp.i

CMakeFiles/network_lab1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/network_lab1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhangqi/CLionProjects/network_lab1/main.cpp -o CMakeFiles/network_lab1.dir/main.cpp.s

CMakeFiles/network_lab1.dir/dealConnect.cpp.o: CMakeFiles/network_lab1.dir/flags.make
CMakeFiles/network_lab1.dir/dealConnect.cpp.o: ../dealConnect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhangqi/CLionProjects/network_lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/network_lab1.dir/dealConnect.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/network_lab1.dir/dealConnect.cpp.o -c /Users/zhangqi/CLionProjects/network_lab1/dealConnect.cpp

CMakeFiles/network_lab1.dir/dealConnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/network_lab1.dir/dealConnect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhangqi/CLionProjects/network_lab1/dealConnect.cpp > CMakeFiles/network_lab1.dir/dealConnect.cpp.i

CMakeFiles/network_lab1.dir/dealConnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/network_lab1.dir/dealConnect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhangqi/CLionProjects/network_lab1/dealConnect.cpp -o CMakeFiles/network_lab1.dir/dealConnect.cpp.s

# Object files for target network_lab1
network_lab1_OBJECTS = \
"CMakeFiles/network_lab1.dir/main.cpp.o" \
"CMakeFiles/network_lab1.dir/dealConnect.cpp.o"

# External object files for target network_lab1
network_lab1_EXTERNAL_OBJECTS =

network_lab1: CMakeFiles/network_lab1.dir/main.cpp.o
network_lab1: CMakeFiles/network_lab1.dir/dealConnect.cpp.o
network_lab1: CMakeFiles/network_lab1.dir/build.make
network_lab1: CMakeFiles/network_lab1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zhangqi/CLionProjects/network_lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable network_lab1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/network_lab1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/network_lab1.dir/build: network_lab1

.PHONY : CMakeFiles/network_lab1.dir/build

CMakeFiles/network_lab1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/network_lab1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/network_lab1.dir/clean

CMakeFiles/network_lab1.dir/depend:
	cd /Users/zhangqi/CLionProjects/network_lab1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhangqi/CLionProjects/network_lab1 /Users/zhangqi/CLionProjects/network_lab1 /Users/zhangqi/CLionProjects/network_lab1/cmake-build-debug /Users/zhangqi/CLionProjects/network_lab1/cmake-build-debug /Users/zhangqi/CLionProjects/network_lab1/cmake-build-debug/CMakeFiles/network_lab1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/network_lab1.dir/depend
