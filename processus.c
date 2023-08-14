/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:20:50 by yachen            #+#    #+#             */
/*   Updated: 2023/08/14 16:42:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_closepipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_error(int *f1, int *f2, char *str)
{
	close(*f1);
	close(*f2);
	perror("!Error :");
	ft_printf("%s", str);
	exit(EXIT_FAILURE);
}

void	ft_error2(int *pipe)
{
	close(*pipe);
	exit(EXIT_FAILURE);
}
char	**make_path(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	**path;

	s1 = "/mnt/nfs/homes/yachen/bin/:/usr/local/sbin/:/usr/local/bin/:/usr/sbin/:";
	s2 = "/usr/bin/:/sbin/:/bin/:/usr/games/:/usr/local/games/:/snap/bin/";
	s3 = ft_strjoin(s1, s2);
	path = ft_split(s3, ':');
	free(s3);
	return (path);
}
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n",tab[i]);
		i++;
	}
}

void	find_execute_cmd(char **path, char **cmd)
{
	int	i;
	int	j;
	char	*tmp;

	j = 0;
	while (path[j])
	{
		tmp = path[j];
		path[j] = ft_strjoin(path[j], cmd[0]);
		free(tmp);
		j++;
	}
	i = 0;
	while (path[i] && execve(path[i], cmd, NULL) == -1)
		i++;
}

void	child_proc(int *f1, char *cmd, int *pipe)
{
	char	**tab;
	char	**path;
		
	close(pipe[0]);
	if (dup2(*f1, STDIN_FILENO) < 0 || dup2(pipe[1], STDOUT_FILENO) < 0)
		ft_error2(pipe + 1);
	tab = ft_split(cmd, ' ');
	if (!tab)
		ft_error2(pipe + 1);
	path = make_path();
	if (!path)
	{
		free_tab(tab);
		ft_error2(pipe + 1);
	}
	find_execute_cmd(path, tab);
	close(pipe[1]);
	free_tab(tab);
	free_tab(path);
	exit(EXIT_SUCCESS);
		
}

void	parent_proc(int *f2, char *cmd, int *pipe)
{
	char 	**tab;
	char	**path;
	int		status;

	waitpid(-1, &status, 0);
	close(pipe[1]);
	if (dup2(pipe[0], STDIN_FILENO) < 0 || dup2(*f2, STDOUT_FILENO) < 0)
		ft_error2(pipe + 0);
	tab = ft_split(cmd, ' ');
	if (!tab)
		ft_error2(pipe + 0);
	path = make_path();
	if (!path)
	{
		free_tab(tab);
		ft_error2(pipe + 0);
	}
	find_execute_cmd(path, tab);
	close(pipe[0]);
	free_tab(tab);
	free_tab(path);
	exit(EXIT_SUCCESS);
	
}

void	processus(char **argv, int *f1, int *f2)
{
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1)
		ft_error(f1, f2, "pipe");
	pid = fork();
	if (pid < 0)
	{
		ft_closepipe(pipefd);
		ft_error(f1, f2, "fork");
	}
	else if (pid == 0)
		child_proc(f1, argv[2], pipefd);
	else
		parent_proc(f2, argv[3], pipefd);
}