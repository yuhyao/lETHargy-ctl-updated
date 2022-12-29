# Hashes a cpp file, ignoring whitespace and comments.
# Usage: $ sh hash-cpp.sh < code.cpp
cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
