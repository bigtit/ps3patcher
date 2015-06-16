# ps3patcher
A homely port of ps3 nor/nand patcher program of  Swizzy/PS3DumpChecker from windows to gnu linux using c++.
**It would be immensely imprudent and precarious to use the tool immediately without a precedent validation of your own ps3 nor/nand dumps, which could be done by the ps3checker program.**

### how to use
1. git clone https://github.com/bigtit/ps3patcher.git
2. cd ps3patcher && make
3. ./tmain -t -f -s ps3.dump
4. the .out file is what you need to burn into ps3

### test environment
archlinux 4.0.5 x86_64 with
gcc version 5.1.0
