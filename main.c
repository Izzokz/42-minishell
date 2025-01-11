#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void) argc;
	(void) argv;
	(void) envp;
	line = readline("minishell > ");
	while (line)
	{
		free(line);
		line = readline("minishell > ");
		printf("Line you wrote: %s\n", line);
		if (line[0] == '\0')
		{
			free(line);
			line = NULL;
		}
	}
	return (0);
}


