/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:29:29 by yachen            #+#    #+#             */
/*   Updated: 2023/08/25 14:26:30 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			child_3(env, argv[i + 2], pipefd);
		i++;
	}
	wait_all_procs(procs);
}
