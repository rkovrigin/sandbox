#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void){
    int p[2];
    pipe(p);

    char out[] = "Hello world!";
    char in[sizeof out];

    int w = write(p[1], out, sizeof out);
    int r = read(p[0], in, sizeof in);
    printf("%s\n", in);
    return 0;
}