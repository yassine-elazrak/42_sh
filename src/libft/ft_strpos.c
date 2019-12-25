/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 05:23:37 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/17 05:27:57 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strpos(char const *s1, char const *s2)
{
	char *str;

	if (!(str = ft_strstr(s1, s2)))
		return (-1);
	return (ft_strlen(s1) - ft_strlen(str));
}
