/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:11:06 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/23 20:28:17 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		param_valid(char *param, int i, char op)
{
	if (!op)
		while (ft_isalnum(param[i]) || param[i] == '_')
			i++;
	if (param[i] && param[i] != ':' && param[i] != '#'
	&& param[i] != '-' && param[i] != '?' && param[i] != '+'
	&& param[i] != '=' && param[i] != '%')
		return (0);
	return (1);
}

int		correct_syntax(char *param)
{
	int		pos;
	int		i;

	pos = 0;
	i = 0;
	if (param[0] == '#')
	{
		i = 1;
		while (param[i])
		{
			if (!ft_isalnum(param[i]) && param[i] != '_')
				return (0);
			i++;
		}
	}
	else if (param[0] == '?' && !param_valid(param, 1, 1))
		return (0);
	else
		while (param[i])
		{
			if (ft_isalnum(param[i]) || param[i] == '_' || param[i] == '?')
				return (!param_valid(param, i, 0) ? 0 : 1);
			return (0);
		}
	return (1);
}

/*
** Not really part of this file.
*/

void	remove_unwanted_chars(char **eof, char *str, int old_i, int i)
{
	quotes_delimiter(eof);
	remove_quotes(eof);
	remove_escapes(eof, UQ_ESCAPE);
	remove_escapes(eof, Q_ESCAPE);
	ft_memset(str + old_i, BLANK, i - old_i);
}
