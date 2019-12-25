/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mul_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:58:05 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/22 17:55:18 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_cal_c(t_init *init, int *k, int *i)
{
	int			a;

	a = 0;
	if ((init->s_col - ((*k) % init->s_col)) > (init->s_col % 8))
	{
		if ((((*k) + 1) % init->s_col) != 0 && (((*k)) % init->s_col) != 0)
			a = (8 - (((*k) % init->s_col) % 8));
	}
	else
	{
		if ((((*k) + 1) % init->s_col) != 0 && (((*k)) % init->s_col) != 0)
			a = (init->s_col - ((*k) % init->s_col)) - 1;
	}
	(*i) += a;
	(*k) += a;
	return (1);
}

int				get_strat(t_init *init, int e_d)
{
	int			i;
	int			a;
	int			j;
	int			k;

	i = 0;
	a = 0;
	k = 0;
	j = e_d;
	while (0 < j && init->out_put[j - 1] != '\n')
		j--;
	while (j <= e_d)
	{
		if (init->out_put[j] == '\t')
			a = ft_cal_c(init, &k, &i);
		if (!a)
		{
			i++;
			k++;
		}
		a = 0;
		j++;
	}
	return (i);
}

static void		ft_move__r(t_init *init, char *str)
{
	(init->s_cursor)++;
	while ((init->out_put[init->s_cursor] &&
			init->out_put[init->s_cursor - 1] == '\t' &&
			(ft_tab_(init, init->s_cursor - 2) == 0)) ||
(init->out_put[init->s_cursor] == '\t' &&
(get_strat(init, init->s_cursor - 1)) % init->s_col == 0))
		init->s_cursor++;
	if ((get_strat(init, init->s_cursor) - 1) % init->s_col == 0)
		ft_printf("\033[%dB\033[%dD", 1, init->s_col - 1);
	else if (init->out_put[(init->s_cursor - 1)] == '\n')
		ft_printf("\033[%dB\033[%dD",
1, (get_strat(init, init->s_cursor - 2)) % init->s_col);
	else if (init->out_put[(init->s_cursor - 1)] == '\t')
	{
		if (ft_tab_(init, init->s_cursor - 2) > 0)
			ft_printf("\033[%dC", ft_tab_(init, init->s_cursor - 2));
	}
	else
		tputs(tgetstr("nd", NULL), 0, my_putchar);
	if (init->s.selection == 1)
		ft_put_clor(init, str);
}

void			ft_move_help(t_init *init, char *str)
{
	if (init->out_put[(init->s_cursor)] == '\t')
	{
		if (ft_tab_(init, init->s_cursor - 1) > 0)
			ft_printf("\033[%dD", ft_tab_(init, init->s_cursor - 1));
	}
	else if (init->out_put[(init->s_cursor)] == '\n')
	{
		ft_printf("\033[%dA", 1);
		if ((get_strat(init, init->s_cursor - 1)))
			ft_printf("\033[%dC",
(get_strat(init, init->s_cursor - 1)) % init->s_col);
	}
	else
		tputs(tgetstr("le", NULL), 0, my_putchar);
	if (init->s.selection == 1)
		ft_put_clor(init, str);
}

void			ft_move_mul_line(t_init *init, char *str)
{
	if (ft_strcmp(str, "+") == 0)
		ft_move__r(init, str);
	else if (ft_strcmp(str, "-") == 0)
	{
		(init->s_cursor)--;
		while ((init->out_put[init->s_cursor] &&
				init->out_put[init->s_cursor] == '\t' &&
				(ft_tab_(init, init->s_cursor - 1) == 0)) ||
(init->out_put[init->s_cursor] == '\t' &&
				(get_strat(init, init->s_cursor - 1)) % init->s_col == 0))
			init->s_cursor--;
		ft_move_help(init, str);
	}
}
