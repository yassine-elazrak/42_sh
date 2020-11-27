/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:51:04 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 13:54:57 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_hash_calc(char *key)
{
	int hash;
	int i;

	hash = 0;
	i = 0;
	while (key[i])
	{
		hash += key[i] * (i + 1);
		i++;
	}
	return (hash % COUNT);
}

void		ft_get_kv(char *str, char **key, char **val)
{
	int		len;
	int		i;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			*key = ft_strsub(str, 0, i);
			*val = ft_strsub(str, i + 1, len);
			return ;
		}
		i++;
	}
	*key = ft_strdup(str);
	*val = NULL;
	return ;
}
