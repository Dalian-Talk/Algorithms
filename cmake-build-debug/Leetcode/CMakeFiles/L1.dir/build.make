# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/keye/CLionProjects/Algorithms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/keye/CLionProjects/Algorithms/cmake-build-debug

# Include any dependencies generated for this target.
include Leetcode/CMakeFiles/L1.dir/depend.make

# Include the progress variables for this target.
include Leetcode/CMakeFiles/L1.dir/progress.make

# Include the compile flags for this target's objects.
include Leetcode/CMakeFiles/L1.dir/flags.make

Leetcode/CMakeFiles/L1.dir/main1.cpp.o: Leetcode/CMakeFiles/L1.dir/flags.make
Leetcode/CMakeFiles/L1.dir/main1.cpp.o: ../Leetcode/main1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/keye/CLionProjects/Algorithms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Leetcode/CMakeFiles/L1.dir/main1.cpp.o"
	cd /Users/keye/CLionProjects/Algorithms/cmake-build-debug/Leetcode && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/L1.dir/main1.cpp.o -c /Users/keye/CLionProjects/Algorithms/Leetcode/main1.cpp

Leetcode/CMakeFiles/L1.dir/main1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/L1.dir/main1.cpp.i"
	cd /Users/keye/CLionProjects/Algorithms/cmake-build-debug/Leetcode && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/keye/CLionProjects/Algorithms/Leetcode/main1.cpp > CMakeFiles/L1.dir/main1.cpp.i

Leetcode/CMakeFiles/L1.dir/main1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/L1.dir/main1.cpp.s"
	cd /Users/keye/CLionProjects/Algorithms/cmake-build-debug/Leetcode && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/keye/CLionProjects/Algorithms/Leetcode/main1.cpp -o CMakeFiles/L1.dir/main1.cpp.s

# Object files for target L1
L1_OBJECTS = \
"CMakeFiles/L1.dir/main1.cpp.o"

# External object files for target L1
L1_EXTERNAL_OBJECTS =

Leetcode/L1: Leetcode/CMakeFiles/L1.dir/main1.cpp.o
Leetcode/L1: Leetcode/CMakeFiles/L1.dir/build.make
Leetcode/L1: Leetcode/CMakeFiles/L1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/keye/CLionProjects/Algorithms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable L1"
	cd /Users/keye/CLionProjects/Algorithms/cmake-build-debug/Leetcode && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/L1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Leetcode/CMakeFiles/L1.dir/build: Leetcode/L1

.PHONY : Leetcode/CMakeFiles/L1.dir/build

Leetcode/CMakeFiles/L1.dir/clean:
	cd /Users/keye/CLionProjects/Algorithms/cmake-build-debug/Leetcode && $(CMAKE_COMMAND) -P CMakeFiles/L1.dir/cmake_clean.cmake
.PHONY : Leetcode/CMakeFiles/L1.dir/clean

Leetcode/CMakeFiles/L1.dir/depend:
	cd /Users/keye/CLionProjects/Algorithms/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/keye/CLionProjects/Algorithms /Users/keye/CLionProjects/Algorithms/Leetcode /Users/keye/CLionProjects/Algorithms/cmake-build-debug /Users/keye/CLionProjects/Algorithms/cmake-build-debug/Leetcode /Users/keye/CLionProjects/Algorithms/cmake-build-debug/Leetcode/CMakeFiles/L1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Leetcode/CMakeFiles/L1.dir/depend

