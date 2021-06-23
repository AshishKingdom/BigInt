@echo off
echo.
echo ---------------------------------
echo        compiling bigint.cpp
echo ---------------------------------
echo.
g++ -c bigint.cpp
echo.
echo ---------------------------------
echo        compiling main.cpp
echo ---------------------------------
echo.
g++ -c main.cpp
echo.
echo ---------------------------------
echo        linking all files
echo ---------------------------------
echo.
g++ main.o bigint.o -o main.exe