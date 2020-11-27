/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:49:44 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/23 09:56:23 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	isspace(int c)
{
	unsigned char s;

	s = c;
	if (s == ' ' || s == '\t'
		|| s == '\v' || s == '\r' || s == '\f')
		return (1);
	return (0);
}

int			is_dollar(char *line, int i, char dq)
{
	if (!dq)
	{
		if (L[i] == '$' && L[i + 1] && (ft_isalnum(L[i + 1]) || L[i + 1] == '{'
		|| L[i + 1] == '(' || L[i + 1] == '_' || L[i + 1] == '?'))
			return ((L[i] = DOLLAR));
	}
	else
	{
		if (NEQ_ESCAPE(i) && L[i] == '$' && L[i + 1] && (ft_isalnum(L[i + 1])
		|| L[i + 1] == '{' || L[i + 1] == '(' || L[i + 1] == '_'
		|| L[i + 1] == '?'))
			return (1);
	}
	return (0);
}

void		operator_check(char *line, int i, char b_p, char q)
{
	if (!q && IS_DOLLAR(0))
		return ;
	if (!b_p && (dc_operator(L, i) || sc_operator(L, i)))
		return ;
	else if (!b_p && isspace(L[i]))
		L[i] = BLANK;
	else if (b_p && L[i] == 92 && L[(i - 1 > 0) ? i - 1 : 0] != UQ_ESCAPE)
		L[i] = UQ_ESCAPE;
	return ;
}

int			quote(char *line, int i, char *dq, char *q)
{
	if (!*q && ((L[i] == '"' && NEQ_ESCAPE(i)) || (L[i] == D_QUOTE)))
	{
		*dq = !*dq;
		return (1);
	}
	else if (!*dq && ((L[i] == '\'' && NEQ_ESCAPE(i)) || (L[i] == QUOTE)))
	{
		*q = !*q;
		return (1);
	}
	return (0);
}

void		mark_operators(char *line)
{
	int		i;
	char	q;
	char	dq;
	int		b_p;

	q = 0;
	dq = 0;
	i = -1;
	b_p = 0;
	while (L[++i])
	{
		if (quote(L, i, &dq, &q))
			continue ;
		else if ((L[i] == '{' || L[i] == '(') && NEQ_ESCAPE(i))
			b_p++;
		else if ((L[i] == '}' || L[i] == ')') && NEQ_ESCAPE(i))
			b_p--;
		if (!q && !dq && NEQ_ESCAPE(i))
			operator_check(L, i, b_p, 0);
		else if (dq && L[(i - 1 > 0) ? i - 1 : 0] != Q_ESCAPE && L[i] == 92)
			L[i] = Q_ESCAPE;
		else if (dq && IS_DOLLAR(1))
			L[i] = DOLLAR;
	}
}
