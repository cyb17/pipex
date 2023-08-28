/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:14:45 by yachen            #+#    #+#             */
/*   Updated: 2023/08/28 17:57:45 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cls_pipe(int *fd)
{
	close(fd[0]);
	close[fd[1]];
}

void	ft_perror(void)
{
	perror("Error : ");
	exit(EXIT_FAILURE);
}

void	child_process(char *infile, int *fd)
{
	int	f1;

	f1 = open(infile, O_RDONLY);
	if (f1 == -1)
	{
		cls_pipe(fd);
		ft_perror();
	}
	if (dup2(infile, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
	{
		cls_pipe(fd);
		close(f1);
		ft_perror();
	}
}

void	parent_process(char *outfile, int *fd)
{
	int	f2;

	f2 = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 == -1)
	{
		cls_pipe(fd);
		ft_perror();
	}
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(outfile, STDOUT_FILENO) < 0)
	{
		cls_pipe(fd);
		close(f2);
		ft_perror();
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_perror();
		pid = fork();
		if (pid == -1)
			ft_perror();
		else if (pid == 0)
			child_process(argv[1], fd);
		else
		{
			waitpid(pid, &status, 0);
			parent_process(argv[argc - 1], fd);
		}
		if (find_execute_cmd(env, argv, pid) == -1)
			perror();
		cls_pipe(fd);
	}
	else
		ft_printf("The number of parameters is not valid");
	return (0);
}
