/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:28:34 by yachen            #+#    #+#             */
/*   Updated: 2023/09/08 16:57:21 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "../includes/pipex.h"

typedef struct s_tab
{
	int		**pipefd;
	pid_t	*pid;
	int		fd[2];
}			t_tab;
void	wait_proces(int j, int *pid, int nb_proces);
int		ft_compare(char *limiter, char *str);
void	ft_here_doc(char *limiter);
void	open_fd_bonus(int fd[], char ***argv, char *outfile, int *argc);
int		creat_pipefd(int i, int argc, int **pipefd);
void	ft_init_tab(t_tab *tab, int argc);
void	free_tab_int(t_tab *tab, int argc);
void	child_procs(int *input, int *output, char **env, char *argv_value);
pid_t	procs_fdin(int *fd, int *pipefd, char **env, char *argv_value);
pid_t	procs_fdout(int *pipefd, int *fd, char **env, char *argv_value);
pid_t	procs_pipe(int *fd, int **pipefd, char **env, char *argv_value);

#endif