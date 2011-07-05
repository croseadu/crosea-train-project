filename=${1:?"File Name is missing"}
lines=${2:-10}

sort -nr $filename | head -$lines

