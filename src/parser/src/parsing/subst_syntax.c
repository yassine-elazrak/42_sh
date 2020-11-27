/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:08:57 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/23 20:24:19 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			valid_token(char **token, char *param, char closed)
{
	*token = ft_strsub(param, 1, ft_strlen(param) - 2);
	if (!ft_strlen(*token))
	{
		free(*token);
		return (0);
	}
	else if (param[ft_strlen(param) - 1] != closed)
	{
		free(*token);
		return (0);
	}
	return (1);
}

int			check_param_syntax(char **token, char *param)
{
	if (!valid_token(token, param, '}'))
		return (0);
	else if (!correct_syntax(*token))
	{
		free(*token);
		return (0);
	}
	return (1);
}

int			check_nested(char **token, char *tmp)
{
	char	*n_param;
	int		i;

	n_param = NULL;
	n_param = (tmp[1] == '(') ? _PARAM(0) : _PARAM(1);
	if (!valid_parameter(n_param, tmp[1]))
	{
		free(n_param);
		free(*token);
		return (0);
	}
	free(n_param);
	return (1);
}

int			valid_parameter(char *param, char type)
{
	char	*token;
	char	*tmp;

	token = NULL;
	if (type == '(')
	{
		if (!valid_token(&token, param, ')'))
			return (0);
	}
	else
	{
		if (param[0] == '{')
		{
			if (!check_param_syntax(&token, param))
				return (0);
		}
		else
			return (1);
	}
	if (token && (tmp = ft_strchr(token, DOLLAR)))
		if (!(check_nested(&token, tmp)))
			return (0);
	free(token);
	return (1);
}

int			subst_syntax(char *line)
{
	char	*tmp;
	char	*param;
	int		j;
	int		i;
	int		k;

	j = 0;
	i = 0;
	while ((tmp = ft_strchr(line + j, DOLLAR)))
	{
		k = ft_strlen(line) - ft_strlen(tmp);
		if (line[k + 1] == '(')
			param = get_dollar_var(tmp, &i, 0);
		else
			param = get_dollar_var(tmp, &i, 1);
		if (!valid_parameter(param, line[k + 1]))
		{
			ft_putendl_fd("42sh: bad substitution", 2);
			free(param);
			return (1);
		}
		free(param);
		j = k + i;
	}
	return (0);
}
