/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_suffix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:06:50 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/25 16:03:49 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		suffix_globing_helper(t_mtools *t, int globing)
{
	while (t->src[globing] != t->suffix[t->i_suffix] &&
			t->src[globing])
		globing++;
	return (globing);
}

void	suffix_globing(t_mtools *t, char pattern_size)
{
	int		globing;

	if ((t->i_suffix > 0 && t->suffix[t->i_suffix - 1] != UQ_ESCAPE &&
				t->suffix[t->i_suffix - 1] != Q_ESCAPE) || t->i_suffix == 0)
	{
		if (t->i_suffix - 1 >= 0 && t->suffix[t->i_suffix - 1])
		{
			t->i_suffix--;
			if (pattern_size == 'S')
			{
				globing = 0;
				globing = suffix_globing_helper(t, globing);
				if (!globing && (t->ret = 1))
					return ;
				t->i_src = globing;
			}
			else
				while (t->src[t->i_src] != t->suffix[t->i_suffix] && t->i_src)
					t->i_src--;
		}
		else if (t->suffix[t->i_suffix + 1])
			t->ret = pattern_size == 'S' ? 1 : 2;
	}
	else
		t->i_suffix -= 1;
}

void	two_in_one(t_mtools *tools, char *src, char *suffix, char mission)
{
	if (mission == 'I')
	{
		tools->i_src = ft_strlen(src);
		tools->i_suffix = ft_strlen(suffix);
		tools->src = src;
		tools->suffix = suffix;
	}
	if (mission == 'E')
	{
		if (tools->i_suffix > 0 &&
			(tools->suffix[tools->i_suffix - 1] == UQ_ESCAPE ||
			tools->suffix[tools->i_suffix - 1] == Q_ESCAPE))
			tools->i_suffix--;
		if (tools->i_src > 0 &&
			(tools->src[tools->i_src - 1] == UQ_ESCAPE ||
			tools->src[tools->i_src - 1] == Q_ESCAPE))
			tools->i_src--;
	}
}

int		find_suffix(char *src, char *suffix, char suffix_size)
{
	t_mtools	tools;

	two_in_one(&tools, src, suffix, 'I');
	while (tools.i_src >= 0 && tools.i_suffix >= 0)
	{
		if (suffix[tools.i_suffix] == '*')
		{
			tools.ret = 0;
			suffix_globing(&tools, suffix_size);
			if (tools.ret == 1)
				return (0);
			if (tools.ret == 2)
				return (tools.i_src + 1);
		}
		two_in_one(&tools, src, suffix, 'E');
		if (src[tools.i_src] != suffix[tools.i_suffix] || !tools.i_suffix)
			break ;
		tools.i_src--;
		tools.i_suffix--;
	}
	if (tools.i_suffix >= 0 && src[tools.i_src] != suffix[tools.i_suffix])
		return (-1);
	return (tools.i_src);
}

char	*rm_suffix(t_param_expan_st *p_w)
{
	int		i_src;
	char	*value;

	if (!(value = ft_getvlaue_bykey(p_w->param, INTERN)))
		return (ft_strdup(""));
	p_w->word = delet_adds_stars(p_w->word, '*');
	if (p_w->operation_type == 's')
	{
		if ((i_src = find_suffix(value, p_w->word, 's')) < 0)
			return (ft_strdup(value));
		return (ft_strsub(value, 0, i_src));
	}
	if ((i_src = find_suffix(value, p_w->word, 'S')) < 0)
		return (ft_strdup(value));
	return (ft_strsub(value, 0, i_src));
}
