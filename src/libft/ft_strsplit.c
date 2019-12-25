/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 00:31:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/02/12 11:18:35 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char *str, char c)
{
	int index;
	int count;

	count = 0;
	index = 0;
	while (str[index])
	{
		if (str[index++] == c)
		{
			count++;
			while (str[index] == c)
				index++;
		}
	}
	count += ft_strlen(str) ? 1 : 0;
	return (count);
}

static void	ft_fill(char *str, char **arr, char c)
{
	int i;
	int element;
	int start;

	i = 0;
	start = 0;
	element = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			arr[element] = ft_strsub(str, start, i - start);
			start = i + 1;
			while (str[i + 1] == c)
			{
				i++;
				start = i + 1;
			}
			element++;
		}
		if (!str[i + 1])
			arr[element] = ft_strsub(str, start, i - start + 1);
		i++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		count;
	char	*str;

	array = NULL;
	if (s)
	{
		if (!(str = ft_strctrim(s, c)))
			return (NULL);
		count = ft_count(str, c);
		if (!(array = ft_memalloc(sizeof(char *) * (count + 1))))
			return (NULL);
		ft_fill(str, array, c);
		free(str);
		str = NULL;
	}
	return (array);
}
