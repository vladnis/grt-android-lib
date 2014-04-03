#!/bin/bash

# Build the grt project in libraries of $lib_types for $platforms and copy libraries
# to android folder

check_result ()
{
  if [ $? -eq 0 ]; then
    printf "\n========== Operation succeded! ==========\n\n"
  else
    printf "\n__________ Operation faild! Abording execution ... __________\n\n"
    exit
  fi
}

# Platforms to build for. Can contain armeabi, X86 and local.
platforms=(armeabi)

# Types of libraries to build for. Can be static and shared.
lib_types=(shared)

# The location that the livraries are saved after make
lib_folder=libraries

# Andoid project location
and_proj_dir=../../GRT

# Android GRT location
and_grt_dir=$and_proj_dir/jni/GRTlib

# Precompiled header name
pre_header_name=GRT.h.gch

for platform in ${platforms[*]}
do
  for lib_type in ${lib_types[*]}
  do
    printf "\n========== Building $lib_type library for $platform platform ==========\n\n"
    make $lib_type PLATFORM=$platform
    check_result

    printf "\n========== Cleaning .obj files  ==========\n\n"
    make clean
    check_result

    if [ $platform != "local" ]; then
      printf "\n========== Copying library to android folder  ==========\n\n"
      cp $lib_folder/$platform/* $and_grt_dir/libs/$platform/
      check_result
    fi
  done
done

# Precompile Header files and copy to android folder
printf "\n========== Precompiling header files ==========\n\n"
make precompileHeaders
check_result

printf "\n========== Copying precompiled header to android folder  ==========\n\n"
cp $pre_header_name $and_grt_dir/include/
check_result
