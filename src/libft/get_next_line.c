/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:49:37 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/25 15:38:53 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_endl(char *str, char n)
{
	ssize_t pos;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == n)
			return (pos);
		pos++;
	}
	return (-1);
}

int		ft_norm(char **line, char **array)
{
	char	*tmp;

	tmp = *line;
	*line = *array;
	if (tmp)
		free(tmp);
	if (!**array)
	{
		*line = NULL;
		return (0);
	}
	if (*array)
		free(*array);
	*array = NULL;
	return (0);
}

int		ft_adjust(char **line, char **array, int pos)
{
	char *tmp;

	if (pos >= 0)
	{
		tmp = *line;
		*line = ft_strsub(*array, 0, pos);
		if (tmp)
			free(tmp);
		tmp = *array;
		*array = ft_strdup(*array + pos + 1);
		free(tmp);
	}
	else
		return (ft_norm(line, array));
	return (1);
}

int		get_next_line(const int fd, char n, char **line)
{
	static char *array;
	ssize_t		lenght;
	ssize_t		pos;
	char		*tmp;

	if (!array)
		array = ft_strnew(1);
	if ((pos = ft_endl(array, n)) == -1)
	{
		*line = ft_strnew(BUFF_SIZE);
		while ((lenght = read(fd, *line, BUFF_SIZE)) > 0)
		{
			(*line)[lenght] = '\0';
			tmp = array;
			array = ft_strjoin(array, *line);
			free(tmp);
			if ((pos = ft_endl(array, n)) >= 0)
				break ;
		}
		if (lenght < 0)
			return (-1);
	}
	return (ft_adjust(line, &array, pos));
}
