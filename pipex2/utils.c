/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:24:26 by yachen            #+#    #+#             */
/*   Updated: 2023/08/19 14:34:48 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	while (*env && ft_strncmp(*env, "PATH", 4) != 0)
		env++;
	return (*env);
}

char	**make_cmd_tab(int argc, char **argv)
{
	int		i;
	char	**cmd_tab;

	cmd_tab = (char **)malloc(sizeof(char *) * argc);
	if (!cmd_tab)
		return (NULL);
	i = 1;
	while (i < argc - 1)
	{
		cmd_tab[i - 1] = ft_strdup(argv[i]);
		if (!cmd_tab[i - 1] || cmd_tab[i - 1] == '\0')
		{
			ft_printf("Error : cmd_tab");
			free_tab(cmd_tab);
			return (NULL);
		}
		i++;
	}
	return (cmd_tab);
}