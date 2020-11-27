/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:19:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 09:33:25 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_function	*ft_is_builtin(char *arg)
{
	t_map	*map;
	int		i;

	i = 0;
	while (i < BUILTINS_COUNT)
	{
		map = &get_shell_cfg(0)->builtins[i];
		if (ft_strequ(map->key, arg))
			return (map->value);
		i++;
	}
	return (NULL);
}

void		ft_addbuiltin(char *name, void *ptr)
{
	int		i;
	t_map	*blt;

	blt = get_shell_cfg(0)->builtins;
	i = 0;
	while (i < BUILTINS_COUNT)
	{
		if (!blt[i].key)
		{
			blt[i].key = name;
			blt[i].value = ptr;
			break ;
		}
		i++;
	}
}

void		ft_addblt(void)
{
	ft_addbuiltin("echo", ft_echo);
	ft_addbuiltin("cd", ft_cd);
	ft_addbuiltin("export", ft_export);
	ft_addbuiltin("set", ft_set);
	ft_addbuiltin("hash", ft_hash);
	ft_addbuiltin("jobs", ft_jobs);
	ft_addbuiltin("fg", ft_fg);
	ft_addbuiltin("bg", ft_bg);
	ft_addbuiltin("unset", ft_unset);
	ft_addbuiltin("exit", ft_exit);
	ft_addbuiltin("type", ft_type);
	ft_addbuiltin("alias", ft_alias);
	ft_addbuiltin("unalias", ft_unalias);
	ft_addbuiltin("test", ft_test);
	ft_addbuiltin("fc", ft_fc);
}

void		ft_init_builtins(char **env)
{
	char	*key;
	char	*value;
	t_shell	*shell;
	t_map	*mp;
	int		i;

	ft_init_hash();
	while (*env)
	{
		ft_get_kv(*env, &key, &value);
		if ((mp = ft_addtohashmap(key, value, INTERN)))
			mp->exported = 1;
		free(key);
		free(value);
		env++;
	}
	shell = get_shell_cfg(0);
	i = 0;
	while (i < BUILTINS_COUNT)
		shell->builtins[i++].key = NULL;
	ft_addblt();
	ft_getset(0)->test_operators = ft_strsplit("\127,-b,-c,-d,-e,-f,-L,-p,-S,\
-u,-g,-r,-w,-x,-s,-z,=,!=,-eq,-ne,-ge,-lt,-le,-gt", ',');
	ft_setoprations();
}
