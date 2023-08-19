/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:02:39 by yachen            #+#    #+#             */
/*   Updated: 2023/08/19 14:05:32 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	perror(ft_printf("%s", str));
	exit(EXIT_FAILURE);
}
void	argc_error(void)
{
	ft_printf("Error : Please, enter more arguments");
	exit(EXIT_FAILURE);
}

void	clsfd_exit_error(int inf, int ouf, char *str)
{
	close(inf);
	close(ouf);
	perror(ft_printf("%s", str));
	exit(EXIT_FAILURE);
}
