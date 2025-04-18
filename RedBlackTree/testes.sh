#!/bin/sh

clear

make

# ./myrb < teste1.in > teste1.out
# diff teste1.sol teste1.out
./myrb < teste2.in > teste2.out
diff teste2.sol teste2.out
# ./myrb < teste3.in > teste3.out
# diff teste3.sol teste3.out
# ./myrb < teste4.in > teste4.out
# diff teste4.sol teste4.out

# rm teste1.out
rm teste2.out
# rm teste3.out
# rm teste4.out

make clean
