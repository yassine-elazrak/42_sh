/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:34:50 by oherba            #+#    #+#             */
/*   Updated: 2019/12/22 17:55:47 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		home_cursor(t_init *init)
{
	while (init->s_cursor > (int)ft_strlen(init->promt))
		ft_move(init, "-", 1);
}

void		end_cursor(t_init *init)
{
	while (init->s_cursor < init->s_l)
		ft_move(init, "+", 1);
}

void		home_cursor_2(t_init *init)
{
	if (init->s_cursor > (int)ft_strlen(init->promt) &&
init->out_put[init->s_cursor - 1] == '\n')
		ft_move(init, "-", 1);
	while (init->s_cursor > (int)ft_strlen(init->promt) &&
init->out_put[init->s_cursor - 1] != '\n')
		ft_move(init, "-", 1);
}

void		end_cursor_2(t_init *init)
{
	if (init->s_cursor < init->s_l && init->out_put[init->s_cursor] == '\n')
		ft_move(init, "+", 1);
	while (init->s_cursor < init->s_l && init->out_put[init->s_cursor] != '\n')
		ft_move(init, "+", 1);
}

int			my_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}
