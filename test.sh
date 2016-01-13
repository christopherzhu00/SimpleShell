#!/bin/bash

function makeBeautifulThings() {
touch a
printf "hi\n" > a
printf "hi again\n" >> a
touch b
touch cancer
touch output
}

function sayGoodBye() {
rm -f a
rm -f b
#rm -f cancer
#rm -f output
}

makeBeautifulThings

# Test case to see if cat works
./simpsh --rdonly a --wronly b --wronly cancer --command 0 1 2 cat

printf "hi\n" > checkFile
printf "hi again\n" >> checkFile

cmp --silent b checkFile || echo "cat didn't work"

# Test case to check for errors for incorrect number of arguments as well as verbose
./simpsh --verbose --rdonly a  --wronly cancer --command 0 1 2 cat > output
printf -- "--rdonly a\n" >checkFile
printf -- "--wronly cancer\n" >>checkFile
printf -- "--command 0 1 2 cat\n" >> checkFile

cmp --silent output checkFile || echo "verbose didn't work"

# Test case for when arguments for command are too large
./simpsh --rdonly a --wronly b --wronly cancer --command 100 1 2 cat
printf "cat: -: Input/output error\n" > checkFile
cmp --silent cancer checkFile || echo "check to make sure error checking works"


sayGoodBye