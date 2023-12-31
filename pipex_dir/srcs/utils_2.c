/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:27:04 by yachen            #+#    #+#             */
/*   Updated: 2023/09/13 12:26:23 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	cls_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_perror(char *str, int indice)
{
	if (indice == 1)
		perror("Error");
	if (str)
		ft_printf(": %s\n", str);
	exit(EXIT_FAILURE);
}

void	fork_error(int *pipefd, int *fd)
{
	cls_fd(pipefd);
	cls_fd(fd);
	ft_perror("fork", 1);
}

void	create_tmpinfile(int *fd)
{
	fd[0] = open("/tmp/tmpinfile", O_CREAT | O_RDONLY, 0644);
	if (fd[0] == -1)
		ft_perror("tmpinfile", 1);
}

void	open_fd(int *fd, char *infile, char *outfile)
{
	fd[0] = open(infile, O_RDONLY);
	if (fd[0] == -1)
	{
		perror("Error : ");
		create_tmpinfile(fd);
	}
	fd[1] = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		close(fd[0]);
		ft_perror(outfile, 1);
	}
}
