/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:25:37 by yachen            #+#    #+#             */
/*   Updated: 2023/08/31 18:16:30 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_processus(int *intput, int *output, char **env, char *argv_value)
{
	char	*path;
	char	**cmd;

	path = parsing_cmd(env, argv_value);
	if (!path)
		return ;
	if (dup2(intput[0], STDIN_FILENO) < 0 || dup2(output[1], STDOUT_FILENO) < 0)
	{
		cls_fd(intput);
		cls_fd(output);
		ft_perror("dup2");
	}
	cls_fd(intput);
	cls_fd(output);
	cmd = make_cmd(argv_value);
	if (execve(path, cmd, NULL) == -1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		perror("Error");
	}
}
void	clear_pipe_and_fd(int *fd, int pipefd[][2], int nb_pipe)
{
	int	i;
	
	cls_fd(fd);
	i = 0;
	while (i < nb_pipe)
		cls_fd(pipefd[i++]);
}

void	wait_proces(int *pid, int nb_proces)
{
	int	i;
	int	status;
	
	i = 0;
	while (i < nb_proces)
		waitpid(pid[i++], &status, 0);
}

pid_t	proces(int *intput, int *output, char **env, char *argv_value)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return (0);
	}
	else if (pid == 0)
		child_processus(intput, output, env, argv_value);
	else
		return (pid);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[argc - 4][2];
	pid_t	pid[argc - 3];
	int		fd[2];
	int		i;
	
	if (argc >= 5)
	{
		open_fd(fd, argv[1], argv[argc - 1]);
		i = 0;
		argv = argv + 2;
		while (i < argc - 3)
		{
			if (i < argc - 2)
				pipe(pipefd[i]);
			if (i == 0)
				pid[i] = proces(fd, pipefd[i], env, *argv);
			else if (i > 0 && i < argc - 4)
				pid[i] = proces(pipefd[i - 1], pipefd[i], env, *argv);
			else
				pid[i] = proces(pipefd[i - 1], fd, env, *argv);
			i++;
			argv++;
		}
		clear_pipe_and_fd(fd, pipefd, argc - 4);
		wait_proces(pid, argc - 3);
	}
	else
		ft_printf("The number of parameters is not valid\n");
	return (0);
}
