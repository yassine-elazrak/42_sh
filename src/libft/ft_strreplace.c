/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 01:07:25 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/16 01:07:28 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char const *s, char const *pattern, char const *replace)
{
	char	*result;
	char	*temp;
	char	*parts[2];
	int		lenghts[2];
	int		end;

	result = NULL;
	lenghts[0] = ft_strlen(s);
	lenghts[1] = ft_strlen(pattern);
	if (s && pattern)
	{
		if ((temp = ft_strstr(s, pattern)))
		{
			end = lenghts[0] - ft_strlen(temp);
			parts[0] = ft_strsub(s, 0, end);
			parts[1] = ft_strsub(s, end + lenghts[1], lenghts[0] - 1);
			if ((temp = ft_strreplace(parts[1], pattern, replace)))
			{
				parts[1] = temp;
			}
			result = ft_strjoin(parts[0], replace);
			result = ft_strjoin(result, parts[1]);
		}
	}
	return (result);
}
