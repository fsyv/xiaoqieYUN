# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src

# Include any dependencies generated for this target.
include message/CMakeFiles/msgIO.dir/depend.make

# Include the progress variables for this target.
include message/CMakeFiles/msgIO.dir/progress.make

# Include the compile flags for this target's objects.
include message/CMakeFiles/msgIO.dir/flags.make

message/CMakeFiles/msgIO.dir/recvMsg.o: message/CMakeFiles/msgIO.dir/flags.make
message/CMakeFiles/msgIO.dir/recvMsg.o: message/recvMsg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object message/CMakeFiles/msgIO.dir/recvMsg.o"
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msgIO.dir/recvMsg.o   -c /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message/recvMsg.c

message/CMakeFiles/msgIO.dir/recvMsg.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msgIO.dir/recvMsg.i"
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message/recvMsg.c > CMakeFiles/msgIO.dir/recvMsg.i

message/CMakeFiles/msgIO.dir/recvMsg.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msgIO.dir/recvMsg.s"
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message/recvMsg.c -o CMakeFiles/msgIO.dir/recvMsg.s

message/CMakeFiles/msgIO.dir/recvMsg.o.requires:

.PHONY : message/CMakeFiles/msgIO.dir/recvMsg.o.requires

message/CMakeFiles/msgIO.dir/recvMsg.o.provides: message/CMakeFiles/msgIO.dir/recvMsg.o.requires
	$(MAKE) -f message/CMakeFiles/msgIO.dir/build.make message/CMakeFiles/msgIO.dir/recvMsg.o.provides.build
.PHONY : message/CMakeFiles/msgIO.dir/recvMsg.o.provides

message/CMakeFiles/msgIO.dir/recvMsg.o.provides.build: message/CMakeFiles/msgIO.dir/recvMsg.o


message/CMakeFiles/msgIO.dir/sendMsg.o: message/CMakeFiles/msgIO.dir/flags.make
message/CMakeFiles/msgIO.dir/sendMsg.o: message/sendMsg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object message/CMakeFiles/msgIO.dir/sendMsg.o"
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msgIO.dir/sendMsg.o   -c /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message/sendMsg.c

message/CMakeFiles/msgIO.dir/sendMsg.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msgIO.dir/sendMsg.i"
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message/sendMsg.c > CMakeFiles/msgIO.dir/sendMsg.i

message/CMakeFiles/msgIO.dir/sendMsg.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msgIO.dir/sendMsg.s"
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message/sendMsg.c -o CMakeFiles/msgIO.dir/sendMsg.s

message/CMakeFiles/msgIO.dir/sendMsg.o.requires:

.PHONY : message/CMakeFiles/msgIO.dir/sendMsg.o.requires

message/CMakeFiles/msgIO.dir/sendMsg.o.provides: message/CMakeFiles/msgIO.dir/sendMsg.o.requires
	$(MAKE) -f message/CMakeFiles/msgIO.dir/build.make message/CMakeFiles/msgIO.dir/sendMsg.o.provides.build
.PHONY : message/CMakeFiles/msgIO.dir/sendMsg.o.provides

message/CMakeFiles/msgIO.dir/sendMsg.o.provides.build: message/CMakeFiles/msgIO.dir/sendMsg.o


# Object files for target msgIO
msgIO_OBJECTS = \
"CMakeFiles/msgIO.dir/recvMsg.o" \
"CMakeFiles/msgIO.dir/sendMsg.o"

# External object files for target msgIO
msgIO_EXTERNAL_OBJECTS =

message/libmsgIO.a: message/CMakeFiles/msgIO.dir/recvMsg.o
message/libmsgIO.a: message/CMakeFiles/msgIO.dir/sendMsg.o
message/libmsgIO.a: message/CMakeFiles/msgIO.dir/build.make
message/libmsgIO.a: message/CMakeFiles/msgIO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libmsgIO.a"
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && $(CMAKE_COMMAND) -P CMakeFiles/msgIO.dir/cmake_clean_target.cmake
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/msgIO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
message/CMakeFiles/msgIO.dir/build: message/libmsgIO.a

.PHONY : message/CMakeFiles/msgIO.dir/build

message/CMakeFiles/msgIO.dir/requires: message/CMakeFiles/msgIO.dir/recvMsg.o.requires
message/CMakeFiles/msgIO.dir/requires: message/CMakeFiles/msgIO.dir/sendMsg.o.requires

.PHONY : message/CMakeFiles/msgIO.dir/requires

message/CMakeFiles/msgIO.dir/clean:
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message && $(CMAKE_COMMAND) -P CMakeFiles/msgIO.dir/cmake_clean.cmake
.PHONY : message/CMakeFiles/msgIO.dir/clean

message/CMakeFiles/msgIO.dir/depend:
	cd /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message /home/liuzheng/YUNPAN/xiaoqieYUN/LinuxServer/src/message/CMakeFiles/msgIO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : message/CMakeFiles/msgIO.dir/depend

