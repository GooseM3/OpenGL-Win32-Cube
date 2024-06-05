@echo off
mkdir build
pushd build
cl /std:c++20 /DDEBUG /Zi /Fe: rot_cube.exe ../main.cpp  Opengl32.lib user32.lib Gdi32.lib
popd
