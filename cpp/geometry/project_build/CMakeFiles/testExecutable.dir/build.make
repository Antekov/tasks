# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "M:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "M:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\antek\source\repos\geometry

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\antek\source\repos\geometry\project_build

# Include any dependencies generated for this target.
include CMakeFiles/testExecutable.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testExecutable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testExecutable.dir/flags.make

CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.obj: CMakeFiles/testExecutable.dir/flags.make
CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.obj: CMakeFiles/testExecutable.dir/includes_CXX.rsp
CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.obj: ../tests/geometry_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\antek\source\repos\geometry\project_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.obj"
	M:\mingw-w64\i686-8.1.0-win32-dwarf-rt_v6-rev0\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\testExecutable.dir\tests\geometry_test.cpp.obj -c C:\Users\antek\source\repos\geometry\tests\geometry_test.cpp

CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.i"
	M:\mingw-w64\i686-8.1.0-win32-dwarf-rt_v6-rev0\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\antek\source\repos\geometry\tests\geometry_test.cpp > CMakeFiles\testExecutable.dir\tests\geometry_test.cpp.i

CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.s"
	M:\mingw-w64\i686-8.1.0-win32-dwarf-rt_v6-rev0\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\antek\source\repos\geometry\tests\geometry_test.cpp -o CMakeFiles\testExecutable.dir\tests\geometry_test.cpp.s

# Object files for target testExecutable
testExecutable_OBJECTS = \
"CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.obj"

# External object files for target testExecutable
testExecutable_EXTERNAL_OBJECTS =

testExecutable.exe: CMakeFiles/testExecutable.dir/tests/geometry_test.cpp.obj
testExecutable.exe: CMakeFiles/testExecutable.dir/build.make
testExecutable.exe: CMakeFiles/testExecutable.dir/linklibs.rsp
testExecutable.exe: CMakeFiles/testExecutable.dir/objects1.rsp
testExecutable.exe: CMakeFiles/testExecutable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\antek\source\repos\geometry\project_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testExecutable.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\testExecutable.dir\link.txt --verbose=$(VERBOSE)
	"M:\Program Files\CMake\bin\cmake.exe" -D TEST_TARGET=testExecutable -D TEST_EXECUTABLE=C:/Users/antek/source/repos/geometry/project_build/testExecutable.exe -D TEST_EXECUTOR= -D TEST_WORKING_DIR=C:/Users/antek/source/repos/geometry/project_build -D TEST_SPEC= -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_LIST=testExecutable_TESTS -D CTEST_FILE=C:/Users/antek/source/repos/geometry/project_build/testExecutable_tests-b858cb2.cmake -P "C:/Program Files (x86)/Catch2/lib/cmake/Catch2/CatchAddTests.cmake"

# Rule to build all files generated by this target.
CMakeFiles/testExecutable.dir/build: testExecutable.exe

.PHONY : CMakeFiles/testExecutable.dir/build

CMakeFiles/testExecutable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\testExecutable.dir\cmake_clean.cmake
.PHONY : CMakeFiles/testExecutable.dir/clean

CMakeFiles/testExecutable.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\antek\source\repos\geometry C:\Users\antek\source\repos\geometry C:\Users\antek\source\repos\geometry\project_build C:\Users\antek\source\repos\geometry\project_build C:\Users\antek\source\repos\geometry\project_build\CMakeFiles\testExecutable.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testExecutable.dir/depend

