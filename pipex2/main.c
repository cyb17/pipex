/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:50:45 by yachen            #+#    #+#             */
/*   Updated: 2023/08/19 14:10:38 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		f1;
	int		f2;
	char	*path;
	char	**cmd_tab;
	
	if (argc < 5)
		argc_error();
	f1 = open(argv[1], O_RDONLY);
	if (f1 == -1)
		ft_error("Error : open fd failed");
	f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 == -1)
	{
		close(f1);
		ft_error("Error : open fd failed");
	}
	path = find_path(env);
	if (!path)
		clsfd_exit_error(f1, f2, "Error : path not found")
	cmd_tab = make_cmd_tab(argc, argv);
	if (!cmd_tab)
		clsfd_exit_error(f1, f2, "Error : cmd_tab");		
	processus(path, cmd_tab, f1, f2);
	return (0);
}
