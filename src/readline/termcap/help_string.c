/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:47:48 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/25 18:00:52 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*ft_get_search(t_init *init, char *str)
{
	t_history	*lst;

	lst = init->last_history;
	if (str == NULL || str[0] == '\0')
		return ("");
	while (lst)
	{
		if (ft_strstr(lst->str, str))
			return (lst->str);
		lst = lst->prvet;
	}
	return ("");
}

void			ft_search_init(t_init *init)
{
	init->search = 0;
	home_cursor(init);
	ft_printf("\033[%dD", init->s_col);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	ft_strdel(&init->promt);
	init->promt = ft_getprompt();
	ft_strdel(&init->out_put);
	init->out_put = ft_strjoin(init->promt, init->str_search);
	init->s_cursor = ft_strlen(init->out_put);
	init->s_l = ft_strlen(init->out_put);
	ft_putstr(init->out_put);
}

char			*ft_search_(char *str, t_init *init)
{
	if ((!(ft_check_key(init, str))) || ((str[0] == 10 && ft_strlen(str) == 1)))
		ft_search_init(init);
	else
	{
		tputs(tgetstr("cd", NULL), 0, my_putchar);
		ft_str_line(str, init);
		tputs(tgetstr("sc", NULL), 0, my_putchar);
		ft_strdel(&init->str_search);
		init->str_search = ft_strdup(ft_get_search(init,
		&init->out_put[(int)ft_strlen(init->promt)]));
		ft_putstr(" : `");
		ft_putstr(init->str_search);
		ft_putchar('`');
		tputs(tgetstr("rc", NULL), 0, my_putchar);
	}
	return (NULL);
}

int				ft_tab_(t_init *init, int e_d)
{
	int			i;
	int			k;
	int			a;

	i = 0;
	a = (get_strat(init, e_d));
	a = (a) % init->s_col;
	i = a;
	k = i;
	if ((init->s_col - (i % init->s_col)) > (init->s_col % 8))
		return (8 - ((i) % 8));
	else
		return ((init->s_col - (i % init->s_col)) - 1);
}
