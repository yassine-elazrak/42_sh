/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:38:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 23:45:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list		*ft_getlist(void)
{
	int		i;
	t_list	*l;
	t_list	**lst;
	t_map	*map;
	t_list	*keys;

	keys = NULL;
	i = 0;
	lst = get_shell_cfg(0)->hashmap;
	while (i < COUNT)
	{
		l = lst[i];
		while (l)
		{
			map = l->content;
			if (map->type == ALIAS)
				ft_lstadd(&keys, ft_lstnew(map->key, 0));
			l = l->next;
		}
		i++;
	}
	return (keys);
}

char		**ft_getaliaskeys(void)
{
	t_list	*keys;
	int		len;
	char	**ptr;
	int		index;

	keys = ft_getlist();
	len = ft_lstcount(keys);
	if (len <= 0)
		return (NULL);
	ptr = ft_memalloc(sizeof(char *) * (len + 1));
	index = 0;
	while (keys)
	{
		ptr[index++] = ft_strdup(keys->content);
		keys = keys->next;
	}
	return (ptr);
}

int			ft_isvalid(char *key)
{
	if (!ft_isalphanum(key))
	{
		ft_printf_fd(2, "alias: '%s': invalid alias name\n", key);
		return (0);
	}
	return (1);
}

int			ft_alias(char **args)
{
	char	*key;
	char	*value;
	int		i;
	int		rval;

	i = -1;
	rval = 0;
	while (args[++i])
	{
		if (ft_strpos(args[i], "=") > 0)
		{
			ft_get_kv(args[i], &key, &value);
			if (!ft_isvalid(key))
				rval = 1;
			else
				ft_addtohashmap(key, value, ALIAS);
			free(key);
			free(value);
		}
		else
			ft_show_aliases(args[i]);
	}
	if (i == 0)
		ft_show_aliases(NULL);
	return (rval);
}
