/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:13:38 by yachen            #+#    #+#             */
/*   Updated: 2023/08/30 13:28:39 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cls_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_perror(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
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

/* join str to each tab[i] of char **tab 
return NULL if ft_strjoin failed */
int	tab_strjoin(char **tab, char *str)
{
	int		i;
	char	*tmp;

	if (!str)
		return (-1);
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

/* find and split environnement variable PATH, than join each path with "/cmd"
return NULL if (PATH don't find | ft_split failed * | tab_join failed */
char	**find_path(char **env, char *cmd)
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
	if (tab_strjoin(path, "/") == -1
		| tab_strjoin(path, cmd) == -1)
	{
		free_tab(path);
		return (NULL);
	}
	return (path);
}

/* find executable file's path
return NULL if not found */
char	*find_execute_path(char **env, char **cmd)
{
	char	**cmd_path;
	char	*path;
	int		i;

	cmd_path = find_path(env, cmd[0]);
	if (!cmd_path)
		return (NULL);
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
	if (!path)
		perror("Error");
	return (path);
}

int	parsing_cmd(char **env, char *cmd)
{
	char	**split_cmd;
	char	**env_path;

	split_cmd = make_cmd(cmd);
	if (cmd[0] == '/')
	{
		if (access(split_cmd[0], F_OK | R_OK | X_OK) == -1)
		{
			free_tab(split_cmd);
			perror("Error");
			return (-1);
		}
	}
	else
	{
		env_path = find_path(env, split_cmd[0]);
		while (env_path[i])
		{
			if (access(env_path[i], F_OK | R_OK | X_OK) == 0)
			{
				free_tab(split_cmd);
				free_tab(env_path);
				return(1);
			}
			i++;
		}
	}
	return (-1);
}
