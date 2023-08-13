/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:21:36 by yachen            #+#    #+#             */
/*   Updated: 2023/05/15 14:06:49 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate_s;
	int		i;

	i = 0;
	duplicate_s = (char *)malloc(sizeof(*duplicate_s) * (ft_strlen(s) + 1));
	if (!duplicate_s)
		return (NULL);
	while (s[i])
	{
		duplicate_s[i] = s[i];
		i++;
	}
	duplicate_s[i] = '\0';
	return (duplicate_s);
}
/*
#include <stdio.h>

int	main()
{
	char	s[] = "chat";
	char	*duplicate_s;
	duplicate_s = ft_strdup(s);
	printf("%s", duplicate_s);
	free(duplicate_s);
}*/
