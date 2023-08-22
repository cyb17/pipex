/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:02:07 by yachen            #+#    #+#             */
/*   Updated: 2023/08/15 13:58:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./libft/libft.h"

void	clean_resource(char **tab, char **path, int pipefd, int f);
void	error_execve(char **tab, char **path, int pipefd, int f);
void	closefd_and_error(int f1, int f2, char *str);
void	closepipe_and_error(int pipefd, char *str);
char	**make_path(void);
int		find_execute_cmd(char **path, char **cmd);
void	child_proc(int *f1, char *cmd, int *pipe);
void	parent_proc(int *f2, char *cmd, int *pipe);
void	processus(char **argv, int *f1, int *f2);

#endif