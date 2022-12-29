# Hashes each line of given file.
# Usage: $ sh hash-line.sh hash-cpp.sh code.cpp
IFS=''
while read line; do
  echo $line | sh $1 | cut -c-2 | tr -d '\n'
  echo " "$line
done < $2
