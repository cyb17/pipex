/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:03:52 by yachen            #+#    #+#             */
/*   Updated: 2023/08/19 15:49:28 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	make_path_tab2(char **path_tab, char *slash_cmd_name)
{
	int		i;
	char	**tmp;
	
	i = 0;
	while (path_tab[i])
	{
		tmp = path_tab[i];
		path_tab[i] = ft_strjoin(path_tab[i], slash_cmd_name);
		if (!path_tab)
		{
			free(slash_cmd_name);
			free_tab(path_tab);
			return (-1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

char	**make_path_tab(char *path, char *cmd_name)
{
	char *slash_cmd_name;
	char **path_tab;

	slash_cmd_name = ft_strjoin("/", cmd);
	if (!slash_cmd_name)
		return (NULL);
	path_tab = ft_split(path, ':');
	if (!path_tab)
	{
		free(slash_cmd_name);
		return (NULL);
	}
	if (make_path_tab2(path_tab, slash_cmd_name) == -1);
		return (NULL);
	return (path_tab);
}

int	execute_cmd(char **path_tab, char **cmd);
{
	int	i;
	
	i = 0;
	while (path_tab[i] && execve(path_tab[i], cmd, NULL))
		i++;
	if (path_tab[i] == NULL)
		return (-1);
	return (0);
}

int	pipex(int in, int out)
{
	int	pipe[2];
	
	close(pipe[0]);
	if (dup2(in, STDIN_FILENO) < 0 || dup2(pipe[1], STDOUT_FILENO) < 0)
	{
		close(pipe[1]);
		return (-1);
	}
	
}

void	child_procs(char *path, char **cmd_tab, int inf, int outf)
{
		pid_t	*pid;
		
		while ()
}

void	processus(char *path, char **cmd_tab, int inf, int outf)
{
	int		i;
	int		status;
	pid_t	*pid;

	i = 0;
	status = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * ft_strlen(cmd_tab));
	while (cmd_tab[i])
	{
		pid[i] = fork();
		i++;
	}
	if (pid[i] < 0)
		clsfd_exit_error(inf, ouf, "Error : fork");
	else if (pid[i] == 0)
		child_procs(path, cmd_tab, inf, outf);
	close(inf);
	close(outf);
	waitpid(pid[i], &status, 0);
}