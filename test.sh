#!/bin/bash

function makeBeautifulThings() {
touch a
printf "hi\n" > a
printf "hi again\n" >> a
touch b
touch cancer
touch output
touch file1.txt
touch file2
touch file3
touch out
touch one
touch check
}

function sayGoodBye() {
rm -f a
rm -f b
rm -f thirdTest.txt
rm -f cancer
rm -f output
rm -f file1.txt
rm -f file2
rm -f file3
rm -f out
#rm -f one
#rm -f c
rm -f errors
#rm -f check
}

makeBeautifulThings

 #Test case to see if cat works
./simpsh --rdonly a --wronly b --wronly cancer --command 0 1 2 cat

printf "hi\n" > checkFile
printf "hi again\n" >> checkFile

cmp --silent b checkFile || echo "cat didn't work"

#Test case to check for errors for incorrect number of arguments as well as verbose
./simpsh --verbose --rdonly a --wronly b --wronly cancer --command 0 1 2 cat > output
#./simpsh --verbose --rdonly a --wronly b --wronly cancer --command 0 1 2 cat
printf "./test.sh\n" >checkFile
printf -- "--rdonly a\n" >checkFile
printf -- "--wronly b\n" >>checkFile
printf -- "--wronly cancer\n" >>checkFile
printf -- "--command 0 1 2 cat\n" >> checkFile
cmp --silent output checkFile || echo "verbose didn't work"


./simpsh --rdonly --wronly file2 --wronly file3 --command 0 1 2 cat 2> out
printf "Incorrect number of arguments\nError in opening file.\nError in arguments. Not enough arguments.\n" > file1.txt
cmp --silent out file1.txt || echo "Failing to handle insufficient arguments."

printf "WORLD\n" >one
printf "Hello\n" >>one
printf "hi\n" >check
printf "hi again\n" >>check
printf "hello\n" >>check
printf "world\n" >>check 
./simpsh --rdonly one --pipe --pipe --creat --wronly cats --creat --append --wronly errors --command 3 5 6 tr A-Z a-z --command 0 2 6 sort --command 1 4 6 cat b - 
cmp --silent check cats || echo "Last check fails"

rm -f checkFile

sayGoodBye