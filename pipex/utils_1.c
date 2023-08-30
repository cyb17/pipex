/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:13:38 by yachen            #+#    #+#             */
/*   Updated: 2023/08/30 16:14:02 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cls_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_perror(char *str)
{
	perror("Error");
	if (str)
		ft_printf(": %s\n", str);
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
	if (cmd[0] == NULL)
	{
		ft_printf("Error: %s: Command not found\n", str);
		exit(EXIT_FAILURE);
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
