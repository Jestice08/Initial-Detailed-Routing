# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yi/Utexas/CAD/mycode/CAD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yi/Utexas/CAD/mycode/CAD

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/local/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/yi/Utexas/CAD/mycode/CAD/CMakeFiles /home/yi/Utexas/CAD/mycode/CAD/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/yi/Utexas/CAD/mycode/CAD/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ARouter

# Build rule for target.
ARouter: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ARouter
.PHONY : ARouter

# fast build rule for target.
ARouter/fast:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/build
.PHONY : ARouter/fast

src/db/lefiLayer.o: src/db/lefiLayer.cpp.o

.PHONY : src/db/lefiLayer.o

# target to build an object file
src/db/lefiLayer.cpp.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/db/lefiLayer.cpp.o
.PHONY : src/db/lefiLayer.cpp.o

src/db/lefiLayer.i: src/db/lefiLayer.cpp.i

.PHONY : src/db/lefiLayer.i

# target to preprocess a source file
src/db/lefiLayer.cpp.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/db/lefiLayer.cpp.i
.PHONY : src/db/lefiLayer.cpp.i

src/db/lefiLayer.s: src/db/lefiLayer.cpp.s

.PHONY : src/db/lefiLayer.s

# target to generate assembly for a file
src/db/lefiLayer.cpp.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/db/lefiLayer.cpp.s
.PHONY : src/db/lefiLayer.cpp.s

src/main/main.o: src/main/main.cpp.o

.PHONY : src/main/main.o

# target to build an object file
src/main/main.cpp.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/main/main.cpp.o
.PHONY : src/main/main.cpp.o

src/main/main.i: src/main/main.cpp.i

.PHONY : src/main/main.i

# target to preprocess a source file
src/main/main.cpp.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/main/main.cpp.i
.PHONY : src/main/main.cpp.i

src/main/main.s: src/main/main.cpp.s

.PHONY : src/main/main.s

# target to generate assembly for a file
src/main/main.cpp.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/main/main.cpp.s
.PHONY : src/main/main.cpp.s

src/parser/lefdef/DefDataBase.o: src/parser/lefdef/DefDataBase.cc.o

.PHONY : src/parser/lefdef/DefDataBase.o

# target to build an object file
src/parser/lefdef/DefDataBase.cc.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefDataBase.cc.o
.PHONY : src/parser/lefdef/DefDataBase.cc.o

src/parser/lefdef/DefDataBase.i: src/parser/lefdef/DefDataBase.cc.i

.PHONY : src/parser/lefdef/DefDataBase.i

# target to preprocess a source file
src/parser/lefdef/DefDataBase.cc.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefDataBase.cc.i
.PHONY : src/parser/lefdef/DefDataBase.cc.i

src/parser/lefdef/DefDataBase.s: src/parser/lefdef/DefDataBase.cc.s

.PHONY : src/parser/lefdef/DefDataBase.s

# target to generate assembly for a file
src/parser/lefdef/DefDataBase.cc.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefDataBase.cc.s
.PHONY : src/parser/lefdef/DefDataBase.cc.s

src/parser/lefdef/DefDriver.o: src/parser/lefdef/DefDriver.cc.o

.PHONY : src/parser/lefdef/DefDriver.o

# target to build an object file
src/parser/lefdef/DefDriver.cc.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefDriver.cc.o
.PHONY : src/parser/lefdef/DefDriver.cc.o

src/parser/lefdef/DefDriver.i: src/parser/lefdef/DefDriver.cc.i

.PHONY : src/parser/lefdef/DefDriver.i

# target to preprocess a source file
src/parser/lefdef/DefDriver.cc.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefDriver.cc.i
.PHONY : src/parser/lefdef/DefDriver.cc.i

src/parser/lefdef/DefDriver.s: src/parser/lefdef/DefDriver.cc.s

.PHONY : src/parser/lefdef/DefDriver.s

# target to generate assembly for a file
src/parser/lefdef/DefDriver.cc.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefDriver.cc.s
.PHONY : src/parser/lefdef/DefDriver.cc.s

src/parser/lefdef/DefReader.o: src/parser/lefdef/DefReader.cpp.o

.PHONY : src/parser/lefdef/DefReader.o

# target to build an object file
src/parser/lefdef/DefReader.cpp.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefReader.cpp.o
.PHONY : src/parser/lefdef/DefReader.cpp.o

src/parser/lefdef/DefReader.i: src/parser/lefdef/DefReader.cpp.i

.PHONY : src/parser/lefdef/DefReader.i

# target to preprocess a source file
src/parser/lefdef/DefReader.cpp.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefReader.cpp.i
.PHONY : src/parser/lefdef/DefReader.cpp.i

src/parser/lefdef/DefReader.s: src/parser/lefdef/DefReader.cpp.s

.PHONY : src/parser/lefdef/DefReader.s

# target to generate assembly for a file
src/parser/lefdef/DefReader.cpp.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/DefReader.cpp.s
.PHONY : src/parser/lefdef/DefReader.cpp.s

src/parser/lefdef/LefDataBase.o: src/parser/lefdef/LefDataBase.cc.o

.PHONY : src/parser/lefdef/LefDataBase.o

# target to build an object file
src/parser/lefdef/LefDataBase.cc.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefDataBase.cc.o
.PHONY : src/parser/lefdef/LefDataBase.cc.o

