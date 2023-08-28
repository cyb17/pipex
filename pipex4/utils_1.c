/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:24:26 by yachen            #+#    #+#             */
/*   Updated: 2023/08/28 14:58:39 by yachen           ###   ########.fr       */
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

int	find_execute_cmd(char **path, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], cmd[0]);
		if (!path[i])
			return (-1);
		free(tmp);
		if (execve(path[i], cmd, NULL) == -1)
			i++;
		else
			break ;
	}
	if (path[i] == NULL)
		return (-1);
	return (0);
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
