/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:29:29 by yachen            #+#    #+#             */
/*   Updated: 2023/08/24 15:57:06 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_1(char **env, char **argv, int inf, int *pipefd)
{
	
}

void	processus(char **env, char **argv, int f1, int f2)
{
	int		pipefd[2];
	int		procs;
	pid_t	*pid;
	int		i;

	pipe(pipefd);
	procs = 2;
	while (argv[i + 1])
		i++;
	procs -= 2;
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
			child_1(env, argv, f1, pipefd);
		else if (pid[i] == 0 && i == procs - 2);
			child_2(env, argv, f2, pipefd);
		else if (pid[i] == 0)
			child_3(env, argv, pipefd);
		i++;
	}	
	
}
