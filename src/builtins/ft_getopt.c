/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 10:31:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/23 13:28:16 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_check(char *arg, char *valid, char *buffer)
{
	int i;
	int option;

	i = 0;
	while (arg[i])
	{
		if (!ft_strchr(valid, arg[i]))
			return (-arg[i]);
		if ((option = (int)arg[i]) > 0)
			buffer[option] = 1;
		i++;
	}
	return (0);
}

int		ft_getopt(char **args, char *buffer, char *valid)
{
	int		i;
	int		c;

	i = 0;
	ft_bzero(buffer, 127);
	while (args[i])
	{
		if (ft_strequ(args[i], "--"))
			return (i + 1);
		if (args[i][0] == '-' && args[i][1])
		{
			if ((c = ft_check(args[i] + 1, valid, buffer)) < 0)
				return (c);
		}
		else
			return (i);
		i++;
	}
	return (i);
}
