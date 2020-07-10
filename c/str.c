#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void){
	int pipe1[2], pipe2[2];
	pipe(pipe1); // stdin parent-write-1, child-read-0
	pipe(pipe2); // stdout parent-read-0, child-write-1

	
	int pid = fork();
	if (pid) {
		//parent
		close(pipe1[0]);
		close(pipe2[1]);
		int to_stdin = pipe1[1];
		int from_stdout = pipe2[0];

		char out[100];
		read(from_stdout, out, sizeof out);
		printf("{%s}\n", out);
		write(to_stdin, out, strlen(out));
		printf("parent finish\n");
		waitpid(pid, NULL, 0);
	} else {
		//child
		close(pipe1[1]);
		close(pipe2[0]);
		dup2(pipe1[0], STDIN_FILENO);
		dup2(pipe2[1], STDOUT_FILENO);
		close(pipe1[0]);
		close(pipe2[1]);

		//execlp("./b.out", "b.out");
		execlp("/bin/ls", "ls", NULL);
		char out[100];
		read(STDIN_FILENO, out, sizeof out);
		printf("[%s]\n", out);
		printf("child finish");
	}
	return 0;
}
