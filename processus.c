/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:12:50 by yachen            #+#    #+#             */
/*   Updated: 2023/08/13 14:15:20 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc(char *cmd, int *f)
{
	char	**tab_cmd;

	tab_cmd = ft_split(cmd, " ");
	if (!tab_cmd)
	{
		perror("Error ft_split ");
		exit(EXIT_FAILURE);
	}
	execve()
	
}

void	processus(char **argv, int *fd1, int *fd2)
{
	int	f[2];
	int		value;

	if (pipe(f) == -1)
		return (perror("Error: pipe "));
	value = fork();
	if (value < 0)
		return (perror("Error: fork "));
	else if (value == 0)
		child_proc(argv[2], f);
	else
		parent_proc()
}