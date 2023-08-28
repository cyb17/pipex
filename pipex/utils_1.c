/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:13:38 by yachen            #+#    #+#             */
/*   Updated: 2023/08/28 18:47:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* find variable PATH in char **env and split it 
return NULL if don't find or ft_split failed */
char	**find_path(char **env)
{
	char	**path;

	while (*env && ft_strncmp(*env, "PATH", 4) != 0)
		env++;
	if (*env)
		return (NULL);
	path = ft_split(*env, ':');
	if (!path)
		return (NULL);
	return (path);
}

/* make PATH a char ** with '/' 
return NULL if (PATH == NULL | ft_split  failed | ft_strjoin failed) */
char	**make_path(char **var_path, char **cmd)
{
	int		i;
	char 	*tmp1;
	char	*tmp2;
	
	if (!var_path)
		return (NULL);
	i = 0;
	while (var_path[i])
	{
		tmp1 = var_path[i];
		var_path[i] = ft_strjoin(var_path[i], "/");
		if (!var_path[i])
		{
			free_tab(var_path);
			return (NULL);
		}
		free(tmp1);
		tmp2 = var_path[i];
		var_path[i] = ft_strjoin(var_path[i], cmd[0]);
		if (!var_path[i])
		{
			free_tab(var_path);
			return (NULL);
		}
		free(tmp2);
		i++;
	}
	return (var_path);
}

int	find_execute_cmd(char **env, char **argv, pid_t pid)
{
	char	**path;
	char	**cmd;
	int		i;

	if (pid == 0)
		cmd = make_cmd(argv[2]);
	else
		cmd = make_cmd(argv[3]);
	path = make_path(find_var_path(env), cmd);
	if (!path)
		return (-1);
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		while (path[i] && execve(path[i], cmd, NULL) == -1)
			i++;
		if (!path[i])
		{
			free_tab(path);
			free_tab(cmd);
			return (-1);
		}
	}
	return (0);
}
