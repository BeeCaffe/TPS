# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/caffe/clion-2019.1.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/caffe/clion-2019.1.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/caffe/CLionProjects/TPS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/caffe/CLionProjects/TPS/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TPS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TPS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TPS.dir/flags.make

CMakeFiles/TPS.dir/main.cpp.o: CMakeFiles/TPS.dir/flags.make
CMakeFiles/TPS.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/caffe/CLionProjects/TPS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TPS.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TPS.dir/main.cpp.o -c /home/caffe/CLionProjects/TPS/main.cpp

CMakeFiles/TPS.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TPS.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/caffe/CLionProjects/TPS/main.cpp > CMakeFiles/TPS.dir/main.cpp.i

CMakeFiles/TPS.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TPS.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/caffe/CLionProjects/TPS/main.cpp -o CMakeFiles/TPS.dir/main.cpp.s

# Object files for target TPS
TPS_OBJECTS = \
"CMakeFiles/TPS.dir/main.cpp.o"

# External object files for target TPS
TPS_EXTERNAL_OBJECTS =

TPS: CMakeFiles/TPS.dir/main.cpp.o
TPS: CMakeFiles/TPS.dir/build.make
TPS: /usr/local/lib/libopencv_dnn.so.3.4.6
TPS: /usr/local/lib/libopencv_ml.so.3.4.6
TPS: /usr/local/lib/libopencv_objdetect.so.3.4.6
TPS: /usr/local/lib/libopencv_shape.so.3.4.6
TPS: /usr/local/lib/libopencv_stitching.so.3.4.6
TPS: /usr/local/lib/libopencv_superres.so.3.4.6
TPS: /usr/local/lib/libopencv_videostab.so.3.4.6
TPS: /usr/local/lib/libopencv_calib3d.so.3.4.6
TPS: /usr/local/lib/libopencv_features2d.so.3.4.6
TPS: /usr/local/lib/libopencv_flann.so.3.4.6
TPS: /usr/local/lib/libopencv_highgui.so.3.4.6
TPS: /usr/local/lib/libopencv_photo.so.3.4.6
TPS: /usr/local/lib/libopencv_video.so.3.4.6
TPS: /usr/local/lib/libopencv_videoio.so.3.4.6
TPS: /usr/local/lib/libopencv_imgcodecs.so.3.4.6
TPS: /usr/local/lib/libopencv_imgproc.so.3.4.6
TPS: /usr/local/lib/libopencv_core.so.3.4.6
TPS: CMakeFiles/TPS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/caffe/CLionProjects/TPS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TPS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TPS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TPS.dir/build: TPS

.PHONY : CMakeFiles/TPS.dir/build

CMakeFiles/TPS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TPS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TPS.dir/clean

CMakeFiles/TPS.dir/depend:
	cd /home/caffe/CLionProjects/TPS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/caffe/CLionProjects/TPS /home/caffe/CLionProjects/TPS /home/caffe/CLionProjects/TPS/cmake-build-debug /home/caffe/CLionProjects/TPS/cmake-build-debug /home/caffe/CLionProjects/TPS/cmake-build-debug/CMakeFiles/TPS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TPS.dir/depend

