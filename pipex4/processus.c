/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:29:29 by yachen            #+#    #+#             */
/*   Updated: 2023/08/28 14:48:02 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*static void	ft_clean(int f1, int f2, int **pipefd)
{
	int	i;

	close(f1);
	close(f2);
	i = 0;
	while (pipefd[i])
	{
		close(pipefd[i][1]);
		close(pipefd[i][0]);
		i++;
	}
}

int	**make_pipefd(int procs)
{
	int	**pipefd;
	int	i;

	pipefd = (int **)malloc(sizeof(int *) * procs);
	if (!pipefd)
		return (NULL);
	i = 0;
	while (pipefd[i])
	{
		pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipefd[i])
		{
			while (i >= 0)
				free(pipefd[i--]);
			free(pipefd);
			return (NULL);
		}
		i++;
	}
	return (pipefd);
}

void	processus(char **env, char **argv, int f1, int f2)
{
	int		**pipefd;
	int		procs;
	pid_t	*pid;
	int		i;

	procs = count_procs(argv);
	pipefd = make_pipefd(procs);
	if (!pipefd)
		clsfd_exit_error(f1, f2, NULL, "Error : int **pipefd malloc failed ");
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
			child_1(env, argv[i + 2], f1, pipefd[0]);
		else if (pid[i] == 0 && i == procs - 1)
			child_2(env, argv[i + 2], f2, pipefd[procs - 1]);
		else if (pid[i] == 0)
		{
			ft_printf("test\n");
			child_3(env, argv[i + 2], pipefd[i - 1], pipefd[i]);
		}
		i++;
	}
	ft_clean(f1, f2, pipefd);
	//wait_all_procs(procs);
}
*/
