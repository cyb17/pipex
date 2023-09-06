/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:13:38 by yachen            #+#    #+#             */
/*   Updated: 2023/09/06 11:31:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* split cmd and options in char **
return NULL if (str == NULL | split failed) */
char	**make_cmd(char *str)
{
	char	**cmd;

	if (!str)
		return (NULL);
	cmd = ft_split(str, ' ');
	if ((cmd[0] == NULL) || !cmd)
	{
		if (cmd)
		{
			free(cmd);
			ft_printf("Error : %s: Command not found\n", str);
		}
		return (NULL);
	}
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
	if ((tab_strjoin(path, "/") == -1)
		| (tab_strjoin(path, cmd) == -1))
	{
		free_tab(path);
		return (NULL);
	}
	return (path);
}

static char	*sub_parsing_cmd(char **split_cmd)
{
	char	*path;

	if (!split_cmd)
		return (NULL);
	path = NULL;
	if (access(split_cmd[0], F_OK | R_OK | X_OK) == -1)
		ft_printf("Error: %s: no such file or directory\n", split_cmd[0]);
	else
		path = ft_strdup(split_cmd[0]);
	free_tab(split_cmd);
	return (path);
}

/* check cmd and find it path, return NULL if there is a pb */
char	*parsing_cmd(char **env_main, char *cmd, char **env_exev)
{
	char	**split_cmd;
	char	**env_path;
	char	*path;
	int		i;

	split_cmd = make_cmd(cmd);
	path = NULL;
	if (cmd[0] == '/')
	{
		path = sub_parsing_cmd(split_cmd);
		return (path);
	}
	env_path = find_path(env_main, split_cmd[0]);
	if (!env_path)
		env_path = find_path(env_exev, split_cmd[0]);
	i = 0;
	while (env_path[i] && access(env_path[i], F_OK | R_OK | X_OK) == -1)
		i++;
	if (!env_path[i])
		ft_printf("Error: %s: Command not found\n", split_cmd[0]);
	else
		path = ft_strdup(env_path[i]);
	free_tab(split_cmd);
	free_tab(env_path);
	return (path);
}
