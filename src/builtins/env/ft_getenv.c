/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:34:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 14:39:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*ft_getenv(char *key)
{
	return (ft_getvlaue_bykey(key, INTERN));
}

static int		ft_condition(t_map *map, int exported)
{
	return (map->type == INTERN &&
		(exported & INCLUDE_UNEXPORTED ||
		(exported & EXPORTED_ONLY && map->exported)));
}

static size_t	ft_envcount(char exported)
{
	size_t	count;
	int		i;
	t_list	*lst;
	t_map	*map;

	i = 0;
	count = 0;
	while (i < COUNT)
	{
		lst = get_shell_cfg(0)->hashmap[i];
		while (lst)
		{
			map = lst->content;
			if (ft_condition(map, exported))
				count++;
			lst = lst->next;
		}
		i++;
	}
	return (count);
}

char			**ft_serialize_env(char exported)
{
	int		i;
	t_list	*lst;
	t_map	*map;
	char	**env;
	int		index;

	i = -1;
	env = ft_memalloc(sizeof(char *) * (ft_envcount(exported) + 1));
	index = 0;
	while (++i < COUNT)
	{
		lst = get_shell_cfg(0)->hashmap[i];
		while (lst)
		{
			map = lst->content;
			if (ft_condition(map, exported))
			{
				env[index++] = ft_join(exported & KEYS_ONLY ? "%s" : "%s=%s",
					map->key, map->value);
			}
			lst = lst->next;
		}
	}
	env[index] = NULL;
	return (env);
}
