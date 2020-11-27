/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 21:15:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/18 10:48:04 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_type(char **args)
{
	int		i;
	char	*file;
	char	*err;
	int		rval;

	i = 0;
	rval = 0;
	while (args[i])
	{
		if (ft_is_builtin(args[i]))
			ft_printf("%s is a shell builtin\n", args[i]);
		else if ((file = ft_getvlaue_bykey(args[i], ALIAS)))
			ft_printf("%s is alias for %s\n", args[i], file);
		else if ((file = ft_getvlaue_bykey(args[i], COMMANDS)))
			ft_printf("%s is hashed (%s)\n", args[i], file);
		else if ((file = ft_findfile(args[i], &err, 0)))
			ft_printf("%s is %f\n", args[i], file);
		else
		{
			rval = 1;
			ft_printf("42sh: type %s: not found\n", args[i]);
		}
		i++;
	}
	return (rval);
}
