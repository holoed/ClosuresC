gcc -g -C src/Main.c src/JuniorLib.c -I include -o testProg   
./testProg
# objdump -d -S testProg
rm testProg