/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepeat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 06:18:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 13:54:21 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrepeat(char const *str, size_t count)
{
	char	*new;
	size_t	len;

	new = NULL;
	if (str && count > 0)
	{
		len = ft_strlen(str) * count + 1;
		if ((new = ft_memalloc(len)) == NULL)
			return (NULL);
		while (count--)
		{
			ft_strcat(new, str);
		}
	}
	return (new);
}
