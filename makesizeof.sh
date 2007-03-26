#!/bin/tcsh
# Author: Greg Sawka

# Writes a makefile named Makefile in current directory based on all
# cpp files in the current directory.  Requires an executable name as
# $1, and takes additional arguments to be compiler options

# Will not work correctly if any of the .cpp files contain ", " or
# newlines in the filename.  Writes a temporary file named tmp in the
# current directory.  Requires all dependencies to be specified with
# pattern "#include \"".

echo -n "" > outSizeof

# Writes a newline-delimitted list of .hpp files to tmp
ls -m | sed -e 's/, /\n/g' | sed -e 's/,$//' | grep '.hpp$' > tmp

@ fileCount = `wc -l tmp | sed -e 's/tmp//'`

set currentFile = 1
while ($currentFile <= $fileCount)
  set fileName = `head -$currentFile tmp | tail -1`
  echo "// $fileName" >> outSizeOf
  grep '^class' $fileName | grep -v ';' | sed -e 's/class//' | sed -e 's/:.*//' | sed -e 's/{.*//' | sed -e 's/ //' > tmp2
  grep '^struct' $fileName | grep -v ';' | sed -e 's/struct//' | sed -e 's/:.*//' | sed -e 's/{.*//' | sed -e 's/ //' >> tmp2
  @ classCount = `wc -l tmp2 | sed -e 's/tmp2//'`
  set currentClass = 1
  while ($currentClass <= $classCount)
    set className = `head -$currentClass tmp2 | tail -1`
    echo -n 'std::cout << "' >> outSizeOf
    echo -n "Size of $className" >> outSizeOf
    echo -n ': " << ' >> outSizeOf
    echo "sizeof( $className ) << std::endl;" >> outSizeOf
    @ currentClass = $currentClass + 1
  end
  @ currentFile = $currentFile + 1
  echo "" >> outSizeOf
end
