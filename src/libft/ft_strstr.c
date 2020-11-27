/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 05:47:25 by sid-bell          #+#    #+#             */
/*   Updated: 2019/02/23 22:24:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*str;
	size_t	needle_lenght;
	size_t	haystack_lenght;
	int		i;

	i = 0;
	needle_lenght = ft_strlen(needle);
	haystack_lenght = ft_strlen(haystack);
	while (haystack_lenght >= needle_lenght)
	{
		if (!(str = ft_strsub(haystack, i, needle_lenght)))
			return (NULL);
		haystack_lenght = ft_strlen(str);
		if (!ft_strncmp(str, needle, needle_lenght))
		{
			free(str);
			return ((char *)haystack + i);
		}
		free(str);
		i++;
	}
	return (NULL);
}
