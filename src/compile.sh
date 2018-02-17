#!/bin/bash
#Don't know cmake so here's a simple bash script for compialation
g++ -c Directory.cpp -o Directory.o
g++ Main.cpp Directory.o -o File-viewer

