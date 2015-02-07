#!/bin/bash

../bin/muncher ../tests/1.txt >& logs/output_1.txt
../bin/muncher ../tests/2.txt >& logs/output_2.txt
../bin/muncher ../tests/3.txt >& logs/output_3.txt

egrep "^[0-9]+" logs/output_1.txt >& logs/verif_1.txt
egrep "^[0-9]+" logs/output_2.txt >& logs/verif_2.txt
egrep "^[0-9]+" logs/output_3.txt >& logs/verif_3.txt

perl verif.pl logs/verif_1.txt 1
if [ $? -ne 0 ]; then
    echo "1st test failed!"
    exit 1;
fi    
perl verif.pl logs/verif_2.txt 0
if [ $? -ne 0 ]; then
    echo "2nd test failed!"
    exit 1;
fi    
perl verif.pl logs/verif_3.txt 0
if [ $? -ne 0 ]; then
    echo "3rd test failed!"
    exit 1;
fi    

echo "Congratulations! All tests successful!"
rm logs/*
