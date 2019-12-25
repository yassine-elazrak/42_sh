/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_string_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:50:17 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/23 16:51:56 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_cke_c_eskip(int i, char *str)
{
	int		j;

	j = 0;
	while (i >= 0)
	{
		if (str[i] == '\\')
			j++;
		else
			return (((j % 2) == 0) ? 1 : 0);
		i--;
	}
	return (((j % 2) == 0) ? 1 : 0);
}

int			get_end(t_init *init, int e_d)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (e_d < init->s_l)
	{
		if (init->out_put[e_d] == '\t')
		{
			a = ft_tab_(init, e_d - 1);
			i += a;
		}
		if (init->out_put[e_d] == '\n')
			return (i);
		if (!a)
			i++;
		e_d++;
	}
	return (i);
}

char		*ft_cmd_mangement__(char *str, t_init *init)
{
	char	*cmd;

	(void)str;
	cmd = NULL;
	if (init->esq == 1)
	{
		cmd = ft_strjoin(init->kote,
		&init->out_put[(int)ft_strlen(init->promt)]);
		ft_strdel(&init->kote);
		init->esq = 0;
	}
	else
		cmd = ft_strdup(&init->out_put[(int)ft_strlen(init->promt)]);
	end_cursor(init);
	ft_printf("\033[%dD", init->s_col);
	return (cmd);
}

char		*call_qote(t_init *init, char c, char *str)
{
	init->qt = c;
	ft_strdel(&str);
	init->kote = ft_strdup(&init->out_put[(int)ft_strlen(init->promt)]);
	ft_strdel(&init->promt);
	init->promt = ft_strdup("(qout)>");
	init->qoute = 1;
	ft_init_qote(init);
	return (NULL);
}

char		*call_esqp(char *str, t_init *init)
{
	int		i;

	i = ft_strlen(str) - 1;
	if (str[i] == '\\' && str[i + 1] == '\0' && ft_cke_c_eskip(i - 1, str))
		str[i] = '\0';
	init->kote = ft_strdup(str);
	ft_strdel(&init->promt);
	init->promt = ft_strdup("> ");
	init->esq = 1;
	ft_strdel(&str);
	ft_init_output(init);
	return (NULL);
}
