/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:34:28 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/05 13:34:35 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_strtest(int id, char *l_oper, char *r_oper)
{
	if (id == 15)
	{
		if (!r_oper)
			return (0);
		return (*r_oper != 0);
	}
	if (id == 16)
		return (ft_strcmp(l_oper, r_oper));
	if (id == 17)
		return (ft_strequ(l_oper, r_oper));
	if (id == 18)
		return (ft_strequ(l_oper, r_oper));
	return (1);
}
