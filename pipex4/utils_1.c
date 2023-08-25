/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:24:26 by yachen            #+#    #+#             */
/*   Updated: 2023/08/25 14:09:07 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* find variable PATH in char **env 
return NULL if don't find */
char	*find_var_path(char **env)
{
	while (*env && ft_strncmp(*env, "PATH", 4) != 0)
		env++;
	return (*env);
}

/* make PATH a char ** with '/' 
return NULL if (PATH == NULL | split  failed | strjoin failed) */
char	**make_path(char *var_path)
{
	char	**path;
	int		i;
	char 	*tmp;
	
	if (!var_path)
		return (NULL);
	path = ft_split(var_path, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
		{
			free_tab(path);
			return (NULL);
		}
		free(tmp);
		i++;
	}
	return (path);
}

/* split cmd and options in char **
return NULL if (str == NULL | split failed) */
char	**make_cmd(char *str)
{
	char **cmd;

	if (!str)
		return (NULL);
	cmd = ft_split(str, ' ');
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	count_procs(char **argv)
{
	if (!argv)
		return (0);
	int	procs;

	procs = 2;
	while (argv[procs + 1])
		procs++;
	return (procs - 2);
}

void	wait_all_procs(int procs)
{
	int status;
	pid_t pid;
	int n = 0;
	while (n < procs)
	{
		pid = wait(&status);
		printf("Fork [%i] terminé avec le code %i\n", pid, status);
		n++;
	}
}
