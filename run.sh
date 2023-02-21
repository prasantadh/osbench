#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 output-folder"
    echo "Example: $0 data"
    exit 1
fi

# remove the artifacts of previous runs
rm -rf out

# build the script
mkdir out
cd out
meson --buildtype=release ../src
ninja
cd ..

# run the benchmark specified number of times
run() {

    if [[ $file == "out/create_files" ]]; then
        rm -rf files
        mkdir files
        mount -t tmpfs -o size=2G tmpfs `pwd`/files
        ./$file /tmp
        umount -f `pwd`/files
    else
        ./$file
    fi;

}

for file in $(find out -maxdepth 1 -executable -type f | sort); do
    echo $file `date` > /dev/stderr;
    run $file;
done > $1/$(uname -r);
