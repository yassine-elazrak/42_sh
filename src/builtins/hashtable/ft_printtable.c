/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:53:01 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 14:02:43 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_printtable(t_map *map, char *first)
{
	if (map->type == COMMANDS)
	{
		if (*first)
		{
			*first = 0;
			ft_printf("hits\t command\n");
		}
		ft_printf("%3d\t %s\n", map->hits, map->value);
	}
}

int		ft_print_hash_list(void)
{
	int		i;
	t_list	*l;
	t_map	*map;
	char	first;

	i = -1;
	first = 1;
	while (++i < COUNT)
	{
		l = get_shell_cfg(0)->hashmap[i];
		while (l)
		{
			map = l->content;
			ft_printtable(map, &first);
			l = l->next;
		}
	}
	if (first)
		ft_printf("42sh: hash table empty\n");
	return (0);
}
