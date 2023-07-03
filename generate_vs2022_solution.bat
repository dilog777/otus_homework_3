@echo OFF
rd /q /s build
mkdir build
cd build
cmake ..
