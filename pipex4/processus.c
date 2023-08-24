/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bing <bing@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:29:29 by yachen            #+#    #+#             */
/*   Updated: 2023/08/24 23:14:20 by bing             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_execute_cmd(char **path, char **cmd)
{
	int	i;

	i = 0;
	while (path[i] && execve(path[i], cmd, NULL) == -1)
		i++;
	if (path[i] == NULL)
	{
		ft_printf("Error : command not found\n");
		return (-1);
	}
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
		if (make_path2(path, cmd[0]) == -1)
			return (-1);
		if (find_execute_cmd(path[i], cmd) == -1)
			return (-1);
	}
}

void	child_1(char **env, char *str, int inf, int *pipefd)
{

}

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

void	processus(char **env, char **argv, int f1, int f2)
{
	int		pipefd[2];
	int		procs;
	pid_t	*pid;
	int		i;

	pipe(pipefd);
	procs = count_procs(argv);
	pid = (int *)malloc(sizeof(int) * procs);
	if (!pid)
		return ;
	i = 0;
	while (i < procs)
	{	
		pid[i] = fork();
		if (!pid[i])
		{
			close(f1);
			close(f2);
			ft_perror("Error : fork");
		}
		else if (pid[i] == 0 && i == 0)
			child_1(env, argv[i + 2], f1, pipefd);
		else if (pid[i] == 0 && i == procs - 2)
			child_2(env, argv[i + 2], f2, pipefd);
		else if (pid[i] == 0)
			child_3(env, argv[i + 2], pipefd);
		i++;
	}	
}
