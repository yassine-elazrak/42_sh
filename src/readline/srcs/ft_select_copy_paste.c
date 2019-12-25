/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_copy_paste.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:16:14 by oherba            #+#    #+#             */
/*   Updated: 2019/12/07 18:35:47 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		key__slect_22(t_init *init, char *str)
{
	if (str[0] == -61 && str[1] == -97)
	{
		if (init->s.selection == 0)
			init->s.selection = 1;
		else
		{
			ft_refrech(init);
			init->s.selection = 0;
		}
		ft_init_s_00(init);
		init->s.s_t = init->s_cursor;
		return (1);
	}
	if (str[0] == -61 && str[1] == -89 && init->s.selection == 1)
	{
		init->s.selection = 0;
		init->s.cp = 1;
		ft_refrech(init);
		return (1);
	}
	return (0);
}

int				key_slect(char *str, t_init *init)
{
	if (key__slect_22(init, str))
		return (1);
	if (str[0] == -30 && str[1] == -119 && str[2] == -120)
	{
		init->s.selection = 0;
		init->s.cpd = 1;
		return (1);
	}
	if (str[0] == -30 && str[1] == -120 && str[2] == -102)
	{
		init->s.selection = 0;
		init->s.pass = 1;
		return (1);
	}
	return (0);
}

void			ft_copy_delete(t_init *init)
{
	int	i;

	i = init->s_cursor;
	if (init->s_cursor < init->s.s_t)
	{
		ft_move(init, "+", init->s.s_t - i);
		ft_del_str(init, init->s.s_t - i);
	}
	else
		ft_del_str(init, i - init->s.s_t);
}

void			ft_take_copy(t_init *init)
{
	ft_strdel(&init->tmp);
	if (init->s_cursor < init->s.s_t)
		init->tmp = ft_strsub(init->out_put, init->s_cursor,
				init->s.s_t - init->s_cursor);
	else
		init->tmp = ft_strsub(init->out_put, init->s.s_t,
				init->s_cursor - init->s.s_t);
}

void			ft_exec_ket_s(t_init *init)
{
	if (init->s.pass == 1 && init->tmp != NULL)
	{
		ft_print_(init->tmp, init);
		ft_refrech(init);
		ft_init_s_00(init);
	}
	if (init->s.cp == 1)
	{
		ft_take_copy(init);
		ft_init_s_00(init);
	}
	if (init->s.cpd == 1)
	{
		ft_take_copy(init);
		ft_copy_delete(init);
		ft_init_s_00(init);
	}
}
