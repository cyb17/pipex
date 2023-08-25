/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:29:29 by yachen            #+#    #+#             */
/*   Updated: 2023/08/25 15:18:07 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_clean(int f1, int f2, int *pipefd)
{
	close(f1);
	close(f2);
	close(pipefd[1]);
	close(pipefd[0]);
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
		clsfd_exit_error(f1, f2, NULL, "Error : int *pid malloc failed ");
	i = 0;
	while (i < procs)
	{	
		pid[i] = fork();
		ft_printf("fork : %d\n", pid[i]);
		if (pid[i] == -1)
			clsfd_exit_error(f1, f2, pid, "Error : fork ");
		if (pid[i] == 0 && i == 0)
			child_1(env, argv[i + 2], f1, pipefd);
		else if (pid[i] == 0 && i == procs - 1)
			child_2(env, argv[i + 2], f2, pipefd);
		else if (pid[i] == 0)
		{
			ft_printf("test\n");
			child_3(env, argv[i + 2], pipefd);
		}
		i++;
	}
	ft_clean(f1, f2, pipefd);
	wait_all_procs(procs);
}
