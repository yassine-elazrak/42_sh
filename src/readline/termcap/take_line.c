/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 01:13:38 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 14:16:56 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_move__(t_init *init, char *str)
{
	(void)str;
	if (init->x0 + (get_strat(init, ft_strlen(init->out_put)) - \
	get_strat(init, init->s_cursor)) \
	% init->s_col >= init->s_col && init->y0 +
	(get_strat(init, ft_strlen(init->out_put)) - \
	get_strat(init, init->s_cursor)) / init->s_col >= init->s_line)
	{
		ft_printf("\033[%dS", 1);
		ft_printf("\033[%dA", 1);
	}
}

void			ft_get_pos_(t_init *init)
{
	char		buf[30];
	int			ret;
	char		ch;
	int			i;

	i = 0;
	ch = 0;
	write(1, "\033[6n", 4);
	ft_bzero(buf, 30);
	while (ch != 'R')
	{
		ch = 0;
		ret = read(0, &ch, 1);
		buf[i] = ch;
		i++;
	}
	if (ft_strchr(buf, '['))
		init->y0 = ft_atoi(ft_strchr(buf, '[') + 1);
	if (ft_strchr(buf, ';'))
		init->x0 = ft_atoi(ft_strchr(buf, ';') + 1);
}

int				ft_cat_of_line(char *str, t_init *init)
{
	char		*line;
	char		*temp;
	char		*t_line;

	if (init->out_put == NULL)
		init->out_put = ft_strnew(0);
	line = init->out_put;
	temp = ft_strsub(line, 0, init->s_cursor);
	t_line = ft_strjoin(temp, str);
	ft_strdel(&temp);
	init->out_put = ft_strjoin(t_line, &init->out_put[init->s_cursor]);
	ft_strdel(&t_line);
	ft_strdel(&line);
	init->s_cursor += ft_strlen(str);
	init->s_l = ft_strlen(init->out_put);
	return (0);
}

void			ft_str_line(char *str, t_init *init)
{
	char		*tmp;
	int			j;

	j = 0;
	ft_get_pos_(init);
	if (str[0] == 127)
		del_char_of_line(&init->out_put, init);
	else if (str && ft_strcmp(str, ""))
	{
		if (str[0] == -30 && str[1] == -128 && str[2] == -96)
			ft_strncpy(str, "\t", 2);
		while (str[j])
		{
			if (ft_isprint(str[j]) || str[j] == '\n' || (str[j] == '\t' &&
				(get_strat(init, init->s_cursor) % init->s_col != 0 ||
				(get_strat(init, init->s_cursor) - 1) % init->s_col != 0)))
			{
				tmp = ft_strsub(str, j, 1);
				ft_cat_string_of_line(init, tmp);
				ft_strdel(&tmp);
			}
			j++;
		}
	}
}

void			ft_cat_string_of_line(t_init *init, char *str)
{
	char		*tmp;

	tmp = NULL;
	ft_cat_of_line(str, init);
	ft_move__(init, str);
	tputs(tgetstr("sc", NULL), 0, my_putchar);
	if (init->s_cursor != init->s_l)
	{
		ft_get_pos_(init);
		tputs(tgetstr("cd", NULL), 0, my_putchar);
	}
	tmp = ft_strdup(&init->out_put[init->s_cursor - ft_strlen(str)]);
	ft_putstr_fd(tmp, 1);
	ft_strdel(&tmp);
	if (init->s_cursor != init->s_l)
	{
		tputs(tgetstr("rc", NULL), 0, my_putchar);
		init->s_cursor--;
		ft_move_mul_line(init, "+");
	}
}
