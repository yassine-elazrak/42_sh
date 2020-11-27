/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:43:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 22:04:39 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_free_kv(char *key, char *val)
{
	free(val);
	free(key);
	return (1);
}

static int	ft_check(char *key, char *value)
{
	if (ft_isdigit(key[0]) || !ft_isalphanum(key))
	{
		ft_printf("42sh: export: '%s': not a valid identifier\n", key);
		return (ft_free_kv(key, value));
	}
	return (0);
}

static int	ft__export__(int export, char *arg)
{
	t_map	*map;
	char	*key;
	char	*value;

	ft_get_kv(arg, &key, &value);
	if (ft_check(key, value))
		return (1);
	else
	{
		if (!export)
		{
			if ((map = ft_getbykey(key, INTERN)))
			{
				map->exported = 1;
				value = ft_strdup(map->value);
			}
			else
				return (0);
		}
		ft_addtohashmap(key, value, INTERN)->exported = 1;
	}
	ft_free_kv(key, value);
	return (0);
}

int			ft_export(char **args)
{
	int		i;
	char	export;
	int		rvalue;
	char	buffer[127];

	if (!args || !args[0])
		return (ft_printenv(NULL));
	if ((i = ft_getopt(args, buffer, "p")) < 0)
	{
		ft_printf_fd(2, "42sh: export: -%c: invalid option\n", -i);
		ft_printf_fd(2,
				"42sh: usage: export [-p] [name[=value] ...]\n");
		return (1);
	}
	if (buffer['p'])
		return (ft_printenv(buffer));
	rvalue = 0;
	while (args[i])
	{
		export = ft_strchr(args[i], '=') ? 1 : 0;
		if (ft__export__(export, args[i]))
			rvalue = 1;
		i++;
	}
	return (rvalue);
}
