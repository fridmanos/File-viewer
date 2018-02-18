#!/bin/bash
#Don't know cmake so here's a simple bash script for compiling
g++ -c Directory.cpp -o Directory.o
g++ -c Functions.cpp -o Functions.o
g++ Functions.o Directory.o Main.cpp -o File-viewer
