/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:14:45 by yachen            #+#    #+#             */
/*   Updated: 2023/08/30 16:39:13 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_fd(int *fd, char *infile, char *outfile)
{
	fd[0] = open(infile, O_RDONLY);
	if (fd[0] == -1)
		ft_perror(infile);
	fd[1] = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		close(fd[0]);
		ft_perror(outfile);
	}
}

static char	*parsing_cmd(char **env, char *cmd)
{
	char	**split_cmd;
	char	**env_path;
	char	*path;
	int		i;
	
	split_cmd = make_cmd(cmd);
	path = NULL;
	if (cmd[0] == '/')
	{
		if (access(split_cmd[0], F_OK | R_OK | X_OK) == -1)
			ft_printf("Error: %s: no such file or directory\n", split_cmd[0]);
		else
			path = ft_strdup(split_cmd[0]);
		free_tab(split_cmd);
		return (path);
	}
	env_path = find_path(env, split_cmd[0]);
	i = 0;
	while (env_path[i] && access(env_path[i], F_OK | R_OK | X_OK) == -1)
		i++;
	if (!env_path[i])
		ft_printf("Error: %s: Command not found\n", split_cmd[0]);
	else
		path = ft_strdup(env_path[i]);
	free_tab(split_cmd);
	free_tab(env_path);
	return (path);
}

void	sub_child1(int *fd, int *pipefd, char **env, char *cmd_str)
{
	char	*path;
	char	**cmd;
	
	path = parsing_cmd(env, cmd_str);
	if (!path)
		return ;
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		cls_fd(fd);
		cls_fd(pipefd);
		ft_perror(NULL);
	}
	cmd = make_cmd(cmd_str);
	close(fd[0]);
	close(pipefd[0]);
	if (execve(path, cmd, NULL) == -1)
		perror("Error");
}

void	sub_child2(int *fd, int *pipefd, char **env, char *cmd_str)
{
	char	*path;
	char	**cmd;
	
	path = parsing_cmd(env, cmd_str);
	if (!path)
		return ;
	if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
	{
		cls_fd(fd);
		cls_fd(pipefd);
		ft_perror(NULL);
	}
	cmd = make_cmd(cmd_str);
	close(fd[1]);
	close(pipefd[1]);
	if (execve(path, cmd, NULL) == -1)
		perror("Error");
}

void	child_process(char **env, char **argv)
{
	int		pipefd[2];
	int		fd[2];
	int		status;
	pid_t	pid;
	
	open_fd(fd, argv[1], argv[4]);
	if ((pipe(pipefd)) == -1)
		ft_perror(NULL);
	pid = fork();
	if (pid == -1)
	{
		cls_fd(pipefd);
		cls_fd(fd);
		ft_perror(NULL);
	}
	else if (pid == 0)
		sub_child1(fd, pipefd, env, argv[2]);
	else
		sub_child2(fd, pipefd, env, argv[3]);
	waitpid(pid, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		status;
	
	if (argc == 5)
	{
		pid = fork();
		if (pid == -1)
			ft_perror(NULL);
		else if (pid == 0)
			child_process(env, argv);
		else
			waitpid(pid, &status, 0);
	}
	else
		ft_printf("The number of parameters is not valid\n");
	return (0);
}
