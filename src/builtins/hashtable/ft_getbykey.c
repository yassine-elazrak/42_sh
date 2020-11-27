/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getbykey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:48:43 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 16:45:03 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_map		*ft_getbykey(char *key, char type)
{
	int		index;
	t_list	**l;
	t_list	*nodelist;
	t_map	*map;

	if (!key)
		return (NULL);
	if ((index = ft_hash_calc(key)) < 0)
		return (NULL);
	l = get_shell_cfg(0)->hashmap;
	nodelist = l[index];
	while (nodelist)
	{
		map = nodelist->content;
		if (map->type == type && ft_strequ(map->key, key))
			return (map);
		nodelist = nodelist->next;
	}
	return (NULL);
}

char		*ft_getvlaue_bykey(char *key, char type)
{
	t_map	*map;

	if ((map = ft_getbykey(key, type)))
	{
		map->hits++;
		return (map->value);
	}
	return (NULL);
}
