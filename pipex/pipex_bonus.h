/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:28:34 by yachen            #+#    #+#             */
/*   Updated: 2023/09/01 10:47:15 by yachen           ###   ########.fr       */
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

void	clear_pipefd(int *fd, int pipefd[][2], int nb_pipe);
void	wait_proces(int *pid, int nb_proces);
void	child_processus(int *input, int *output, char **env, char *argv_value);
pid_t	proces(int *input, int *output, char **env, char *argv_value);

#endif