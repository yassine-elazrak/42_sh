/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:23:39 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 23:33:34 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_addtohastable(char **args)
{
	int		rval;
	int		i;
	char	*file;

	i = 0;
	rval = 0;
	while (args[i])
	{
		if ((file = getfullpath(args[i])))
			ft_addtohashmap(args[i], file, COMMANDS);
		else if ((rval = 1))
			ft_printf_fd(2, "42sh: hash: %s: not found\n", args[i]);
		i++;
		free(file);
	}
	return (rval);
}

int		ft_hash(char **args)
{
	int		i;
	char	options[127];

	if (!args[0])
		return (ft_print_hash_list());
	if ((i = ft_getopt(args, options, "r")) < 0)
	{
		ft_printf_fd(2, "42sh: hash: -%c: invalid option\n", -i);
		ft_printf_fd(2, "42sh: usage: hash [-r] name [name ...]\n");
		return (1);
	}
	if (options['r'])
		ft_empty(COMMANDS);
	return (ft_addtohastable(args + i));
}
