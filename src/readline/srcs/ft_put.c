/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:35:10 by oherba            #+#    #+#             */
/*   Updated: 2019/12/24 15:24:43 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_cmd(t_init *init)
{
	char	*tmp;

	tmp = ft_strsub(init->out_put, 0, (int)ft_strlen(init->promt));
	free(init->out_put);
	init->s_cursor = (int)ft_strlen(init->promt);
	init->s_l = (int)ft_strlen(init->promt);
	init->out_put = ft_strdup(tmp);
	free(tmp);
}

void	ft_init_terminal(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VTIME] = 1;
	term.c_cc[VMIN] = 0;
	tcsetattr(0, TCSANOW, &term);
	ft_init_output(get_shell_cfg(0)->init);
}

void	ft_alt_up_2(int *x, int *a, t_init *init)
{
	if (init->out_put[init->s_cursor] == '\n')
	{
		*a = 1;
		*x = get_strat(init, init->s_cursor - 1);
		ft_move(init, "-", *x);
	}
	else
	{
		*x = get_strat(init, init->s_cursor);
		ft_move(init, "-", *x - 1);
	}
	if (init->out_put[init->s_cursor - 1] == '\n' && *x != 0)
		ft_move(init, "-", 1);
	if (*x == 0)
		ft_move(init, "-", 1);
}

void	ft_print_(char *str, t_init *init)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	while (str[j])
	{
		if (ft_isprint(str[j]) || str[j] == '\n')
		{
			tmp = ft_strsub(str, j, 1);
			ft_cat_string_of_line(init, tmp);
			ft_strdel(&tmp);
		}
		j++;
	}
}
