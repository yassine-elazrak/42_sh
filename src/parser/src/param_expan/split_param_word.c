/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_param_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 09:18:20 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/25 16:12:27 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		skip_qout_escap(char *str, int i)
{
	if (str[i] == '"' && (i - 1 >= 0 && str[i - 1] != '\\'))
	{
		i++;
		while (str[i] != '"')
			i++;
	}
	else if (str[i] == '\'' && (i - 1 >= 0 && str[i - 1] != '\\'))
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	return (i);
}

void	specify_pattern_expan(t_param_expan_st *p_w, char *p_ex, int i)
{
	p_w->type = 'F';
	if (p_ex[i] == '%')
	{
		p_ex[i] = -1;
		if (p_ex[i + 1] == '%' && (p_w->operation_type = 'S'))
			p_ex[i + 1] = -1;
		else
			p_w->operation_type = 's';
		return ;
	}
	p_ex[i] = -1;
	if (i == 0)
		p_w->operation_type = 'l';
	else
	{
		if (p_ex[i + 1] == '#' && (p_w->operation_type = 'B'))
			p_ex[i + 1] = -1;
		else
			p_w->operation_type = 'b';
	}
}

void	specify_expan_type(t_param_expan_st *p_w, char *p_ex, int i)
{
	if (p_ex[i] == ':')
	{
		p_ex[i] = -1;
		p_w->type = 'P';
		if (p_ex[i + 1] == '+' && (p_w->operation_type = p_ex[i + 1]))
			p_ex[i + 1] = -1;
		else if (p_ex[i + 1] == '-' && (p_w->operation_type = p_ex[i + 1]))
			p_ex[i + 1] = -1;
		else if (p_ex[i + 1] == '=' && (p_w->operation_type = p_ex[i + 1]))
			p_ex[i + 1] = -1;
		else if (p_ex[i + 1] == '?' && (p_w->operation_type = p_ex[i + 1]))
			p_ex[i + 1] = -1;
		return ;
	}
	p_w->type = 'A';
	if (p_ex[i] == '-')
		p_w->operation_type = p_ex[i];
	if (p_ex[i] == '+')
		p_w->operation_type = p_ex[i];
	if (p_ex[i] == '=')
		p_w->operation_type = p_ex[i];
	if (p_ex[i] == '?')
		p_w->operation_type = p_ex[i];
	p_ex[i] = -1;
}

void	specify_param_word(t_param_expan_st *p_w, char *p_ex)
{
	int		i;

	i = 0;
	if (p_ex[0] == -1)
		i = 1;
	while (p_ex[i] && p_ex[i] != -1)
		i++;
	p_w->param = ft_strsub(p_ex, (p_ex[0] == -1 ? 1 : 0), i);
	if (p_ex[i] == -1 && p_ex[i + 1] == -1)
		i += 2;
	else
		i++;
	p_w->word = ft_strsub(p_ex, i, ft_strlen(p_ex) - i);
}

void	split_param_expan(char *param_expan, t_param_expan_st *param_word)
{
	int		i;

	i = 0;
	while (param_expan[i])
	{
		i = skip_qout_escap(param_expan, i);
		if ((param_expan[i] == ':' || param_expan[i] == '-' ||
			(param_expan[i] == '?' && i != 0) || param_expan[i] == '+' ||
			param_expan[i] == '=' || param_expan[i] == '%' ||
			param_expan[i] == '#') &&
			((i > 0 && param_expan[i - 1] != UQ_ESCAPE &&
			param_expan[i - 1] != Q_ESCAPE) || i == 0))
		{
			if (param_expan[i] == '%' || param_expan[i] == '#')
				specify_pattern_expan(param_word, param_expan, i);
			else
				specify_expan_type(param_word, param_expan, i);
			specify_param_word(param_word, param_expan);
			return ;
		}
		i++;
	}
	param_word->param = ft_strdup(param_expan);
}
