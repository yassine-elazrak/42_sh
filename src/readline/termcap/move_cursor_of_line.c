/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_of_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:20:17 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/25 14:32:37 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				get_strat_2(t_init *init, int e_d)
{
	int			i;

	i = 0;
	while (0 <= e_d)
	{
		if (init->out_put[e_d] == '\n')
			return (i);
		i++;
		e_d--;
	}
	return (i);
}

char			*ft_check_qout(char *str, t_init *init)
{
	int			i;
	char		c;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if ((str[i] == '"' && ft_cke_c_eskip(i - 1, str)) ||
			(str[i] == '\'' && ft_cke_c_eskip(i - 1, str)))
		{
			c = str[i++];
			while ((str[i] != c || (str[i] == c &&
!ft_cke_c_eskip(i - 1, str))) && str[i])
				i++;
			if (str[i] != c)
				return (call_qote(init, c, str));
		}
		else if (ft_cke_c_eskip(i - 1, str) && ((str[i] == '\\' ||
		str[i] == '|' || (i > 0 && str[i - 1] == '&' &&
		str[i] == '&')) && str[i + 1] == '\0'))
			return (ft_check_qout(call_esqp(str, init), init));
	}
	return (str);
}

int				ft_searh_(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '!' && str[i + 1] != ' ' &&
		str[i + 1] != '=' && str[i + 1] != '\t' &&
		str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

char			*ft_return(char *str, t_init *init)
{
	char		*line;

	line = NULL;
	ft_putchar('\n');
	line = ft_cmd_mangement__(str, init);
	if (line && ft_searh_(line))
	{
		if ((line = ft_expansion(init, line)))
		{
			ft_init_output(init);
			ft_str_line(line, init);
			ft_strdel(&line);
			return (NULL);
		}
	}
	if (line && ft_strncmp(line, "fc", 2) != 0)
		ft_add_history_(init, line, 1);
	return (ft_check_qout(line, init));
}

char			*move_cursor_and_mangemant_fonction(char *str,
t_init *init)
{
	if (!(ft_check_key(init, str)))
		return (NULL);
	if (str[0] == 9 && str[1] == '\0' && init->heredoc_int != 1)
	{
		ft_autocomplete_42(init);
		return (NULL);
	}
	else if (str[0] == -62 && str[1] == -82 && init->heredoc_int != 1)
	{
		init->search = 1;
		home_cursor(init);
		ft_printf("\033[%dD", init->s_col);
		tputs(tgetstr("cd", NULL), 0, my_putchar);
		return (readline(init, "(reverse-i-search)> "));
	}
	else if (str[0] == 10 && ft_strlen(str) == 1 && init->heredoc_int == 1)
		return (ft_strdup(&init->out_put[(int)ft_strlen(init->promt)]));
	else if (str[0] == 10 && ft_strlen(str) == 1)
		return (ft_return(str, init));
	else
		ft_str_line(str, init);
	ft_add_history_(init, &init->out_put[(int)ft_strlen(init->promt)], 0);
	return (NULL);
}
