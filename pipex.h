/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:02:07 by yachen            #+#    #+#             */
/*   Updated: 2023/08/14 15:00:42 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./libft/libft.h"

void	ft_closepipe(int *pipe);
void	ft_error(int *f1, int *f2, char *str);
void	ft_error2(int *pipe);
char	**make_path(void);
void	child_proc(int *f1, char *cmd, int *pipe);
void	parent_proc(int *f2, char *cmd, int *pipe);
void	processus(char **argv, int *f1, int *f2);
#endif