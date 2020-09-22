
bison -dy filename.y
flex filename.l
cc lex.yy.c y.tab.c -w
./a.out
