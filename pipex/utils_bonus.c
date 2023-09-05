/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:55:26 by yachen            #+#    #+#             */
/*   Updated: 2023/09/05 16:43:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_pipe_and_fd(int j, int *fd, int pipefd[][2], int nb_pipe)
{
	int	i;
	
	i = 0;
	while (i < nb_pipe && i < j)
		cls_fd(pipefd[i++]);
	cls_fd(fd);
}

void	wait_proces(int j, int *pid, int nb_proces)
{
	int	i;
	int	status;
	
	i = 0;
	while (i < nb_proces && i < j)
		waitpid(pid[i++], &status, 0);
}

int	ft_compare(char *limiter, char *str)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] != str[i])
			return (0);
		i++;
	}
	if (limiter[i] == '\0' && str[i] == '\n')
		return (1);
	return (0);
}

int	ft_here_doc(char *limiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_compare(limiter, line) == 1)
		{
			free(line);
			break;
		}
		free(line);
	}
	return (STDIN_FILENO);
}

int	open_fd_bonus(int fd[], char ***argv, char *outfile, int *argc)
{

	if (ft_strcmp("here_doc", argv[0][1]))
	{
		fd[0] = ft_here_doc(argv[0][2]);
		fd[1] = open(outfile, O_CREAT | O_RDWR , 0644);
		if (fd[1] == -1)
		{
			close(fd[0]);
			ft_perror(outfile, 1);
		}
		(*argc)--;
		*argv = *argv + 3;
		return (1);
	}
	fd[0] = open(argv[0][1], O_RDONLY);
	if (fd[0] == -1)
		ft_perror(argv[0][1], 1);
	fd[1] = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		close(fd[0]);
		ft_perror(outfile, 1);
	}
	*argv = *argv + 2;
	return (0);
}
