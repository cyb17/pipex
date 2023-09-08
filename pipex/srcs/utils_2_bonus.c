/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:02:53 by yachen            #+#    #+#             */
/*   Updated: 2023/09/08 16:22:22 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_tab_int(t_tab *tab, int argc)
{
	int	i;

	i = 0;
	if (tab->pid)
		free(tab->pid);
	while (i < argc - 4)
	{
		if (tab->pipefd[i])
			free(tab->pipefd[i]);
		i++;
	}
	free(tab->pipefd);
}

void	ft_init_tab(t_tab *tab, int argc)
{
	int	i;

	i = 0;
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
			free_tab_int(tab, argc);
			ft_perror("Error : tab_pipefd\n", 0);
		}
		i++;
	}
}
