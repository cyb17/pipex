/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bing <bing@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:02:07 by yachen            #+#    #+#             */
/*   Updated: 2023/08/28 10:39:24 by bing             ###   ########.fr       */
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
void	clsfd_exit_error(int inf, int ouf, int *pid, char *str);
char	*find_var_path(char **env);
char	**make_path(char *var_path);
char	**make_cmd(char *str);
int		count_procs(char **argv);
int		find_execute_cmd(char **path, char **cmd);
int		sub_child(char **env, char *str);
void	child_1(char **env, char *str, int inf, int *pipefd);
void	child_2(char **env, char *str, int outf, int *pipefd);
void	child_3(char **env, char *str, int *fdin, int *fdout);
void	processus(char **env, char **argv, int f1, int f2);
void	wait_all_procs(int procs);

#endif