build: dns

tema2 : dns.o tree.o addrList.o treeChildren.o files.o user.o
	gcc -Wall $^ -o dns
tema2.o : dns.c
	gcc -Wall -c -g dns.c
tree.o : tree.c
	gcc -Wall -c -g tree.c
addrList.o : addrList.c
	gcc -Wall -c -g addrList.c
treeChildren.o : treeChildren.c
	gcc -Wall -c -g treeChildren.c
files.o : files.c
	gcc -Wall -c -g files.c
user.o : user.c
	gcc -Wall -c -g user.c

run : tema2
	./dns

clean :
	rm -rf *.o tema2
