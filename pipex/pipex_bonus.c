/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:25:37 by yachen            #+#    #+#             */
/*   Updated: 2023/09/05 16:38:00 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_procs(int *input, int *output, char **env, char *argv_value)
{
	char	*path;
	char	**cmd;
	char	*env_exev[] = {"PATH=/mnt/nfs/homes/yachen/bin:/usr/local/sbin:\
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", NULL};

	path = parsing_cmd(env, argv_value, env_exev);
	if (!path)
		return ;
	if (dup2(input[0], STDIN_FILENO) || dup2(output[1], STDOUT_FILENO) < 0)
	{
		cls_fd(input);
		cls_fd(output);
		ft_perror("dup2", 1);
	}
	cls_fd(input);
	cls_fd(output);
	cmd = make_cmd(argv_value);
	if (execve(path, cmd, NULL) == -1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		perror("Error");
	}
}

pid_t	procs_fd(int *input, int *output, char **env, char *argv_value)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
		child_procs(input, output, env, argv_value);
	else
		return (pid);
	return (0);
}

pid_t	procs_pipe(int *p_in, int *p_out, char **env, char *argv_value)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
		child_procs(p_in, p_out, env, argv_value);
	else
	{
		close(p_in[1]);
		return (pid);
	}
	return (0);
}

static int	creat_pipefd(int i, int argc, int pipefd[][2])
{
	if (i < argc - 4)
	{
		if ((pipe(pipefd[i])) < 0)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[argc - 4][2];
	pid_t	pid[argc - 3];
	int		fd[2];
	int		i;
	
	if (argc < 5)
		ft_perror("The number of parameters is not valid\n", 0);
	open_fd_bonus(fd, &argv, argv[argc - 1], &argc);
	i = 0;
	while (i < argc - 3)
	{
		if (creat_pipefd(i, argc, pipefd) == -1)
			break ;
		if (i == 0)
			pid[i] = procs_fd(fd, pipefd[i], env, *argv++);
		else if (i > 0 && i < argc - 4)
			pid[i] = procs_pipe(pipefd[i - 1], pipefd[i], env, *argv++);
		else
			pid[i] = procs_fd(pipefd[i - 1], fd, env, *argv++);
		i++;
	}
	clear_pipe_and_fd(i, fd, pipefd, argc - 4);
	wait_proces(i, pid, argc - 3);
	return (0);
}
