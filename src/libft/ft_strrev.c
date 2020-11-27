/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 05:21:18 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/17 05:22:43 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	lenght;
	char	tmp;
	size_t	i;

	lenght = ft_strlen(str);
	i = 0;
	while (i < lenght)
	{
		tmp = str[i];
		str[i] = str[lenght - 1];
		str[lenght - 1] = tmp;
		i++;
		lenght--;
	}
	return (str);
}
