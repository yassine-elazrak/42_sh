/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 01:09:38 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 14:39:34 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					ft_check_key(t_init *init, char *str)
{
	if (g_sig)
	{
		ft_init_output(init);
		g_sig = 0;
	}
	if (((str[0] == -30) || (str[0] == -61)) &&
	key_slect(str, init) != 0 && init->heredoc_int != 1)
	{
		ft_exec_ket_s(init);
		return (0);
	}
	if ((str[0] == 27) && (str[1] == 91) && key_4_of_cursor(str, init) != 0)
		return (0);
	return (1);
}

static void			ft_free_history(t_history *lst)
{
	t_history		*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_strdel(&tmp->str);
		ft_memdel((void **)&tmp);
	}
}

void				ft_init_free(void)
{
	t_init			*init;

	init = get_shell_cfg(0)->init;
	ft_free_history(init->history);
	ft_strdel(&init->out_put);
	ft_strdel(&init->promt);
	ft_strdel(&init->str_search);
	ft_memdel((void **)init);
}

void				ft_chang_size(void)
{
	t_init			*init;

	init = get_shell_cfg(0)->init;
	g_sig_win = 0;
	ft_putstr_fd(&init->out_put[(int)ft_strlen(init->promt)], 1);
	init->s_cursor = ft_strlen(init->out_put);
}
