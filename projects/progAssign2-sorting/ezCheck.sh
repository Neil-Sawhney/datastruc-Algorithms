#!/bin/bash
g++ main.cpp

./a.out << bloop 
sample1.txt
out1.txt
bloop

./a.out << bloop 
sample2.txt
out2.txt
bloop

./a.out << bloop 
sample3.txt
out3.txt
bloop

./a.out << bloop 
sample4.txt
out4.txt
bloop

diff out_sample1.txt out1.txt
diff out_sample2.txt out2.txt
diff out_sample3.txt out3.txt
diff out_sample4.txt out4.txt