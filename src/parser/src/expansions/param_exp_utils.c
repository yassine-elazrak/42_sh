/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 20:14:38 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/24 11:47:49 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		param_subst(char *s, char *tmp, char **str)
{
	char	*param;
	char	*exp;
	int		len;
	int		i;

	param = get_dollar_var(tmp, &i, 1);
	len = ft_strlen(param);
	if (s[len + 1])
		*str = ft_strdup(s + len + 1);
	param = ft_strchr(param, DOLLAR) ?
	get_param(&param, 0) : get_param(&param, 1);
	if ((exp = get_param_expan(param)) && ft_strlen(exp))
	{
		if (*str)
			*str = ft_fstrjoin(exp, *str);
		else
			*str = exp;
	}
	else if (exp && !ft_strlen(exp))
		free(exp);
	else
		get_shell_cfg(0)->abort = 1;
	free(param);
}

void		get_expansion(char *s, char *tmp, char **str)
{
	char	*param;
	char	*exp;
	int		i;
	int		len;

	param = get_dollar_var(tmp, &i, 1);
	len = ft_strlen(param);
	if (s[len + 1])
		*str = ft_strdup(s + len + 1);
	if (param[0] == '{')
		param = ft_fstrsub(param, 1, len - 2);
	if ((exp = get_param_expan(param)) && ft_strlen(exp))
	{
		if (*str)
			*str = ft_fstrjoin(exp, *str);
		else
			*str = exp;
	}
	else if (exp && !ft_strlen(exp))
		free(exp);
	else
		get_shell_cfg(0)->abort = 1;
	free(param);
}

void		expand_param(char **s)
{
	char	*tmp;
	int		k;
	char	*str[2];

	tmp = NULL;
	while ((tmp = ft_strrchr((*s), DOLLAR)))
	{
		str[0] = NULL;
		str[1] = NULL;
		k = ft_strlen(*s) - ft_strlen(tmp);
		if (k > 0)
			str[0] = ft_strsub(*s, 0, k);
		if ((*s)[k + 1] == '(')
			ctl_subst((*s) + k, tmp, &str[1], is_quoted(*s, k));
		else
			get_expansion((*s) + k, tmp, &str[1]);
		if (str[0] && !ft_strlen(str[0]))
			str[0][0] = BLANK;
		if (str[1] && !ft_strlen(str[1]))
			str[1][0] = BLANK;
		free(*s);
		*s = ft_fstrjoin(str[0] ? str[0] :
		ft_strnew(0), str[1] ? str[1] : ft_strnew(0));
	}
}

void		search_and_expand(char **s)
{
	char	*tmp;
	int		j;
	int		k;
	char	*str[2];

	j = 0;
	while ((tmp = ft_strchr((*s) + j, DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		str[0] = NULL;
		str[1] = NULL;
		str[0] = (k > 0) ? ft_strsub(*s, 0, k) : NULL;
		if ((*s)[k + 1] == '(')
			ctl_subst((*s) + k, tmp, &str[1], is_quoted(*s, k));
		else
			param_subst((*s) + k, tmp, &str[1]);
		if (str[0] && !ft_strlen(str[0]))
			str[0][0] = BLANK;
		if (str[1] && !ft_strlen(str[1]))
			str[1][0] = BLANK;
		free(*s);
		*s = ft_fstrjoin(str[0] ? str[0] : ft_strnew(0),
		str[1] ? str[1] : ft_strnew(0));
		j = ((size_t)j < ft_strlen(*s)) ? j + 1 : j;
	}
}

int			expand(char **args, t_arg *c)
{
	char	*tmp;
	int		size;

	size = 0;
	tmp = ft_strdup(*args);
	search_and_expand(&tmp);
	quoted_escape(&tmp);
	expand_tilde(&tmp);
	free(*args);
	*args = tmp;
	remove_escapes(args, UQ_ESCAPE);
	remove_escapes(args, Q_ESCAPE);
	remove_quotes(args);
	store_args(c, args, &size);
	return (size);
}
