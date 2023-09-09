/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:02:53 by yachen            #+#    #+#             */
/*   Updated: 2023/09/09 14:17:23 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_tab_int(t_tab *tab)
{
	int	i;

	i = 0;
	if (tab->pid)
		free(tab->pid);
	while (i < tab->nb_pipe)
	{
		if (tab->pipefd[i])
			free(tab->pipefd[i]);
		i++;
	}
	if (tab->pipefd)
		free(tab->pipefd);
}

void	ft_init_tab(t_tab *tab, int argc)
{
	int	i;

	i = 0;
	tab->nb_pipe = argc - 4;
	tab->pid = (int *)malloc(sizeof(int) * (argc - 3));
	if (!(tab->pid))
		ft_perror("Error : tab_pid\n", 0);
	tab->pipefd = (int **)malloc(sizeof(int *) * (argc - 4));
	if (!(tab->pipefd))
	{
		free(tab->pid);
		ft_perror("Error : tab_pipefd\n", 0);
	}
	while (i < argc -4)
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(tab->pipefd[i]))
		{
			free_tab_int(tab);
			ft_perror("Error : tab_pipefd\n", 0);
		}
		i++;
	}
}

void	close_pipefd(int **pipefd, int nb_pipe, int i)
{
	int	j;

	j = 0;
	while (j <= i && j < nb_pipe)
		cls_fd(pipefd[j++]);
}

void	clean_all(t_tab *tab, int i, int indice)
{
	close(tab->fdin);
	close(tab->fdout);
	close_pipefd(tab->pipefd, tab->nb_pipe, i);
	if (indice == 1)
		free_tab_int(tab);
}

void	wait_proces(int j, int *pid, int nb_proces)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_proces && i < j)
		waitpid(pid[i++], &status, 0);
}
