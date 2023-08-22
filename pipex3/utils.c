/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bing <bing@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:24:26 by yachen            #+#    #+#             */
/*   Updated: 2023/08/22 11:04:16 by bing             ###   ########.fr       */
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

/* return NULL if (!cmd_tab | strdup failed | argv[i] is empty) */
char	**make_cmd_tab(int argc, char **argv)
{
	int		i;
	char	**cmd_tab;

	cmd_tab = (char **)malloc(sizeof(char *) * (argc - 2));
	if (!cmd_tab)
		return (NULL);
	i = 0;
	while (i < argc - 3)
	{
		cmd_tab[i] = ft_strdup(argv[i + 2]);
		if (!cmd_tab[i] || *(cmd_tab[i]) == '\0')
		{
			free_tab(cmd_tab);
			return (NULL);
		}
		i++;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

int	count_child(char **cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	wait_all_procs(int i, int *pid)
{
	int		status;
	
	while (--i >= 0)
		waitpid(pid[i], &status, 0);
}

void	clean_ressource(char **path, char **cmd, int inf, int outf)
{
	free_tab(path);
	free_tab(cmd);
	close(inf);
	close(outf);
}
