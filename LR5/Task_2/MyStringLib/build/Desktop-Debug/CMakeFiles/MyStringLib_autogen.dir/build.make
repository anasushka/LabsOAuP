# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib/build/Desktop-Debug

# Utility rule file for MyStringLib_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/MyStringLib_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyStringLib_autogen.dir/progress.make

CMakeFiles/MyStringLib_autogen: MyStringLib_autogen/timestamp

MyStringLib_autogen/timestamp: /usr/lib/qt6/libexec/moc
MyStringLib_autogen/timestamp: CMakeFiles/MyStringLib_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target MyStringLib"
	/usr/bin/cmake -E cmake_autogen /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib/build/Desktop-Debug/CMakeFiles/MyStringLib_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib/build/Desktop-Debug/MyStringLib_autogen/timestamp

MyStringLib_autogen: CMakeFiles/MyStringLib_autogen
MyStringLib_autogen: MyStringLib_autogen/timestamp
MyStringLib_autogen: CMakeFiles/MyStringLib_autogen.dir/build.make
.PHONY : MyStringLib_autogen

# Rule to build all files generated by this target.
CMakeFiles/MyStringLib_autogen.dir/build: MyStringLib_autogen
.PHONY : CMakeFiles/MyStringLib_autogen.dir/build

CMakeFiles/MyStringLib_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyStringLib_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyStringLib_autogen.dir/clean

CMakeFiles/MyStringLib_autogen.dir/depend:
	cd /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib/build/Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib/build/Desktop-Debug /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib/build/Desktop-Debug /home/anastacia/Documents/OAuP/LR5/Task_2/MyStringLib/build/Desktop-Debug/CMakeFiles/MyStringLib_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyStringLib_autogen.dir/depend

