#!/bin/sh

rm -f bin/*

for i in `ls src/*.cpp | sed -e 's/src\///g' | sed -e 's/\.cpp//g'`
do
  echo $i
  g++ -Wall -fPIC -g -c src/$i.cpp -o bin/$i.o
done

FILE_LIST=`ls bin/*.o`
g++ -shared -Wl,-soname,inidb.so -o inidb.so $FILE_LIST

#g++ -Wall -shared -fPIC -m32 -o bin/libmyext.so src/libmyext.cpp
