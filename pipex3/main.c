/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bing <bing@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:30:10 by bing              #+#    #+#             */
/*   Updated: 2023/08/22 12:18:10 by bing             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		f1;
	int		f2;
	char	**path;
	char	**cmd;
	
	if (argc < 5)
		print_error("Error : Please, enter more arguments\n");
	f1 = open(argv[1], O_RDONLY);
	if (f1 == -1)
		ft_perror("Error : open fd failed ");
	f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 == -1)
	{
		close(f1);
		ft_perror("Error : open fd failed ");
	}
	path = make_path(find_var_path(env));
	if (!path)
		clsfd_exit_error(f1, f2, "Error : PATH not found ");
	cmd = make_cmd_tab(argc, argv);
	if (!cmd)
		clsfd_exit_error(f1, f2, "Error : command shell false ");
	processus(path, cmd, f1, f2);
	return (0);
}
