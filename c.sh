#!/bin/sh
name=$1
gcc -o ${name} ${name}.c && ./${name}

