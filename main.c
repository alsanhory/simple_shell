#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

/**
 * main - the main entry
 * Return: 0 on sucess
 */

int main(void)
{
	
	char input[MAX_INPUT_SIZE];
	char *args[MAX_INPUT_SIZE / 2 + 1];

	while (1)
	{
		printf("#cisfun$ ");

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		size_t len = strlen(input);
		if (len > 0 && input[len - 1] == '\n')
		{
			input[len - 1] = '\0';
		}

		char *token = strtok(input, " ");
		int i = 0;

		while (token != NULL)
	       	{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{

			if (execvp(args[0], args) == -1)
			{
				perror(args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{

			int status;
			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
			{

				printf("\n");
			}
		}
	}

	return (0);
}

