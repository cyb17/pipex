/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:55:26 by yachen            #+#    #+#             */
/*   Updated: 2023/09/06 14:20:21 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_here_doc(char *limiter)
{
	char	*line;
	int		here_doc;

	here_doc = open("/tmp/here_doc", O_CREAT | O_RDWR, 0644);
	if (here_doc == -1)
		ft_perror("here_doc", 1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			close(here_doc);
			ft_perror("here_doc", 0);
		}
		write(here_doc, line, ft_strlen(line) + 1);
		if (ft_compare(limiter, line) == 1)
		{
			close(here_doc);
			free(line);
			break;
		}
		free(line);
		close(here_doc);
	}
}

void	open_fd_bonus(int fd[], char ***argv, char *outfile, int *argc)
{
	char	*infile;
	int		indice;
	
	infile = argv[0][1];
	indice = ft_strcmp("here_doc", argv[0][1]);
	if (indice == 1)
	{
		ft_here_doc(argv[0][2]);
		infile = "/tmp/here_doc";
		fd[1] = open(outfile, O_CREAT | O_RDWR , 0644);
	}
	else
		fd[1] = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[1] == -1)
		ft_perror(outfile, 1);
	fd[0] = open(infile, O_RDONLY);
	if (fd[0] == -1)
	{
		close(fd[1]);
		ft_perror(infile, 1);
	}
	if (indice == 0)
		return ;
	*argv = *argv + 1;
	(*argc)--;
}
