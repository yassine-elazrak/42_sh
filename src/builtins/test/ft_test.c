/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:09:56 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 23:38:35 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_inittest(char **p1, char **p2, char **p3)
{
	*p1 = NULL;
	*p2 = NULL;
	*p3 = NULL;
}

int		ft_dotest(char *oper, char *r_oper, char *l_oper)
{
	int id;

	if (!(id = ft_getoperator_id(oper, (l_oper && r_oper) ? BINARY : UNARY)))
		return (2);
	if (id < 9)
		return (ft_eval(id, r_oper));
	if (id == 10 || id == 9)
		return (ft_usergroup(id, r_oper));
	if (id == 11 || id == 12 || id == 13)
		return (ft_rwx(id, r_oper));
	if (id == 14)
		return (ft_sizetest(r_oper));
	if (id < 18)
		return (ft_strtest(id, l_oper, r_oper));
	return (ft_mathcmp(id, l_oper, r_oper));
}

int		ft_test(char **args)
{
	char	*oper;
	char	*l_oper;
	char	*r_oper;
	int		id;

	ft_inittest(&l_oper, &r_oper, &oper);
	if (!args[0] || !args[1])
		return (args[0] ? 0 : 1);
	if (ft_strequ(args[0], "!"))
	{
		id = ft_test(args + 1);
		return (!id);
	}
	if (ft_getoprators(args, &l_oper, &oper, &r_oper))
		return (2);
	if (!r_oper && oper)
	{
		r_oper = oper;
		oper = l_oper;
		l_oper = NULL;
	}
	return (ft_dotest(oper, r_oper, l_oper));
}
