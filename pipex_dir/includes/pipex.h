/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:45:02 by yachen            #+#    #+#             */
/*   Updated: 2023/11/03 16:01:37 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../../libft/libft.h"

// utils_2
void	cls_fd(int *fd);
void	ft_perror(char *str, int indice);
void	fork_error(int *pipefd, int *fd);
void	create_tmpinfile(int *fdin);
void	open_fd(int *fd, char *infile, char *outfile);

// utils_1
int		tab_strjoin(char **tab, char *str);
char	**make_cmd(char *str);
char	**find_path(char **env, char *cmd);

// parsing_cmd
int		check_cmd(char *cmd);
char	*sub_parsing_cmd1(char **split_cmd);
char	*sub_parsing_cmd2(char **env_main, char **env_exev, char *cmd);
char	*parsing_cmd(char **env_main, char *cmd, char **env_exev);

// main
void	child1(int *fd, int *pipefd, char **env, char *cmd_str);
void	child2(int *fd, int *pipefd, char **env, char *cmd_str);
void	processus(int *pipefd, int *fd, char **env, char**argv);

#endif