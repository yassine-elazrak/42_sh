/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:36:33 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/19 10:51:02 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	join_char(char **str, char c)
{
	char	*joined;
	int		len;
	int		i;

	len = ft_strlen(*str);
	joined = ft_strnew(len + 1);
	i = 0;
	while (i < len)
	{
		joined[i] = (*str)[i];
		i++;
	}
	joined[len] = c;
	joined[++len] = 0;
	free(*str);
	*str = joined;
}

void	update_string(char **str, int *j)
{
	char	*s[3];

	s[0] = NULL;
	s[1] = NULL;
	s[2] = NULL;
	s[0] = ft_strsub(*str, 0, *j);
	join_char(&s[0], BLANK);
	if ((*str)[*j])
		s[1] = ft_strdup((*str) + *j);
	s[2] = ft_fstrjoin(s[0] ? s[0] : ft_strnew(0), s[1] ? s[1] : ft_strnew(0));
	*j = (*str)[*j] == ((*str)[*j] == OUT_RED_OP || (*str)[*j] == IN_RED_OP) ?
		(*j) + 2 : (*j) + 3;
	free(*str);
	*str = s[2];
}

void	add_spaces(char **str)
{
	int		j;
	int		i;

	j = 0;
	while ((*str)[j])
	{
		if ((*str)[j] == OUT_RED_OP || (*str)[j] == IN_RED_OP
		|| (*str)[j] == APP_OUT_RED_OP || (*str)[j] == HEREDOC_OP)
		{
			i = (j > 0) ? j - 1 : 0;
			if (!ft_isdigit((*str)[i]) && (*str)[i] != '&')
				update_string(str, &j);
			else
			{
				j++;
				continue;
			}
		}
		else
			j++;
	}
}

void	combine(t_token *tokens, char **str)
{
	int	j;

	j = 0;
	while (tokens->list[j])
	{
		*str = ft_fstrjoin(*str, ft_strdup(" "));
		*str = ft_fstrjoin(*str, tokens->list[j]);
		j++;
	}
	if (tokens->type == AND || tokens->type == OR)
		join_char(str, tokens->type);
	join_char(str, tokens->type);
}

int		is_quoted(char *s, int len)
{
	int		i;
	char	dq;

	i = 0;
	dq = 0;
	while (i < len)
	{
		if (s[i] == D_QUOTE)
			dq = !dq;
		i++;
	}
	return (dq);
}
