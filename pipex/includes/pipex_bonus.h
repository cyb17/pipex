/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:28:34 by yachen            #+#    #+#             */
/*   Updated: 2023/09/09 14:18:20 by yachen           ###   ########.fr       */
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
	int		fdin;
	int		fdout;
	int		nb_pipe;
}			t_tab;

// utils1_bonus
int		ft_compare(char *limiter, char *str);
void	ft_here_doc(char *limiter);
void	open_fd_bonus(t_tab *tab, char ***argv, char *outfile, int *argc);
int		creat_pipefd(int i, int argc, int **pipefd);

// utils2_bonus
void	ft_init_tab(t_tab *tab, int argc);
void	free_tab_int(t_tab *tab);
void	close_pipefd(int **pipefd, int nb_pipe, int i);
void	clean_all(t_tab *tab, int i, int indice);
void	wait_proces(int j, int *pid, int nb_proces);

// child_procs_step
char	*child_procs_part_1(int i, t_tab *tab, char **env, char *argv_value);
void	child_procs_part_2(int i, t_tab *tab, int input, int output);
void	child_procs_part_3(char *path, char *argv_value);

// fork_case
pid_t	procs_fdin(int i, t_tab *tab, char **env, char *argv_value);
pid_t	procs_pipe(int i, t_tab *tab, char **env, char *argv_value);
pid_t	procs_fdout(int i, t_tab *tab, char **env, char *argv_value);

#endif