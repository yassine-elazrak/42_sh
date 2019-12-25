/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:21:04 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/24 14:30:08 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			del_char_of_line(char **line, t_init *init)
{
	char			*t_line;
	char			*t_2_line;

	t_line = *line;
	if (!(init->s_l > (int)ft_strlen(init->promt) &&\
	init->s_cursor > (int)ft_strlen(init->promt)))
		return ;
	ft_move(init, "-", 1);
	(init->s_cursor)++;
	t_2_line = ft_strsub(t_line, 0, init->s_cursor - 1);
	*line = ft_strjoin(t_2_line, &t_line[init->s_cursor]);
	tputs(tgetstr("sc", NULL), 0, my_putchar);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	ft_putstr_fd(&t_line[init->s_cursor], 1);
	tputs(tgetstr("rc", NULL), 0, my_putchar);
	(init->s_l)--;
	(init->s_cursor)--;
	ft_strdel(&t_2_line);
	ft_strdel(&t_line);
}

void			ft_init_output(t_init *init)
{
	ft_strdel(&init->out_put);
	init->s_cursor = ft_strlen(init->promt);
	init->s_l = ft_strlen(init->promt);
	init->skip_read = 0;
	init->qoute = 0;
	init->qt = '\0';
	init->z0 = 0;
	init->s.selection = 0;
	if (init->promt)
		init->out_put = ft_strdup(init->promt);
	else
		init->out_put = ft_strdup("(42)>");
	if (!g_sig)
		ft_putstr_fd(init->out_put, 1);
}

static void		ft_key__65(char *str, t_init *init)
{
	(void)str;
	(void)init;
	if (init->history_postoin != NULL && init->history_postoin->prvet)
		init->history_postoin = init->history_postoin->prvet;
	else if (init->z0 == 0)
		init->history_postoin = init->last_history;
	if (init->history_postoin)
	{
		home_cursor(init);
		ft_printf("\033[%dD", (int)ft_strlen(init->promt));
		ft_init_output(init);
		tputs(tgetstr("cd", NULL), 0, my_putchar);
		ft_str_line(init->history_postoin->str, init);
		init->z0 = 1;
	}
}

static void		ft_key__66(char *str, t_init *init)
{
	(void)str;
	if (init->history_postoin != NULL && init->history_postoin->next)
	{
		init->history_postoin = init->history_postoin->next;
		home_cursor(init);
		ft_printf("\033[%dD", (int)ft_strlen(init->promt));
		ft_init_output(init);
		tputs(tgetstr("cd", NULL), 0, my_putchar);
		if (init->history_postoin)
			ft_str_line(init->history_postoin->str, init);
	}
}

int				key_4_of_cursor(char *str, t_init *init)
{
	if (str[2] == 65)
	{
		ft_key__65(str, init);
		return (1);
	}
	if (str[2] == 67)
	{
		if (init->s_l > init->s_cursor)
			ft_move_mul_line(init, "+");
		return (1);
	}
	if (str[2] == 66)
	{
		ft_key__66(str, init);
		return (1);
	}
	if (str[2] == 68)
	{
		if (init->s_cursor > (int)ft_strlen(init->promt))
			ft_move_mul_line(init, "-");
		return (1);
	}
	return (0);
}
