/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:29:19 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/20 18:29:20 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_fstrjoin(char const *s1, char const *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free((char *)s1);
	free((char *)s2);
	return (str);
}
