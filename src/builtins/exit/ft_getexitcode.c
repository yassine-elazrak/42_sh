/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getexitcode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:57:35 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 19:26:00 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_sign(int *n1sign, char **n1)
{
	char	*tmp;

	if (**n1 == '-' || **n1 == '+')
	{
		if (**n1 == '-')
			*n1sign = 1;
		tmp = ft_strdup(*n1 + 1);
		free(*n1);
		*n1 = tmp;
	}
}

char		ft_exitcode(char *nbr, uint8_t *code)
{
	int		n1signed;
	int		r;

	r = 0;
	ft_sign(&n1signed, &nbr);
	*code = 255;
	if (!(r = ft_maxinteger(nbr, n1signed)))
		*code = ft_atoi(nbr);
	free(nbr);
	return (r);
}
