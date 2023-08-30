/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:02:07 by yachen            #+#    #+#             */
/*   Updated: 2023/08/30 16:37:09 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "./libft/libft.h"

void	cls_fd(int *fd);
void	ft_perror(char *str);
int		tab_strjoin(char **tab, char *str);
char	**make_cmd(char *str);
char	**find_path(char **env, char *cmd);
char	*find_execute_path(char **env, char **cmd);
void	execute_cmd(char *path, char **cmd, int *fd);
void	open_fd(int *fd, char *infile, char *outfile);
void	sub_child1(int *fd, int *pipefd, char **env, char *cmd_str);
void	sub_child2(int *fd, int *pipefd, char **env, char *cmd_str);
void	child_process(char **env, char **argv);

#endif