/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:08:32 by yachen            #+#    #+#             */
/*   Updated: 2023/08/14 16:41:10 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	error(void)
{
	perror("!Error : open");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int	f1;
	int	f2;

	if (argc == 5)
	{
		f1 = open(argv[1], O_RDONLY);
		if (f1 == -1)
			error();
		f2 = open(argv[4], O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (f2 == -1 || access(argv[4], F_OK | W_OK | R_OK) == -1)
		{
			close(f1);
			error();
		}
		processus(argv, &f1, &f2);
		close(f1);
		close(f2);
	}
	else
		ft_printf("Error : The program needs 4 parameters !");
	return (0);
}
