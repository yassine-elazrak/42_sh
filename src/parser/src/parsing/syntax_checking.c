/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:50:25 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/23 20:24:34 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	counter(char *line, int *j, int o)
{
	char	tmp;

	if (!o)
	{
		while (*j && IS_OPERATOR(*j, _AND, _NEQ))
			(*j)--;
		if ((IS_OPERATOR(*j, _OR, _EQ)))
			(*j)++;
	}
	else
	{
		tmp = line[*j - 1];
		while ((line[*j] && IS_OPERATOR(*j, _AND, _NEQ)) || ((tmp >= OR
		|| tmp == BG) && (IS_REDIR_OP(*j, _OR, _EQ))))
			(*j)++;
	}
}

int		redir_syntax(char *line, int i)
{
	int	j;

	j = i + 1;
	if (IS_REDIR_OP(i, _OR, _EQ))
	{
		if (line[i] == APP_OUT_RED_OP && line[(i - 1 > 0) ? i - 1 : 0] == BG)
			return (0);
		else if (line[i] == OUT_RED_OP && line[(i - 1 > 0) ? i - 1 : 0] == '&'
		&& line[i + 1] == '&')
			return (0);
		else if (line[i + 1] == '&' &&
		(line[i] == IN_RED_OP || line[i] == OUT_RED_OP))
		{
			counter(line, &j, 1);
			if (!is_not_blank(line, i + 2, j))
				return (0);
		}
	}
	return (1);
}

int		get_operands(char *line, int *i, char t_op, int *o_i)
{
	int		j;
	char	operands;

	operands = 0;
	*o_i = *i;
	if (!(*i) && (IS_REDIR_OP(*i, _AND, _NEQ)))
		return (operands);
	j = (*i - 1) >= 0 ? (*i - 1) : *i;
	if ((j >= 0 && IS_OPERATOR(j, _AND, _NEQ))
	|| (!j && (IS_REDIR_OP(j, _OR, _EQ))))
	{
		counter(line, &j, 0);
		if (is_not_blank(line, j, *i))
			operands |= LEFT_OPR;
		t_op ? (j = *i + 2)
		: (j = *i + 1);
		counter(line, &j, 1);
		if (redir_syntax(line, *i) &&
		is_not_blank(line, *i = t_op ? (*i + 2) : (*i + 1), j))
			operands |= RIGHT_OPR;
	}
	return (operands);
}

int		ft_putendline(char const *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	ft_putchar('\n');
	return (1);
}

int		check_syntax_errors(char *line)
{
	int		i;
	char	t_op;
	char	ops;
	int		j;

	i = -1;
	while (line[++i])
	{
		if (IS_OPERATOR(i, _OR, _EQ))
		{
			t_op = TCO(i, _OR, _EQ) ? 1 : 0;
			ops = get_operands(line, &i, t_op, &j);
			if (((ops & LEFT_OPR) == LEFT_OPR && (line[j] == SEMI_COL ||
			line[j] == BG))
			|| ((IS_REDIR_OP(j, _OR, _EQ)) && (ops & RIGHT_OPR) == RIGHT_OPR))
			{
				i--;
				continue ;
			}
			else if ((ops & RIGHT_OPR) != RIGHT_OPR
			|| (ops & LEFT_OPR) != LEFT_OPR)
				return (ft_putendline("syntax error."));
		}
	}
	return (0);
}
