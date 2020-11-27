/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_subst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 10:14:17 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/19 10:14:46 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		get_param_length(char *tmp, int *i, char open, char op)
{
	while (tmp[*i] && open)
	{
		if (op)
		{
			if (tmp[*i] == '{')
				open += 1;
			else if (tmp[*i] == '}')
				open -= 1;
		}
		else
		{
			if (tmp[*i] == '(')
				open += 1;
			else if (tmp[*i] == ')')
				open -= 1;
		}
		(*i)++;
	}
}

char		*get_dollar_var(char *tmp, int *i, char op)
{
	char	*dollar;
	char	open;

	*i = 1;
	if (tmp[*i] == '{' || tmp[*i] == '(')
		*i = 2;
	if ((*i) == 1)
	{
		if (tmp[*i] == '?')
			return (ft_strdup("?"));
		while (tmp[*i] && (ft_isalnum(tmp[*i]) || tmp[*i] == '_'))
			(*i)++;
	}
	else
	{
		open = 1;
		get_param_length(tmp, i, open, op);
	}
	dollar = ft_strsub(tmp, 1, (*i) - 1);
	return (dollar);
}

char		*get_param(char **param, char op)
{
	if (!op)
	{
		expand_param(param);
		if ((*param)[0] == '{')
		{
			*param = ft_fstrsub(*param, 1, ft_strlen(*param) - 2);
			return (*param);
		}
	}
	else
	{
		if ((*param)[0] == '{')
			*param = ft_fstrsub(*param, 1, ft_strlen(*param) - 2);
	}
	return (*param);
}
