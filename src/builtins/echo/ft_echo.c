/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 22:53:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/15 18:03:40 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_echo(char **args)
{
	int		i;
	char	endl;
	int		status;

	endl = 1;
	i = 0;
	status = 0;
	if (ft_strequ(args[0], "-n"))
	{
		endl = 0;
		i++;
	}
	while (!status && args[i])
	{
		if (args[i + 1])
			status += ft_printf("%s ", args[i]);
		else
			status += ft_putstr(args[i]);
		i++;
	}
	if (status)
		ft_printf_fd(2, "42sh: echo: write error: Bad file descriptor\n");
	else if (endl)
		ft_putchar('\n');
	return (status);
}
