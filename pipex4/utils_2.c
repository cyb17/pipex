/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:10:40 by yachen            #+#    #+#             */
/*   Updated: 2023/08/25 14:11:20 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_execute_cmd(char **path, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], cmd[0]);
		free(tmp);
		if (execve(path[i], cmd, NULL) == -1)
			i++;
		else
			break ;
	}
	if (path[i] == NULL)
		return (-1);
	return (0);
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

void	child_3(char **env, char *str, int *pipefd)
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	if (sub_child(env, str) == -1)
	{
		close(pipefd[0]);
		perror("Error : command not found ");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}
