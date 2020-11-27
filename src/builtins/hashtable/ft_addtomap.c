/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addtomap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:52:00 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 13:32:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_cpy(t_map *map)
{
	t_shell	*shell;
	t_map	*cpy;
	t_list	*node;

	shell = get_shell_cfg(0);
	if (shell->tmpvars)
	{
		cpy = ft_memalloc(sizeof(t_map));
		cpy->key = ft_strdup(map->key);
		cpy->value = ft_strdup(map->value);
		cpy->type = map->type;
		cpy->exported = map->exported;
		cpy->hits = 0;
		node = ft_lstnew(cpy, 0);
		ft_lstadd(&shell->newmaps, node);
	}
}

t_map		*ft_addtohashmap(char *key, char *value, char type)
{
	t_map	*map;
	int		index;
	t_list	*l;

	if ((map = ft_getbykey(key, type)))
		free(map->value);
	else
	{
		map = malloc(sizeof(t_map));
		map->key = ft_strdup(key);
		index = ft_hash_calc(key);
		map->exported = 0;
		l = ft_lstnew(map, 0);
		ft_lstadd(&get_shell_cfg(0)->hashmap[index], l);
	}
	map->type = type;
	map->hits = 0;
	map->value = ft_strdup(value);
	if (type == INTERN && get_shell_cfg(0)->tmpvars)
		ft_cpy(map);
	if (ft_strequ(key, "PATH"))
		ft_empty(COMMANDS);
	return (map);
}
