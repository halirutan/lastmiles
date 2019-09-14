

 grep 'Allocate' readme | awk 'p{print $3 "  " $5-p}{p=$5}' > deb_x86_64_tdelta_new.dat


