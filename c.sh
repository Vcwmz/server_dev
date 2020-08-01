#!/bin/sh
#mkdir ${name}
#&&
for file in $(ls *.c)
do
  mv $file ${file%??}
done
#name=$1
#gcc -o ${name} ${name}.c && ./${name}