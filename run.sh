#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <repetitions>"
    echo "Example: $0 4 to run the benchmark 4 times"
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
    for i in `seq 1 $2`; do
        if [[ $file == "out/create_files" ]]; then
            ./$file /tmp
        else
            ./$file
        fi;
    done;
}

for file in $(find out -maxdepth 1 -executable -type f); do
    run $file $1;
done > $(date +%s)-$(uname -r);
