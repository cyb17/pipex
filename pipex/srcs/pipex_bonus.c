/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:25:37 by yachen            #+#    #+#             */
/*   Updated: 2023/09/08 16:59:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	child_procs(int *input, int *output, char **env, char *argv_value)
{
	char	*path;
	char	**cmd;
	char	*env_exev[2];

	env_exev[0] = "PATH=/mnt/nfs/homes/yachen/bin:/usr/local/sbin:\
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	env_exev[1] = NULL;
	path = parsing_cmd(env, argv_value, env_exev);
	if (!path || dup2(input[0], STDIN_FILENO)
		|| dup2(output[1], STDOUT_FILENO) < 0)
	{
		cls_fd(input);
		cls_fd(output);
		if (path)
			ft_perror("dup2", 1);
		else
			exit(EXIT_FAILURE);
	}
	cls_fd(input);
	cls_fd(output);
	cmd = make_cmd(argv_value);
	if (execve(path, cmd, NULL) == -1)
		ft_perror("execve", 1);
}

pid_t	procs_fdin(int *fd, int *pipefd, char **env, char *argv_value)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
		child_procs(fd, pipefd, env, argv_value);
	else
	{
		close(pipefd[1]);
		close(fd[0]);
		return (pid);
	}
	return (0);
}

pid_t	procs_pipe(int *fd, int **pipefd, char **env, char *argv_value)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
	{
		cls_fd(fd);
		child_procs(pipefd[0], pipefd[1], env, argv_value);
	}
	else
	{
		close(pipefd[0][0]);
		close(pipefd[1][1]);
		return (pid);
	}
	return (0);
}

pid_t	procs_fdout(int *pipefd, int *fd, char **env, char *argv_value)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
		child_procs(pipefd, fd, env, argv_value);
	else
	{
		close(pipefd[0]);
		close(fd[1]);
		return (pid);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_tab	tab;
	int		fd[2];
	int		i;

	if (argc < 5)
		ft_perror("The number of parameters is not valid\n", 0);
	open_fd_bonus(fd, &argv, argv[argc - 1], &argc);
	ft_init_tab(&tab, argc);
	i = 0;
	argv = argv + 2;
	while (i < argc - 3)
	{
		if (creat_pipefd(i, argc, tab.pipefd) == -1)
			break ;
		if (i == 0)
			tab.pid[i] = procs_fdin(fd, tab.pipefd[i], env, *argv++);
		else if (i > 0 && i < argc - 4)
			tab.pid[i] = procs_pipe(fd, tab.pipefd + (i - 1), env, *argv++);
		else
			tab.pid[i] = procs_fdout(tab.pipefd[i - 1], fd, env, *argv++);
		i++;
	}
	wait_proces(i, tab.pid, argc - 3);
	free_tab_int(&tab, argc);
	return (0);
}
