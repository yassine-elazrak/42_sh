/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:53:56 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/20 12:51:08 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_bg_jobs(char *line)
{
	int	i;
	int	bg;

	i = 0;
	bg = 0;
	while (line[i])
	{
		if (line[i] == BG)
			bg++;
		i++;
	}
	return (bg);
}

void		mark_bg_op(char *line)
{
	int		i;
	char	q;
	char	dq;
	int		b_p;

	i = -1;
	q = 0;
	dq = 0;
	b_p = 0;
	while (L[++i])
	{
		if (!b_p && !q && L[i] == '"' && NEQ_ESCAPE(i))
			dq = !dq;
		else if (!b_p && !dq && L[i] == '\'' && NEQ_ESCAPE(i))
			q = !q;
		else if ((L[i] == '{' || L[i] == '(') && NEQ_ESCAPE(i))
			b_p++;
		else if ((L[i] == '}' || L[i] == ')') && NEQ_ESCAPE(i))
			b_p--;
		if (L[i] == '{' || L[i] == '(')
			b_p++;
		if (!b_p && !q && !dq && NEQ_ESCAPE(i) && L[i + 1] != OUT_RED_OP &&
		L[INDEX(i)] != OUT_RED_OP && L[INDEX(i)] != IN_RED_OP && line[i] == '&')
			L[i] = BG;
	}
}

int			syntax_error(char **line)
{
	if (check_syntax_errors(*line) || subst_syntax(*line))
	{
		free(*line);
		ft_set_last_rvalue(255);
		return (1);
	}
	return (0);
}

void		highlight_ops(char *line)
{
	mark_operators(line);
	mark_bg_op(line);
}

char		*pre_parse(char *input)
{
	char	*line;

	line = NULL;
	if (!input || !ft_strlen(input))
		return (NULL);
	line = ft_strdup(input);
	highlight_ops(line);
	if (syntax_error(&line))
		return (NULL);
	return (line);
}
