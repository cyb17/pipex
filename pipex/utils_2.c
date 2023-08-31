/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:27:04 by yachen            #+#    #+#             */
/*   Updated: 2023/08/31 15:27:14 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cls_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_perror(char *str)
{
	perror("Error");
	if (str)
		ft_printf(": %s\n", str);
	exit(EXIT_FAILURE);
}

void	fork_error(int *pipefd, int *fd)
{
	cls_fd(pipefd);
	cls_fd(fd);
	ft_perror("fork");
}

/* open infile and outfile, EXIT_FAILURE if file can't be opened */
void	open_fd(int *fd, char *infile, char *outfile)
{
	fd[0] = open(infile, O_RDONLY);
	if (fd[0] == -1)
		ft_perror(infile);
	fd[1] = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		close(fd[0]);
		ft_perror(outfile);
	}
}
