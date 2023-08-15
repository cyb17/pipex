/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:20:50 by yachen            #+#    #+#             */
/*   Updated: 2023/08/15 14:29:06 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc(int *f1, char *cmd, int *pipe)
{
	char	**tab;
	char	**path;
	
	close(pipe[0]);		
	if (dup2(*f1, STDIN_FILENO) < 0 || dup2(pipe[1], STDOUT_FILENO) < 0)
		closepipe_and_error(pipe[1], "dup2");
	path = make_path();
	if (!path)
		closepipe_and_error(pipe[1], "path");
	tab = ft_split(cmd, ' ');
	if (!tab)
	{
		free_tab(path);
		closepipe_and_error(pipe[1], "tab");
	}
	if (find_execute_cmd(path, tab) == -1)
		error_execve(tab, path, pipe[1], *f1);
	clean_resource(tab, path, pipe[1], *f1);
	exit(EXIT_SUCCESS);
}	
void	parent_proc(int *f2, char *cmd, int *pipe)
{
	char 	**tab;
	char	**path;
	int		status;

	waitpid(-1, &status, WNOHANG);
	close(pipe[1]);
	if (dup2(*f2, STDOUT_FILENO) < 0 || dup2(pipe[0], STDIN_FILENO) < 0)
		closepipe_and_error(pipe[0], "dup2");
	path = make_path();
	if (!path)
		closepipe_and_error(pipe[0], "path");
	tab = ft_split(cmd, ' ');
	if (!tab)
	{
		free_tab(path);
		closepipe_and_error(pipe[0], "tab");
	}
	if (find_execute_cmd(path, tab) == -1)
		error_execve(tab, path, pipe[0], *f2);
	clean_resource(tab, path, pipe[0], *f2);
	exit(EXIT_SUCCESS);
	
}

void	processus(char **argv, int *f1, int *f2)
{
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1)
		closefd_and_error(*f1, *f2, "pipe");
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		closefd_and_error(*f1, *f2, "fork");
	}
	else if (pid == 0)
		child_proc(f1, argv[2], pipefd);
	else
		parent_proc(f2, argv[3], pipefd);
}