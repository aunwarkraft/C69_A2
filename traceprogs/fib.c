#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int n, i, fib[47];

    if (argc != 2) {
	fprintf(stderr, "usage: fib n\n");
	return(1);
    }

    if ((n = atoi(argv[1])) < 0 || n >= 47) {
	fprintf(stderr, "fib: maximum argument is 46\n");
	return(1);
    }

    fib[0] = 0;
    fib[1] = 1;
    for (i = 2; i <= n; i++)
	fib[i] = fib[i-1] + fib[i-2];

    printf("%d\n", fib[n]);
    return(0);
}
