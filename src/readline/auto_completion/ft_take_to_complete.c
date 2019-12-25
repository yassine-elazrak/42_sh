/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_to_complete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 14:55:41 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 16:56:57 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_move_left_word(t_init *init, char *tmp)
{
	char	c;

	if (tmp[init->s_cursor] == BLANK)
	{
		if (init->s_cursor > (int)ft_promptlen(init->promt))
		{
			init->s_cursor--;
			tputs(tgetstr("le", NULL), 0, my_putchar);
		}
	}
	c = tmp[init->s_cursor];
	while (init->s_cursor > (int)ft_promptlen(init->promt) &&
		c != BLANK && c != PIPE && c != OR &&
		c != AND && c != SEMI_COL && c != BG)
	{
		if (init->s_cursor > (int)ft_promptlen(init->promt))
		{
			init->s_cursor--;
			tputs(tgetstr("le", NULL), 0, my_putchar);
		}
		c = tmp[init->s_cursor];
	}
}

void	ft_move_right_word(t_init *init, char *tmp)
{
	char	c;

	c = tmp[init->s_cursor];
	if (c == BLANK || c == PIPE || c == OR ||
		c == AND || c == SEMI_COL || c == BG)
	{
		if (init->s_cursor < init->s_l)
		{
			init->s_cursor++;
			tputs(tgetstr("nd", NULL), 0, my_putchar);
		}
	}
	c = tmp[init->s_cursor];
	while (init->s_cursor < init->s_l &&
		c != BLANK && c != PIPE && c != OR &&
		c != AND && c != SEMI_COL && c != BG)
	{
		if (init->s_cursor < init->s_l)
		{
			init->s_cursor++;
			tputs(tgetstr("nd", NULL), 0, my_putchar);
		}
		c = tmp[init->s_cursor];
	}
}

void	ft_move_by_word(int flg, t_init *init)
{
	char	*tmp;

	tmp = ft_strdup(init->out_put);
	mark_operators(tmp);
	mark_bg_op(tmp);
	if (flg == 1)
		ft_move_left_word(init, tmp);
	else if (flg == 4)
		ft_move_right_word(init, tmp);
	ft_strdel(&tmp);
}

char	*ft_take_to_complte_42(t_init *init)
{
	char	*str;
	int		start;
	int		end;

	str = NULL;
	ft_move_by_word(1, init);
	start = init->s_cursor;
	ft_move_by_word(4, init);
	end = init->s_cursor;
	if (start != (int)ft_promptlen(init->promt))
	{
		start += 1;
		str = ft_strsub(init->out_put, start, end - start);
	}
	else
		str = ft_strsub(init->out_put, start, end - start);
	return (str);
}
