/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 21:24:55 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/18 21:24:58 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*new_str;

	if (!(new_str = (char *)malloc(sizeof(char) * n + 1)))
		return (0);
	ft_strncpy(new_str, s1, n);
	return (new_str);
}
