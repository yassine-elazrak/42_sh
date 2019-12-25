/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 00:33:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/19 13:46:58 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	ft_isintern(char *cmd)
{
	char	*key;
	char	*value;
	int		rval;

	rval = 0;
	if (!ft_strchr(cmd, '='))
		return (0);
	ft_get_kv(cmd, &key, &value);
	free(value);
	if (ft_isdigit(key[0]) || !ft_isalphanum(key))
		rval = 1;
	free(key);
	return (rval);
}
