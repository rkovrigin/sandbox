#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
	char s[128];
	memset(s,0,sizeof s);
	size_t m = read(0, s, sizeof s);
	s[m-1] = '\0';
	printf("%s\n", s);
	return 0;
}
