/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 22:10:48 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 10:17:30 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	char	*str;

	str = NULL;
	if (s)
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
		index = 0;
		while (index < len && s[index + start])
		{
			str[index] = s[index + start];
			index++;
		}
		str[index] = '\0';
	}
	return (str);
}
