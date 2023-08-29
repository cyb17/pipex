/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:02:07 by yachen            #+#    #+#             */
/*   Updated: 2023/08/29 16:13:14 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "./libft/libft.h"

void	cls_pipe(int *fd);
void	ft_perror(void);
char	**child_process(char *infile, int *fd, char *argv);
char	**parent_process(char *outfile, int *fd, char *argv);
int		tab_strjoin(char **tab, char *str);
char	**make_cmd(char *str);
char	**find_path(char **env, char **cmd);
char	*find_execute_path(char **env, char **cmd);
void	execute_cmd(char *path, char **cmd, int *fd);
void	sub_main(char **env, char *path, char **cmd, int *fd);

#endif