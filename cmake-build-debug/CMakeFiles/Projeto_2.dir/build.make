# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /private/var/folders/np/271w924s727ckx1rk9r2bxrc0000gn/T/AppTranslocation/7AE59F29-7DDF-4AD5-839E-A1B06AC9B899/d/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /private/var/folders/np/271w924s727ckx1rk9r2bxrc0000gn/T/AppTranslocation/7AE59F29-7DDF-4AD5-839E-A1B06AC9B899/d/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bernardosousa/CLionProjects/Projeto_AED_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Projeto_2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Projeto_2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Projeto_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Projeto_2.dir/flags.make

CMakeFiles/Projeto_2.dir/main.cpp.o: CMakeFiles/Projeto_2.dir/flags.make
CMakeFiles/Projeto_2.dir/main.cpp.o: /Users/bernardosousa/CLionProjects/Projeto_AED_2/main.cpp
CMakeFiles/Projeto_2.dir/main.cpp.o: CMakeFiles/Projeto_2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Projeto_2.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projeto_2.dir/main.cpp.o -MF CMakeFiles/Projeto_2.dir/main.cpp.o.d -o CMakeFiles/Projeto_2.dir/main.cpp.o -c /Users/bernardosousa/CLionProjects/Projeto_AED_2/main.cpp

CMakeFiles/Projeto_2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto_2.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bernardosousa/CLionProjects/Projeto_AED_2/main.cpp > CMakeFiles/Projeto_2.dir/main.cpp.i

CMakeFiles/Projeto_2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto_2.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bernardosousa/CLionProjects/Projeto_AED_2/main.cpp -o CMakeFiles/Projeto_2.dir/main.cpp.s

CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o: CMakeFiles/Projeto_2.dir/flags.make
CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o: /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/LoadingFunctions.cpp
CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o: CMakeFiles/Projeto_2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o -MF CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o.d -o CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o -c /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/LoadingFunctions.cpp

CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/LoadingFunctions.cpp > CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.i

CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/LoadingFunctions.cpp -o CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.s

CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o: CMakeFiles/Projeto_2.dir/flags.make
CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o: /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Airport.cpp
CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o: CMakeFiles/Projeto_2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o -MF CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o.d -o CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o -c /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Airport.cpp

CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Airport.cpp > CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.i

CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Airport.cpp -o CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.s

CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o: CMakeFiles/Projeto_2.dir/flags.make
CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o: /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Logic.cpp
CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o: CMakeFiles/Projeto_2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o -MF CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o.d -o CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o -c /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Logic.cpp

CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Logic.cpp > CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.i

CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Logic.cpp -o CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.s

CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o: CMakeFiles/Projeto_2.dir/flags.make
CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o: /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Airline.cpp
CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o: CMakeFiles/Projeto_2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o -MF CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o.d -o CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o -c /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Airline.cpp

CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Airline.cpp > CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.i

CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bernardosousa/CLionProjects/Projeto_AED_2/Logic/Airline.cpp -o CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.s

CMakeFiles/Projeto_2.dir/UI/UI.cpp.o: CMakeFiles/Projeto_2.dir/flags.make
CMakeFiles/Projeto_2.dir/UI/UI.cpp.o: /Users/bernardosousa/CLionProjects/Projeto_AED_2/UI/UI.cpp
CMakeFiles/Projeto_2.dir/UI/UI.cpp.o: CMakeFiles/Projeto_2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Projeto_2.dir/UI/UI.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projeto_2.dir/UI/UI.cpp.o -MF CMakeFiles/Projeto_2.dir/UI/UI.cpp.o.d -o CMakeFiles/Projeto_2.dir/UI/UI.cpp.o -c /Users/bernardosousa/CLionProjects/Projeto_AED_2/UI/UI.cpp

CMakeFiles/Projeto_2.dir/UI/UI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto_2.dir/UI/UI.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bernardosousa/CLionProjects/Projeto_AED_2/UI/UI.cpp > CMakeFiles/Projeto_2.dir/UI/UI.cpp.i

CMakeFiles/Projeto_2.dir/UI/UI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto_2.dir/UI/UI.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bernardosousa/CLionProjects/Projeto_AED_2/UI/UI.cpp -o CMakeFiles/Projeto_2.dir/UI/UI.cpp.s

# Object files for target Projeto_2
Projeto_2_OBJECTS = \
"CMakeFiles/Projeto_2.dir/main.cpp.o" \
"CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o" \
"CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o" \
"CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o" \
"CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o" \
"CMakeFiles/Projeto_2.dir/UI/UI.cpp.o"

# External object files for target Projeto_2
Projeto_2_EXTERNAL_OBJECTS =

Projeto_2: CMakeFiles/Projeto_2.dir/main.cpp.o
Projeto_2: CMakeFiles/Projeto_2.dir/Logic/LoadingFunctions.cpp.o
Projeto_2: CMakeFiles/Projeto_2.dir/Logic/Airport.cpp.o
Projeto_2: CMakeFiles/Projeto_2.dir/Logic/Logic.cpp.o
Projeto_2: CMakeFiles/Projeto_2.dir/Logic/Airline.cpp.o
Projeto_2: CMakeFiles/Projeto_2.dir/UI/UI.cpp.o
Projeto_2: CMakeFiles/Projeto_2.dir/build.make
Projeto_2: CMakeFiles/Projeto_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Projeto_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Projeto_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Projeto_2.dir/build: Projeto_2
.PHONY : CMakeFiles/Projeto_2.dir/build

CMakeFiles/Projeto_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Projeto_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Projeto_2.dir/clean

CMakeFiles/Projeto_2.dir/depend:
	cd /Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bernardosousa/CLionProjects/Projeto_AED_2 /Users/bernardosousa/CLionProjects/Projeto_AED_2 /Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug /Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug /Users/bernardosousa/CLionProjects/Projeto_AED_2/cmake-build-debug/CMakeFiles/Projeto_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Projeto_2.dir/depend

