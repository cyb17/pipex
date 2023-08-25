/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:02:39 by yachen            #+#    #+#             */
/*   Updated: 2023/08/25 14:13:31 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	print_error(char *str)
{
	ft_printf("%s", str);
	exit(EXIT_FAILURE);
}

void	clsfd_exit_error(int inf, int ouf, int *pid ,char *str)
{
	close(inf);
	close(ouf);
	if (!pid)
		free(pid);
	if (!str)
		perror(str);
	exit(EXIT_FAILURE);
}
