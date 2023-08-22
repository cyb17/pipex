/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:08:32 by yachen            #+#    #+#             */
/*   Updated: 2023/08/19 10:44:57 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	open_error(void)
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
			open_error();
		f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (f2 == -1)
		{
			close(f1);
			open_error();
		}
		processus(argv, &f1, &f2);
	}
	else
		ft_printf("Error : The program needs 4 parameters !");
	return (0);
}
