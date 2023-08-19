#include <stdio.h>
#include "libft/libft.h"

char	*find_path(char **env)
{
	while (*env && ft_strncmp(*env, "PATH", 4) != 0)
		env++;
	return (*env);
}

int	main(int argc, char **argv, char **env)
{
	char *path;

	path = find_path(argv);
	if (!path)
		printf("error");
	printf("%d,%s,%s\n %s", argc, env[0], argv[0], path);
}