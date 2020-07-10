#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// char arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187};
char arr[] = "qwerty";

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

		char out[sizeof arr];
		write(to_stdin, arr, sizeof arr);
		int n = read(from_stdout, out, sizeof out);
		// out[n-1] = '\0';
		waitpid(pid, NULL, 0);
		printf("Got this [%s]\n", out);
		printf("parent finish\n");
	} else {
		//child
		close(pipe1[1]);
		close(pipe2[0]);
		dup2(pipe1[0], STDIN_FILENO);
		dup2(pipe2[1], STDOUT_FILENO);
		close(pipe1[0]);
		close(pipe2[1]);

		//execlp("./b.out", "b.out");
		execlp("./input", "input", NULL);
		// char out[100];
		// printf("[%s]\n", out);
		// printf("child finish");
	}
	return 0;
}
