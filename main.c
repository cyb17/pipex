/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:01:39 by yachen            #+#    #+#             */
/*   Updated: 2023/08/13 13:50:08 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
	int	fd1;
	int	fd2;
	
	fd1 = 0;
	fd2 = 0;
	if (argc == 5)
	{
		parsing(argv, &fd1, &fd2);
		processus(argv, &fd1, &fd2);
		close(fd1);
		close(fd2);
	}
	else
		ft_printf("Error : The program needs 4 parameters !");
	return (0);
}