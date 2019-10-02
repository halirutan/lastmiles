#!/bin/sh
rm -f out
touch out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out
./tn -f >> out

grep -c ' ' out | sed 's/^/  space /'
grep -c '\.[0-9][0-9][0-9][0-9][0-9][0-9][0-9][1-9]0$' out | sed 's/^/ 1 zero /'
grep -c '\.[0-9][0-9][0-9][0-9][0-9][0-9][1-9]00$' out | sed 's/^/ 2 zero /'
grep -c '\.[0-9][0-9][0-9][0-9][0-9][1-9]000$' out | sed 's/^/ 3 zero /'
grep -c '\.[0-9][0-9][0-9][0-9][1-9]0000$' out | sed 's/^/ 4 zero /'
grep -c '\.[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][1-9]$' out | sed 's/^/nonzero /'

