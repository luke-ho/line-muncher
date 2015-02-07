#!/bin/bash

echo "- Creating muncher binary..."
make;
if [ $? -ne 0 ]; then
    echo "Error while trying to make muncher binary!";
    exit 1;
fi
pushd scripts;
if [ $? -ne 0 ]; then
    echo "Error while trying to move to scripts directory!";
    exit 1;
fi

echo "- Generating tests"
make;
if [ $? -ne 0 ]; then
    echo "Error while trying to gen_tests!";
    exit 1;
fi
./gen_tests;
if [ $? -ne 0 ]; then
    echo "Error while trying to run gen_tests!";
    exit 1;
fi
cd ../verif
if [ $? -ne 0 ]; then
    echo "Error while trying to move to verif!";
    exit 1;
fi
./run_tests.sh;
