/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:02:07 by yachen            #+#    #+#             */
/*   Updated: 2023/08/24 14:14:50 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "./libft/libft.h"

void	ft_perror(char *str);
void	print_error(char *str);
void	clsfd_exit_error(int inf, int ouf, char *str);
char	*find_var_path(char **env);
char	**make_path(char *var_path);
char	**make_cmd(char *str);
void	free_cmd_tab(char ***cmd_tab);
char	***make_cmd_tab(int argc, char **argv);
int		find_execute_cmd(char **path, char **cmd);
int		count_child(char **cmd);
void	wait_all_procs(int i, int *pid);
void	clean_ressource(char **path, char **cmd, int inf, int outf);
void	processus(char **path, char **cmd, int inf, int outf);

#endif