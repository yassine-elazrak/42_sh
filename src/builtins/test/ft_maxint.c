/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maxint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 20:25:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 20:27:37 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_checklen(char *nb)
{
	if (ft_strlen(nb) > 19)
	{
		ft_printf("42sh: test: %s: integer expression expected\n", nb);
		return (2);
	}
	return (0);
}

int			ft_maxinteger(char *nb, int sign)
{
	int		i;
	int		n1;
	int		n2;

	if (ft_checklen(nb))
		return (2);
	else if (ft_strlen(nb) == 19)
	{
		i = -1;
		while (++i < 19)
		{
			n1 = MAXNBR[i] - '0';
			n2 = nb[i] - '0';
			if (n2 > n1)
			{
				if (i == 18 && sign && n2 == 8)
					return (0);
				ft_printf("42sh: test: %s: integer expression expected\n", nb);
				return (2);
			}
			else if (n1 > n2)
				return (0);
		}
	}
	return (0);
}
