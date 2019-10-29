#!/bin/sh
# /usr/bin/printf '0 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '0' | wc -l
# /usr/bin/printf '1 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '1' | wc -l
# /usr/bin/printf '2 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '2' | wc -l
# /usr/bin/printf '3 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '3' | wc -l
# /usr/bin/printf '4 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '4' | wc -l
# /usr/bin/printf '5 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '5' | wc -l
# /usr/bin/printf '6 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '6' | wc -l
# /usr/bin/printf '7 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '7' | wc -l
# /usr/bin/printf '8 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '8' | wc -l
# /usr/bin/printf '9 '; grep '^pi' out_100000.test | tail -1 | cut -c11-98654 | grep -o '9' | wc -l

/usr/bin/printf "\n\n\nNow from the billion digits\n"
/usr/bin/printf '0 '; grep -o '0' billion.txt | wc -l
/usr/bin/printf '1 '; grep -o '1' billion.txt | wc -l
/usr/bin/printf '2 '; grep -o '2' billion.txt | wc -l
/usr/bin/printf '3 '; grep -o '3' billion.txt | wc -l
/usr/bin/printf '4 '; grep -o '4' billion.txt | wc -l
/usr/bin/printf '5 '; grep -o '5' billion.txt | wc -l
/usr/bin/printf '6 '; grep -o '6' billion.txt | wc -l
/usr/bin/printf '7 '; grep -o '7' billion.txt | wc -l
/usr/bin/printf '8 '; grep -o '8' billion.txt | wc -l
/usr/bin/printf '9 '; grep -o '9' billion.txt | wc -l


