#!/bin/sh

# This script splits a .hpp file into .h and .cpp files.
# It assumes that the public methods are delcared first, then the priate methods are declared.
# Any include statenebt for a header with the comment "//FWD" after it will get replaced by the forward declared
# version of the header in the newly generated header file.


getClassName()
{
  # This needs to be changed to use the filename rather than any class defintion found within the file.
  className=`sed -rn 's/^class[\t ]?([0-9A-Z_a-z]+)/\1/p' $1`
}

genH() 
{
  getClassName $1
  echo "Generating "$2"$className.h"
  sed -r '
  /\#include.*[/]{2,}FWD/s/.([0-9A-Z_a-z]+)(\.h)./"\1FWD\2"/g
  /^[/]{0,2}\#include.*/{/^\#.*FWD\.h/!d}
  /^\t\{/,/^\t\}/d
  s/[\t ]$//g
  s/(^[\t ]+.*[~A-Z_a-z0-9]+.*\)$)/\1;/g
  ' $1 > "$2"$className.h
}

genCPP() 
{
  getClassName $1
  echo "Generating "$2"$className.cpp"
  sed -r "/\#define/a\\\n\#include \"$className.h\"" $1 |\
  sed -r "
  1,2s/^#.*//g
  \$s/^#.*//g
  /^[/]{2}\#include/d
  /^class[\t ]?$className/,/[\t ]?public:/d
  /private:/,/\};/d
  1,/[^\t ]/{/^$/d}
  s/(^\t[0-9A-Z_a-z]+ )([~A-Z_a-z0-9]+\(.*\).*$)/\1$className::\2/g
  s/^\t([~A-Z_a-z0-9]+\(.*\).*$)/  $className::\1/g
  " > "$2"$className.cpp
}

if [ "$#" -eq 0 ]; then
  echo "Usage: gen_hcpp.sh <source file> <type of file to generate:h/cpp/hcpp(both)> <folder path to write generated files in>"
  exit
elif [ $2 = "h" ]; then
  genH $1 $3
elif [ $2 = "cpp" ]; then
  genCPP $1 $3
elif [ $2 = "hcpp" ]; then
  genH $1 $3
  genCPP $1 $3
fi
