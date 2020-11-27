/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_copy_paste_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:34:26 by oherba            #+#    #+#             */
/*   Updated: 2019/12/24 15:24:27 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_refrech(t_init *init)
{
	int	i;

	i = init->s_cursor;
	init->s.selection = 0;
	tputs(tgetstr("sc", NULL), 0, my_putchar);
	home_cursor(init);
	ft_printf("\033[%dD", (int)ft_strlen(init->promt));
	init->s_cursor = i;
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	ft_putstr_fd(&init->out_put[0], 1);
	tputs(tgetstr("rc", NULL), 0, my_putchar);
}

void	ft_init_s_00(t_init *init)
{
	init->s.cp = 0;
	init->s.cpd = 0;
	init->s.pass = 0;
	init->s.cp_end = 0;
	init->s.cp_st = 0;
	init->s.s_t = 0;
}

void	ft_del_str(t_init *init, int a)
{
	int i;

	i = 0;
	while (i < a)
	{
		del_char_of_line(&init->out_put, init);
		i++;
	}
}

void	ft_move(t_init *init, char *str, int a)
{
	int	i;

	i = -1;
	while (++i < a)
		ft_move_mul_line(init, str);
}
