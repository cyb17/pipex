/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:14:45 by yachen            #+#    #+#             */
/*   Updated: 2023/09/04 11:10:42 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* -parse command, EXIT_FAILURE if command is "" or "  " 
-redirect input and output, EXIT_FAILURE if error
-execute command if path and command are correct, else EXIT_FAILURE */
void	child1(int *fd, int *pipefd, char **env, char *cmd_str)
{
	char	*path;
	char	**cmd;
	char	*env_exev[] = {"PATH=/mnt/nfs/homes/yachen/bin:/usr/local/sbin:\
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", NULL};

	path = parsing_cmd(env, cmd_str, env_exev);
	if (!path)
		return ;
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		cls_fd(fd);
		cls_fd(pipefd);
		ft_perror("dup2", 1);
	}
	cls_fd(pipefd);
	cls_fd(fd);
	cmd = make_cmd(cmd_str);
	if (execve(path, cmd, NULL) == -1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		perror("Error");
	}
}

void	child2(int *fd, int *pipefd, char **env, char *cmd_str)
{
	char	*path;
	char	**cmd;
	char	*env_exev[] = {"PATH=/mnt/nfs/homes/yachen/bin:/usr/local/sbin:\
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", NULL};

	path = parsing_cmd(env, cmd_str, env_exev);
	if (!path)
		return ;
	if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
	{
		cls_fd(fd);
		cls_fd(pipefd);
		ft_perror("dup2", 1);
	}
	cls_fd(pipefd);
	cls_fd(fd);
	cmd = make_cmd(cmd_str);
	if (execve(path, cmd, NULL) == -1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		perror("Error");
	}
}

/* creat 2 childs process and wait for them all */
void	processus(int *pipefd, int *fd, char **env, char**argv)
{
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		fork_error(pipefd, fd);
	else if (pid1 == 0)
		child1(fd, pipefd, env, argv[2]);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			fork_error(pipefd, fd);
		else if (pid2 == 0)
			child2(fd, pipefd, env, argv[3]);
	}
	cls_fd(fd);
	cls_fd(pipefd);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	int		fd[2];

	if (argc == 5)
	{
		open_fd(fd, argv[1], argv[4]);
		if ((pipe(pipefd)) == -1)
			ft_perror("pipe", 1);
		processus(pipefd, fd, env, argv);
	}
	else
		ft_printf("The number of parameters is not valid\n");
	return (0);
}
