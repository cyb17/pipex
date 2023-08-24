/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:30:10 by bing              #+#    #+#             */
/*   Updated: 2023/08/24 15:29:00 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		f1;
	int		f2;
	
	if (argc < 5)
		print_error("Error : Please, enter correct number of arguments \n");
	f1 = open(argv[1], O_RDONLY);
	if (f1 == -1)
		ft_perror("Error : open infile failed ");
	f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 == -1)
	{
		close(f1);
		ft_perror("Error : open outfile failed ");
	}
	processus(env, argv, f1, f2);
	return (0);
}
