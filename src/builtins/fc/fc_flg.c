/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_flg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:48:00 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/22 19:29:23 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					ft_printerror(void)
{
	ft_printf("42sh : fc: history specification out of range\n");
	return (-1);
}

static int			get_index_nm(char *key)
{
	t_history		*tmp;

	tmp = get_shell_cfg(0)->init->last_history;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, key, ft_strlen(key)) == 0)
			return (tmp->index);
		tmp = tmp->prvet;
	}
	return (-1);
}

void				ft_sawap(int *s, int *e)
{
	int				a;

	if (*s > *e)
	{
		a = *s;
		*s = *e;
		*e = a;
	}
}

int					get_start_end(int *s, int *e, char **args)
{
	if (args[0] && ft_isdigit(args[0][0]))
		*s = ft_atoi(args[0]);
	else if (args[0])
		*s = get_index_nm(args[0]);
	else
	{
		if (get_shell_cfg(0)->init->last_history->index > 16)
			*s = get_shell_cfg(0)->init->last_history->index - 15;
		else
			*s = get_shell_cfg(0)->init->history->index;
	}
	if (*s < 0)
		return (ft_printerror());
	if (args[0] && args[1] && ft_isdigit(args[1][0]))
		*e = ft_atoi(args[1]);
	else if (args[0] && args[1])
		*e = get_index_nm(args[1]);
	else
		*e = get_shell_cfg(0)->init->last_history->index;
	if (*e < 0)
		return (ft_printerror());
	ft_sawap(s, e);
	return (0);
}
