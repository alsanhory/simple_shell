#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

/**
 * display_prompt - used to display
 */
void display_prompt(void);

/**
 * execute_command - Execute
 * @input: command
 */
void execute_command(char *input);

/**
 * main - the main
 * Return: 0 on success.
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	size_t len;

	while (1)
	{
		display_prompt();

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		len = strlen(input);
		if (len > 0 && input[len - 1] == '\n')
		{
			input[len - 1] = '\0';
		}

		execute_command(input);

		if (strcmp(input, "exit") != 0)
		{
			printf("\n");
		}
	}

	return (0);
}

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * execute_command - Execute the provided command.
 * @input: The command to execute.
 */
void execute_command(char *input)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execlp(input, input, NULL) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

