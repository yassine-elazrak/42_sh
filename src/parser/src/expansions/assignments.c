/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 09:58:28 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/24 10:02:42 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			**get_assignments(char ***args)
{
	int		pos;
	char	flag;
	int		size;
	t_arg	*h;
	t_arg	*t;

	pos = 0;
	h = NULL;
	t = NULL;
	size = 0;
	while (*args && **args)
	{
		quotes_delimiter(*args);
		flag = 1;
		if ((pos = ft_strpos(**args, "=")) != -1)
		{
			valid_assignment(**args, &flag, pos);
			if (!flag)
				size += expand_and_append(&h, &t, args);
		}
		if (flag)
			break ;
		(*args)++;
	}
	return (size ? convert_args(h, size) : NULL);
}
