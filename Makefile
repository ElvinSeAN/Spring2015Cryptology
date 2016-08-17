gmpexample: gmpexample.c
	clang -L /usr/local/lib -I /usr/local/include -lgmpxx -lgmp -o testing gmpexample.c 