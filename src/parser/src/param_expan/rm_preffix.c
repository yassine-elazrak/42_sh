/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_preffix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 14:47:38 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/25 16:11:20 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	preffix_globing(t_mtools *t, char pattern_size)
{
	int		globing;

	if ((t->i_preffix - 1 >= 0 && t->preffix[t->i_preffix - 1] != UQ_ESCAPE &&
		t->preffix[t->i_preffix - 1] != Q_ESCAPE) || t->i_preffix == 0)
	{
		if (t->preffix[t->i_preffix + 1])
		{
			t->i_preffix++;
			if (pattern_size == 'B')
			{
				globing = ft_strlen(t->src);
				while (t->src[globing] != t->preffix[t->i_preffix] && globing)
					globing--;
				t->i_src = globing;
			}
			else
				while (t->src[t->i_src] != t->preffix[t->i_preffix] &&
						t->src[t->i_src])
					t->i_src++;
		}
		else if (t->preffix[t->i_preffix - 1])
			t->ret = pattern_size == 'B' ? 1 : 2;
	}
	else
		t->i_preffix += 1;
}

void	ptwo_in_one(t_mtools *tools, char *src, char *preffix, char mission)
{
	if (mission == 'I')
	{
		tools->i_src = 0;
		tools->i_preffix = 0;
		tools->src = src;
		tools->preffix = preffix;
	}
	if (mission == 'E')
	{
		if (tools->i_preffix > 0 &&
			(tools->preffix[tools->i_preffix - 1] == UQ_ESCAPE ||
			tools->preffix[tools->i_preffix - 1] == Q_ESCAPE))
			tools->i_preffix++;
		if (tools->i_src > 0 &&
			(tools->src[tools->i_src - 1] == UQ_ESCAPE ||
			tools->src[tools->i_src - 1] == Q_ESCAPE))
			tools->i_src++;
	}
}

int		find_preffix(char *src, char *preffix, char preffix_size)
{
	t_mtools	tools;

	ptwo_in_one(&tools, src, preffix, 'I');
	while (src[tools.i_src] && preffix[tools.i_preffix])
	{
		if (preffix[tools.i_preffix] == '*')
		{
			tools.ret = 0;
			preffix_globing(&tools, preffix_size);
			if (tools.ret == 1)
				return (ft_strlen(src));
			if (tools.ret == 2)
				return (tools.i_src);
		}
		ptwo_in_one(&tools, src, preffix, 'E');
		if (src[tools.i_src] != preffix[tools.i_preffix] ||
				!preffix[tools.i_preffix])
			break ;
		tools.i_src++;
		tools.i_preffix++;
	}
	return (preffix[tools.i_preffix] ? -1 : tools.i_src);
}

char	*rm_preffix(t_param_expan_st *p_w)
{
	int		i_src;
	char	*value;

	if (!(value = ft_getvlaue_bykey(p_w->param, INTERN)))
		return (ft_strdup(""));
	p_w->word = delet_adds_stars(p_w->word, '*');
	if (p_w->operation_type == 'b')
	{
		if ((i_src = find_preffix(value, p_w->word, 'b')) < 0)
			return (ft_strdup(value));
		return (ft_strsub(value, i_src, ft_strlen(value) - i_src));
	}
	if ((i_src = find_preffix(value, p_w->word, 'B')) < 0)
		return (ft_strdup(value));
	return (ft_strsub(value, i_src, ft_strlen(value) - i_src));
}
