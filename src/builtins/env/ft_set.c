/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:25:32 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 19:45:49 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_set(void)
{
	int		i;
	t_list	*l;
	t_list	**lst;
	t_map	*map;

	i = 0;
	lst = get_shell_cfg(0)->hashmap;
	while (i < COUNT)
	{
		l = lst[i];
		while (l)
		{
			map = l->content;
			if (map->type == INTERN)
				ft_printf_fd(1, "%s=%s\n", map->key, map->value);
			l = l->next;
		}
		i++;
	}
	return (0);
}

int			ft_unset(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		ft_hashdelete_one(args[i], INTERN);
		i++;
	}
	return (0);
}
