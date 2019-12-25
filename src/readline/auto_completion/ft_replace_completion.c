/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_completion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 16:08:20 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 17:48:56 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_completion_display(t_init *init, char *completion)
{
	int i;
	int j;
	int k;

	i = 0;
	j = init->s_cursor;
	k = ft_strlen(completion) - 1;
	while (i < k)
	{
		if (j < init->s_l)
			tputs(tgetstr("nd", NULL), 0, my_putchar);
		j++;
		i++;
	}
}

void	replace_the_auto_comlete_42(t_init *init, char *completion)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = init->s_cursor - 1;
	tmp = ft_strdup(init->out_put);
	mark_operators(tmp);
	mark_bg_op(tmp);
	while (i > (int)ft_promptlen(init->promt) && IS_STOP_CHAR(i))
		i--;
	ft_strdel(&tmp);
	if (i != (int)ft_promptlen(init->promt))
		i += 1;
	if (init->s_cursor > (int)ft_promptlen(init->promt))
	{
		j = init->s_cursor;
		while (j > i)
		{
			del_char_of_line(&init->out_put, init);
			i++;
		}
	}
	ft_cat_string_of_line(init, completion);
	ft_completion_display(init, completion);
}

void	ft_print_one_completion(t_init *init, char *to_complete)
{
	char	*completion;
	int		i;
	char	*str;

	i = 0;
	completion = NULL;
	str = NULL;
	if (ft_is_var(to_complete) == 1)
	{
		while (to_complete[i] && to_complete[i] != '$')
			i++;
		if (to_complete[i] && to_complete[i] == '$' &&
		to_complete[i + 1] == '{')
			i++;
		str = ft_strsub(to_complete, 0, i + 1);
		completion = ft_strjoin(str, (init->completion_lst->str));
		ft_strdel(&str);
	}
	else
		completion = ft_strdup(init->completion_lst->str);
	replace_the_auto_comlete_42(init, completion);
	ft_strdel(&completion);
}

void	ft_print_completion_posibilities(t_init *init, int lst_len, int max_len)
{
	int print_len;
	int tmp_cursor;

	max_len = ft_max_len_lst_42(init->completion_lst, &lst_len);
	print_len = ft_8_multipl(max_len);
	tmp_cursor = init->s_cursor;
	ft_ls_print_42(init->completion_lst, print_len, lst_len);
	ft_putchar('\n');
	ft_putstr(init->out_put);
	tmp_cursor = ft_strlen(init->out_put) - tmp_cursor;
	while (tmp_cursor > 0)
	{
		tputs(tgetstr("le", NULL), 0, my_putchar);
		tmp_cursor--;
	}
}

void	ft_print_completion_42(t_init *init)
{
	int		max_len;
	int		lst_len;
	char	*min_completion;
	char	*old_to_complete;

	if (init->completion_lst == NULL)
		return ;
	max_len = ft_max_len_lst_42(init->completion_lst, &lst_len);
	if (lst_len == 1)
		ft_print_one_completion(init, init->to_complete);
	else if (lst_len > 1)
	{
		min_completion = ft_max_completion(init->completion_lst);
		if (min_completion)
		{
			old_to_complete = ft_take_to_complte_42(init);
			ft_print_max_completion(init, old_to_complete, min_completion);
			ft_strdel(&min_completion);
		}
		ft_print_completion_posibilities(init, lst_len, max_len);
	}
}
