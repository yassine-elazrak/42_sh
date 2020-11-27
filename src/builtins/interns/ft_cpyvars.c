/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyvars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:28:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 14:51:21 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_add(void)
{
	t_list	*next;
	t_list	*lst;
	t_map	*map;
	t_map	*mp;

	lst = get_shell_cfg(0)->newmaps;
	get_shell_cfg(0)->tmpvars = NULL;
	while (lst)
	{
		next = lst->next;
		map = lst->content;
		if ((mp = ft_addtohashmap(map->key, map->value, map->type)))
			mp->exported = mp->exported;
		free(map->key);
		free(map->value);
		free(map);
		free(lst);
		lst = next;
	}
	get_shell_cfg(0)->newmaps = NULL;
}

int		ft_gettmpvars(t_process *process, t_function *func)
{
	t_list	**saved;
	int		rval;

	saved = get_shell_cfg(0)->hashmap;
	get_shell_cfg(0)->hashmap = ft_cppyvars();
	ft_getinterns(process, ENV_ENTRY);
	get_shell_cfg(0)->tmpvars = saved;
	rval = func(process->arg + 1);
	ft_empty(ANYHASH);
	free(get_shell_cfg(0)->hashmap);
	get_shell_cfg(0)->hashmap = saved;
	ft_add();
	return (rval);
}

void	ft_cpymap(t_map *map, t_list **new, int i)
{
	t_map	*newmap;
	t_list	*newnode;

	newmap = ft_memalloc(sizeof(t_map));
	newmap->exported = map->exported;
	newmap->key = ft_strdup(map->key);
	newmap->value = ft_strdup(map->value);
	newmap->type = map->type;
	newnode = ft_lstnew(newmap, 0);
	ft_lstadd(&new[i], newnode);
}

t_list	**ft_cppyvars(void)
{
	t_list	**lst;
	int		i;
	t_list	*node;
	t_list	**new;
	t_map	*map;

	i = 0;
	lst = get_shell_cfg(0)->hashmap;
	new = ft_memalloc(sizeof(t_list *) * COUNT);
	while (i < COUNT)
	{
		node = lst[i];
		while (node)
		{
			map = node->content;
			ft_cpymap(map, new, i);
			node = node->next;
		}
		i++;
	}
	return (new);
}
