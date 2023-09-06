/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:28:34 by yachen            #+#    #+#             */
/*   Updated: 2023/09/06 15:50:15 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX__BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "./libft/libft.h"
# include "pipex.h"

void	wait_proces(int j, int *pid, int nb_proces);
int		ft_compare(char *limiter, char *str);
int		ft_here_doc(char *limiter);
void	open_fd_bonus(int fd[], char ***argv, char *outfile, int *argc);
void	child_procs(int *input, int *output, char **env, char *argv_value);
pid_t	procs_fdin(int *fd, int *pipefd, char **env, char *argv_value);
pid_t	procs_fdout(int *pipefd, int *fd, char **env, char *argv_value);
pid_t	procs_pipe(int i, int pipefd[][2], char **env, char *argv_value);

#endif