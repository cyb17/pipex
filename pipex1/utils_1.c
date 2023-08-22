/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:36:39 by yachen            #+#    #+#             */
/*   Updated: 2023/08/15 14:09:42 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_resource(char **tab, char **path, int pipefd, int f)
{
	close(f);
	close(pipefd);
	free_tab(path);
	free_tab(tab);
}
void	error_execve(char **tab, char **path, int pipefd, int f)
{
	clean_resource(tab, path, pipefd, f);
	perror("Error : execve");
	exit(EXIT_FAILURE);
}

void	closefd_and_error(int f1, int f2, char *str)
{
	close(f1);
	close(f2);
	perror("!Error :");
	ft_printf("%s", str);
	exit(EXIT_FAILURE);
}

void	closepipe_and_error(int pipefd, char *str)
{
	close(pipefd);
	perror("!Error :");
	ft_printf("%s", str);
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

int	find_execute_cmd(char **path, char **cmd)
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
	if (path[i] == NULL)
		return (-1);
	return (0);
}
