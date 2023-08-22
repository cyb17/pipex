/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bing <bing@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:21:53 by bing              #+#    #+#             */
/*   Updated: 2023/08/22 12:18:01 by bing             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_execute_cmd(char **path, char **cmd)
{
	int	i;

	i = 0;
	while (path[i] && execve(path[i], cmd, NULL) == -1)
		i++;
	if (path[i] == NULL)
	{
		ft_printf("Error : command not found\n");
		return (-1);
	}
	return (0);
}

static int	sub_child(char **path, char *cmd_str)
{
	int		i;
	char	*tmp;
	char	**cmd;
	
	i = 0;
	cmd = ft_split(cmd_str, ' ');
	if (!cmd)
		return (-1);	
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], cmd[0]);
		if (!path[i])
			return (-1);
		free(tmp);
		i++;
	}
	if (find_execute_cmd(path, cmd) == -1)
	{
		free_tab(cmd);
		return (-1);
	}
	free_tab(cmd);
	return (0);
}

static void	child_in(char **path, char *cmd, int inf, int *pipefd)
{
	close(pipefd[0]);
	if (dup2(inf, STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
		ft_perror("Error : dup2 child_in ");
	if (sub_child(path, cmd) == -1)
	{
		close(pipefd[1]);
		print_error("Error : sub_child\n");
	}
	close(pipefd[1]);
}

static void	child_out(char **path, char *cmd, int outf, int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(outf, STDOUT_FILENO) < 0)
		ft_perror("Error : dup2 child_out ");
	if (sub_child(path, cmd) == -1)
	{
		close(pipefd[0]);
		print_error("Error : sub_child\n");
	}
	close(pipefd[0]);
}

static void	child(char **path, char *cmd, int *pipefd)
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
		ft_perror("Error : dup2 child ");
	if (sub_child(path, cmd) == -1)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		print_error("Error : sub_child\n");
	}
	close(pipefd[1]);
	close(pipefd[0]);
}

void	processus(char **path, char **cmd, int inf, int outf)
{
	int		pipefd[2];
	int		nb_child;
	pid_t	*pid;
	int		i;
	//int		status;

	pipe(pipefd);
	nb_child = count_child(cmd);
	pid = (pid_t *)malloc(sizeof(pid_t) * nb_child);
	i = -1;
	while (++i < nb_child)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			clsfd_exit_error(inf, outf, "Error : fork failed ");
		else if (pid[i] == 0 && i == 0)
			child_in(path, cmd[i], inf, pipefd);
		else if (pid[i] == 0 && i == nb_child - 1)
			child_out(path, cmd[i], outf, pipefd);
		else if (pid[i] == 0)
			child(path, cmd[i], pipefd);
	}
	/*int j = 0;
	while (j < nb_child)
		printf("%d\n", pid[j++]);*/
	//wait_all_procs(i, pid);
	clean_ressource(path, cmd, inf, outf);
}
