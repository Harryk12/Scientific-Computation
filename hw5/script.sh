#!/bin/bash


if [ $# -lt 1 ] ; then
    echo "You forgot to add an argument"
    exit
fi
if [ $1 -lt 0 ] ; then
    echo "Add a positive integer"
    exit
fi;
if [ $1 == "-h" ] ; then
    echo "Usage: yourscript nnn where nnn is a positive integer"
    exit
fi
PATH="../build/fizzbuzz_unix"

"$PATH" $1
