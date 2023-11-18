#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define PROMPT "#cisfun$ "

void display_prompt(void);

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char *token;
	size_t len = 0;
	int chr;
	pid_t pid;

	while (1)
	{
		display_prompt();

		chr = getline(&token, &len, stdin);

		if (chr == -1)
		{
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}

		if (token[chr - 1] == '\n')
		{
			token[chr - 1] = '\0';
		}

		if (feof(stdin))
		{
			printf("\n");
			free(token);
			exit(EXIT_SUCCESS);
		}

		pid = fork();

		if (pid == -1)
		{
			perror("Fork Failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char *args[2];

			args[0] = token;
			args[1] = NULL;

			execve(token, args, __environ);
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

