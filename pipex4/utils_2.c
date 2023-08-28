/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:10:40 by yachen            #+#    #+#             */
/*   Updated: 2023/08/28 14:54:13 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	sub_child(char **env, char *str)
{
	char	**path;
	char	**cmd;

	cmd = make_cmd(str);
	if (!cmd)
		return (-1);
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		path = make_path(find_var_path(env));
		if (!path)
			return (-1);
		if (find_execute_cmd(path, cmd) == -1)
			return (-1);
	}
	return (0);
}

void	child_1(char **env, char *str, int inf, int *pipefd)
{
	close(pipefd[0]);
	if (dup2(inf, STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	if (sub_child(env, str) == -1)
	{
		perror("Error : command not found ");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

void	child_2(char **env, char *str, int outf, int *pipefd)
{
	close(pipefd[1]);
	if (dup2(outf, STDOUT_FILENO) < 0 || dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	if (sub_child(env, str) == -1)
	{
		perror("Error : command not found ");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

static void	close_pipefd(int *pipefd1, int *pipefd2)
{
	close(pipefd1[0]);
	close(pipefd1[1]);
	close(pipefd2[0]);
	close(pipefd2[1]);
}


void	child_3(char **env, char *str, int *fdin, int *fdout)
{
	close(fdin[1]);
	close(fdout[0]);
	if (dup2(fdin[0], STDIN_FILENO) < 0 || dup2(fdout[1], STDOUT_FILENO) < 0)
	{
		close_pipefd(fdin, fdout);
		exit(EXIT_FAILURE);
	}
	if (sub_child(env, str) == -1)
	{
		close_pipefd(fdin, fdout);
		perror("Error : command not found ");
		exit(EXIT_FAILURE);
	}
	close(fdout[1]);
	close(fdin[0]);
	exit(EXIT_SUCCESS);
}
