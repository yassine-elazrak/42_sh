/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_builtin_completion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:42:34 by oherba            #+#    #+#             */
/*   Updated: 2019/12/24 19:58:19 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_auto		*ft_get_completion_built_42(t_init *init, t_auto **lst)
{
	int		len;
	int		i;
	char	**alias;

	i = 0;
	len = ft_strlen(init->to_complete);
	while (i < BUILTINS_COUNT)
	{
		if (ft_strncmp(get_shell_cfg(0)->builtins[i].key,
			init->to_complete, len) == 0)
			*lst = add_to_auto_42(*lst, get_shell_cfg(0)->builtins[i].key);
		i++;
	}
	alias = ft_getaliaskeys();
	i = 0;
	while (alias && alias[i])
	{
		if (ft_strncmp(alias[i], init->to_complete, len) == 0)
			*lst = add_to_auto_42(*lst, alias[i]);
		i++;
	}
	ft_free_array(alias);
	return (*lst);
}

char		ft_keyexist(t_auto *lst, char *key)
{
	while (lst)
	{
		if (ft_strequ(lst->str, key))
			return (1);
		lst = lst->next;
	}
	return (0);
}

t_auto		*add_to_auto_42(t_auto *lst, char *str)
{
	t_auto	*new;
	t_auto	*tmp;

	if (ft_keyexist(lst, str))
		return (lst);
	tmp = lst;
	if (lst == NULL)
	{
		new = malloc(sizeof(t_auto) * 1);
		new->str = ft_strdup(str);
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	else
	{
		while (lst->next)
			lst = lst->next;
		new = malloc(sizeof(t_auto) * 1);
		new->str = ft_strdup(str);
		new->next = NULL;
		new->prev = lst;
		lst->next = new;
		return (tmp);
	}
}

char		**ft_catpath(void)
{
	char	**array;
	char	*path;

	array = NULL;
	path = ft_getenv("PATH");
	if (!path)
		return (NULL);
	array = ft_strsplit(path, ':');
	return (array);
}

t_auto		*ft_get_completion_path_42(t_init *init)
{
	t_auto			*lst;
	char			**str;
	DIR				*dir;
	struct dirent	*drt;
	char			**tmp;

	lst = NULL;
	str = ft_catpath();
	if (!(tmp = str))
		return (NULL);
	while (*str)
	{
		if (!(dir = opendir(*str)))
			return (NULL);
		while ((drt = readdir(dir)))
		{
			if (!ft_strncmp(drt->d_name, init->to_complete,
					ft_strlen(init->to_complete)))
				lst = add_to_auto_42(lst, drt->d_name);
		}
		closedir(dir);
		str++;
	}
	ft_free_array(tmp);
	return (lst);
}
