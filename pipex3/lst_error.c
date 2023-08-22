/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bing <bing@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:02:39 by yachen            #+#    #+#             */
/*   Updated: 2023/08/21 16:36:31 by bing             ###   ########.fr       */
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

void	clsfd_exit_error(int inf, int ouf, char *str)
{
	close(inf);
	close(ouf);
	perror(str);
	exit(EXIT_FAILURE);
}