src/parser/lefdef/LefDataBase.i: src/parser/lefdef/LefDataBase.cc.i

.PHONY : src/parser/lefdef/LefDataBase.i

# target to preprocess a source file
src/parser/lefdef/LefDataBase.cc.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefDataBase.cc.i
.PHONY : src/parser/lefdef/LefDataBase.cc.i

src/parser/lefdef/LefDataBase.s: src/parser/lefdef/LefDataBase.cc.s

.PHONY : src/parser/lefdef/LefDataBase.s

# target to generate assembly for a file
src/parser/lefdef/LefDataBase.cc.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefDataBase.cc.s
.PHONY : src/parser/lefdef/LefDataBase.cc.s

src/parser/lefdef/LefDriver.o: src/parser/lefdef/LefDriver.cc.o

.PHONY : src/parser/lefdef/LefDriver.o

# target to build an object file
src/parser/lefdef/LefDriver.cc.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefDriver.cc.o
.PHONY : src/parser/lefdef/LefDriver.cc.o

src/parser/lefdef/LefDriver.i: src/parser/lefdef/LefDriver.cc.i

.PHONY : src/parser/lefdef/LefDriver.i

# target to preprocess a source file
src/parser/lefdef/LefDriver.cc.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefDriver.cc.i
.PHONY : src/parser/lefdef/LefDriver.cc.i

src/parser/lefdef/LefDriver.s: src/parser/lefdef/LefDriver.cc.s

.PHONY : src/parser/lefdef/LefDriver.s

# target to generate assembly for a file
src/parser/lefdef/LefDriver.cc.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefDriver.cc.s
.PHONY : src/parser/lefdef/LefDriver.cc.s

src/parser/lefdef/LefReader.o: src/parser/lefdef/LefReader.cpp.o

.PHONY : src/parser/lefdef/LefReader.o

# target to build an object file
src/parser/lefdef/LefReader.cpp.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefReader.cpp.o
.PHONY : src/parser/lefdef/LefReader.cpp.o

src/parser/lefdef/LefReader.i: src/parser/lefdef/LefReader.cpp.i

.PHONY : src/parser/lefdef/LefReader.i

# target to preprocess a source file
src/parser/lefdef/LefReader.cpp.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefReader.cpp.i
.PHONY : src/parser/lefdef/LefReader.cpp.i

src/parser/lefdef/LefReader.s: src/parser/lefdef/LefReader.cpp.s

.PHONY : src/parser/lefdef/LefReader.s

# target to generate assembly for a file
src/parser/lefdef/LefReader.cpp.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/parser/lefdef/LefReader.cpp.s
.PHONY : src/parser/lefdef/LefReader.cpp.s

src/util/MsgPrinter.o: src/util/MsgPrinter.cpp.o

.PHONY : src/util/MsgPrinter.o

# target to build an object file
src/util/MsgPrinter.cpp.o:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/util/MsgPrinter.cpp.o
.PHONY : src/util/MsgPrinter.cpp.o

src/util/MsgPrinter.i: src/util/MsgPrinter.cpp.i

.PHONY : src/util/MsgPrinter.i

# target to preprocess a source file
src/util/MsgPrinter.cpp.i:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/util/MsgPrinter.cpp.i
.PHONY : src/util/MsgPrinter.cpp.i

src/util/MsgPrinter.s: src/util/MsgPrinter.cpp.s

.PHONY : src/util/MsgPrinter.s

# target to generate assembly for a file
src/util/MsgPrinter.cpp.s:
	$(MAKE) -f CMakeFiles/ARouter.dir/build.make CMakeFiles/ARouter.dir/src/util/MsgPrinter.cpp.s
.PHONY : src/util/MsgPrinter.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... ARouter"
	@echo "... edit_cache"
	@echo "... src/db/lefiLayer.o"
	@echo "... src/db/lefiLayer.i"
	@echo "... src/db/lefiLayer.s"
	@echo "... src/main/main.o"
	@echo "... src/main/main.i"
	@echo "... src/main/main.s"
	@echo "... src/parser/lefdef/DefDataBase.o"
	@echo "... src/parser/lefdef/DefDataBase.i"
	@echo "... src/parser/lefdef/DefDataBase.s"
	@echo "... src/parser/lefdef/DefDriver.o"
	@echo "... src/parser/lefdef/DefDriver.i"
	@echo "... src/parser/lefdef/DefDriver.s"
	@echo "... src/parser/lefdef/DefReader.o"
	@echo "... src/parser/lefdef/DefReader.i"
	@echo "... src/parser/lefdef/DefReader.s"
	@echo "... src/parser/lefdef/LefDataBase.o"
	@echo "... src/parser/lefdef/LefDataBase.i"
	@echo "... src/parser/lefdef/LefDataBase.s"
	@echo "... src/parser/lefdef/LefDriver.o"
	@echo "... src/parser/lefdef/LefDriver.i"
	@echo "... src/parser/lefdef/LefDriver.s"
	@echo "... src/parser/lefdef/LefReader.o"
	@echo "... src/parser/lefdef/LefReader.i"
	@echo "... src/parser/lefdef/LefReader.s"
	@echo "... src/util/MsgPrinter.o"
	@echo "... src/util/MsgPrinter.i"
	@echo "... src/util/MsgPrinter.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

