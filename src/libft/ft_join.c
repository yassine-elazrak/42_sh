/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:49:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 20:48:02 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_readpipe(int fd)
{
	char	line[1024];
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	ft_bzero(line, 1024);
	while (read(fd, line, 1023) > 0)
	{
		if (str)
		{
			tmp = ft_strjoin(str, line);
			free(tmp);
		}
		else
			str = ft_strdup(line);
		ft_bzero(line, 1024);
	}
	return (str);
}

char		*ft_join(char *f, ...)
{
	int		p[2];
	va_list	v;
	char	*str;

	va_start(v, f);
	pipe(p);
	ft_vprintf(p[1], &v, f);
	close(p[1]);
	va_end(v);
	str = ft_readpipe(p[0]);
	close(p[0]);
	return (str);
}
