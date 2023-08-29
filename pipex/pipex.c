/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:14:45 by yachen            #+#    #+#             */
/*   Updated: 2023/08/29 16:22:09 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**child_process(char *infile, int *fd, char *argv)
{
	int	f1;
	char **cmd;
	
	f1 = open(infile, O_RDONLY);
	if (f1 == -1)
	{
		cls_pipe(fd);
		ft_perror();
	}
	if (dup2(f1, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
	{
		cls_pipe(fd);
		close(f1);
		ft_perror();
	}
	cmd = make_cmd(argv);
	cls_pipe(fd);
	return (cmd);
}

char	**parent_process(char *outfile, int *fd, char *argv)
{
	int		f2;
	char	**cmd;

	f2 = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 == -1)
	{
		cls_pipe(fd);
		ft_perror();
	}
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(f2, STDOUT_FILENO) < 0)
	{
		cls_pipe(fd);
		close(f2);
		ft_perror();
	}
	cmd = make_cmd(argv);
	cls_pipe(fd);
	return (cmd);
}

void	ft_clean(char *path, char **cmd, int *fd)
{
	free_tab(cmd);
	free(path);
	cls_pipe(fd);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	**cmd;
	char	*path;

	if (argc == 5)
	{
		if(pipe(fd) == -1)
			ft_perror();
		pid = fork();
		if (pid == -1)
			ft_perror();
		else if (pid == 0)
			cmd = child_process(argv[1], fd, argv[2]);
		else
		{
			waitpid(pid, &status, 0);
			cmd = parent_process(argv[4], fd, argv[3]);
		}
		path = find_execute_path(env, cmd);
		execute_cmd(path, cmd, fd);
		ft_clean(path, cmd, fd);
	}
	else
		ft_printf("The number of parameters is not valid");
	return (0);
}
