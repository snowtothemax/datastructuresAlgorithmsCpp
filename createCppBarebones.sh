#!/bin/bash
if [ -e $1 ]; then
  echo "File $1 already exists!"
else
  echo "#include <iostream>" >> $1
  echo "#include <string>" >> $1
  echo "#include <array>" >> $1
  echo >> $1
  echo "int main()" >> $1
  echo "{" >> $1
  echo >> $1
  echo "}" >> $1
fi
