#include <stdio.h>
#include <string.h>

char *my_strtok(char *str, const char *delimiters, char **lastToken) 
{
	char *tokenStart;

	if (str == NULL) 
	{
		str = *lastToken;
	}

	while (*str != '\0' && strchr(delimiters, *str) != NULL) 
	{
		str++;
	}

	if (*str == '\0') 
	{
		*lastToken = NULL;
		return NULL;
	}

	tokenStart = str;
	while (*str != '\0' && strchr(delimiters, *str) == NULL) 
	{
		str++;
	}

	if (*str == '\0') 
	{
		*lastToken = NULL;
	} 
	else 
	{
		*str = '\0';
		*lastToken = str + 1;
	}

	return (tokenStart);
}
