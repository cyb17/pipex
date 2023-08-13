/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:17:00 by yachen            #+#    #+#             */
/*   Updated: 2023/08/13 13:37:40 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parsing(char **argv, int *fd1, int *fd2)
{
	*fd1 = open(argv[1], O_RDONLY);
	if (*fd1 == -1)
		ft_error();
	*fd2 = open(argv[4], O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*fd2 == -1 || access(argv[4], F_OK | W_OK | R_OK) == -1)
	{
		close(*fd1);
		ft_error();
	}
}