#!/bin/bash
g++ -c Directory.cpp -o Directory.o
g++ Main.cpp Directory.o -o File-viewer

