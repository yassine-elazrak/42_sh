/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:49:19 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 13:55:04 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft__check(t_list *prev, int type, int i)
{
	t_map	*map;
	t_list	*tmp;
	t_list	*list;

	list = get_shell_cfg(0)->hashmap[i];
	map = list->content;
	tmp = list->next;
	if (type == ANYHASH || map->type == type)
	{
		free(map->key);
		free(map->value);
		free(map);
		free(list);
		if (prev)
			prev->next = tmp;
		else
			get_shell_cfg(0)->hashmap[i] = tmp;
	}
}

void		ft_empty(char type)
{
	int		i;
	t_list	*list;
	t_list	*tmp;
	t_list	*prev;

	i = -1;
	while (++i < COUNT)
	{
		list = get_shell_cfg(0)->hashmap[i];
		prev = NULL;
		while (type && list)
		{
			tmp = list->next;
			ft__check(prev, type, i);
			list = tmp;
		}
		if (type == 0 || type == ANYHASH)
			get_shell_cfg(0)->hashmap[i] = NULL;
	}
}
