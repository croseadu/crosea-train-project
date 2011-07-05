path="/home/cam/book/long.file.name"
echo '${path##/*/}' is ${path##/*/}
echo '${path#/*/}' is ${path#/*/}
echo '${path}' is ${path}
echo '${path%.*}' is ${path%.*}
echo '${path%%.*}' is ${path%%.*}
