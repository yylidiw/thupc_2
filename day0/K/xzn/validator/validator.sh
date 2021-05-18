#!/bin/sh
g++ validator.cpp -o validator
for (( i = 1; i < 6; i++ )); do
    ./validator < ../../data/$i.in 
done

for (( i = 1; i < 4; i++ )); do
    ./validator < ../../down/$i.in 
done

echo "Finish"
