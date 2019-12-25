/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getoperators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:30:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/05 13:31:01 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_getoperator_id(char *oper, char type)
{
	char	**ops;
	int		i;

	ops = ft_getset(0)->test_operators;
	i = 0;
	while (ops[i])
	{
		if (ft_strequ(ops[i], oper))
		{
			if ((i < 16 && type == BINARY) || (i >= 16 && type == UNARY))
			{
				ft_printf_fd(2, "42sh: test: %s: %snary operator expected\n",
					oper, type == BINARY ? "bi" : "u");
				return (0);
			}
			return (i);
		}
		i++;
	}
	if (type == BINARY)
		ft_printf_fd(2, "42sh: test: %s: binary operator expected\n", oper);
	else if (type == UNARY)
		ft_printf_fd(2, "42sh: test: %s: unary operator expected\n", oper);
	return (0);
}

int		ft_getoprators(char **args, char **l_oper, char **oper, char **r_oper)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (!*l_oper)
			*l_oper = args[i];
		else if (!*oper)
			*oper = args[i];
		else if (!*r_oper)
			*r_oper = args[i];
		else
		{
			ft_printf_fd(2, "42sh: test: too many arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}
