/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:13:38 by yachen            #+#    #+#             */
/*   Updated: 2023/08/29 16:14:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

/* join str to each tab[i] of char **tab 
return NULL if ft_strjoin failed */
int	tab_strjoin(char **tab, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		tmp = tab[i];
		tab[i] = ft_strjoin(tab[i], str);
		if (!tab[i])
		{
			free_tab(tab);
			return (-1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

/* find environnement variable PATH, split it, str_joint each path[i]
with "/cmd"
return NULL if (PATH don't find | ft_split failed * | tab_join failed*/
char	**find_path(char **env, char **cmd)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (!env[i])
		return (NULL);
	path = ft_split(env[i] +5, ':');
	if (!path)
		return (NULL);
	if ((tab_strjoin(path, "/") == -1)
		| (tab_strjoin(path, cmd[0]) == -1))
		return (NULL);
	return (path);
}

/* find path wich have executable file */
char	*find_execute_path(char **env, char **cmd)
{
	char	**cmd_path;
	char	*path;
	int		i;

	if (!cmd)
		return (NULL);
	cmd_path = find_path(env, cmd);
	i = 0;
	path = NULL;
	while (cmd_path[i])
	{
		if (access(cmd[0], F_OK | R_OK | X_OK) == 0)
		{
			path = ft_strdup(cmd[0]);
			break ;
		}
		else if (access(cmd_path[i], F_OK | R_OK | X_OK) == 0)
		{
			path = ft_strdup(cmd_path[i]);
			break ;
		}
		i++;
	}
	free_tab(cmd_path);
	return (path);
}

void	execute_cmd(char *path, char **cmd, int *fd)
{
	if (!cmd)
	{
		cls_pipe(fd);
		perror("Error : cmd malloc failed");
		return ;
	}
	if (!path)
	{
		cls_pipe(fd);
		perror("Error : command not found ");
		return ;
	}
	execve(path, cmd, NULL);
}

void	cls_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_perror(void)
{
	perror("Error : ");
	exit(EXIT_FAILURE);
}
 