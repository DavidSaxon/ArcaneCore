#!/bin/bash

make && valgrind --leak-check=yes --suppressions=tools/valgrind.supp  ./build/linux_x86/tests --single_proc
