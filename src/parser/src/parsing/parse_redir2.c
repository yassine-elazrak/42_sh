/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 00:55:29 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/19 18:13:40 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_redir_type(t_redir *curr, char *str, int i)
{
	if (str[i + 1] != '&' && (str[i] == OUT_RED_OP || str[i] == IN_RED_OP))
		curr->type = (str[i] == OUT_RED_OP) ? O_WRONLY : O_RDONLY;
	else if (str[i] == APP_OUT_RED_OP)
		curr->type = O_APPEND;
	if (curr->type != O_APPEND)
	{
		if (str[i] == OUT_RED_OP && (str[(i - 1 > 0) ? i - 1 : 0] == '&' ||
		(str[i + 1] == '&' && !ft_isdigit(str[i + 2])
		&& !ft_isdigit(str[(i - 1 > 0) ? i - 1 : 0])
		&& str[i + 2] != '-')))
		{
			curr->src_fd = BOTH_FDS;
			curr->type = O_WRONLY;
			if (i > 0)
				str[i - 1] = (str[i - 1] == '&') ? BLANK : str[i - 1];
			str[i + 1] = (str[i + 1] == '&') ? BLANK : str[i + 1];
		}
	}
	if (curr->type != O_APPEND && str[i + 2] && str[i + 1] == '&')
		curr->type = (str[i + 2] == '-') ? CLOSE_FD : FD_AGGR;
}

void	get_src_fd(t_redir *curr, char *str, int *i, int *j)
{
	if (!*i || str[*i - 1] == BLANK ||
	(ft_isprint(str[*i - 1]) && !ft_isdigit(str[*i - 1])))
		curr->src_fd = str[*i] == IN_RED_OP ? 0 : 1;
	else
	{
		(*i) -= 1;
		while (*i >= 0 && str[*i] && ft_isdigit(str[*i]))
			(*i)--;
		curr->src_fd = ft_atoi(str + *i + 1);
		*j = (*i > 0) ? *i : 0;
	}
}

int		get_redir_fds(t_redir *curr, char *str, int *i)
{
	int	old_i;
	int	j;

	old_i = *i;
	j = *i;
	get_src_fd(curr, str, i, &j);
	*i = (curr->type == FD_AGGR || curr->type == CLOSE_FD) ? old_i + 2 : old_i;
	if (curr->type == FD_AGGR && ft_isdigit(str[*i]))
	{
		while (str[*i] && ft_isdigit(str[*i]))
			(*i)++;
		curr->dst_fd = ft_atoi(str + old_i + 2);
	}
	(*i) = curr->type == FD_AGGR ? (*i) - 1 : *i;
	ft_memset((void *)str + j, BLANK,
	(curr->type == CLOSE_FD || curr->type == FD_AGGR) ? *i - j + 1 : *i - j);
	return ((curr->type == FD_AGGR || curr->type == CLOSE_FD) ? 0 : 1);
}

int		get_filename_len(char *str, int *i, int *old_i)
{
	int	length;

	length = 0;
	while (str[*i] == BLANK)
	{
		(*old_i)++;
		(*i)++;
	}
	while (ft_isprint(str[*i]) || str[*i] == UQ_ESCAPE || str[*i] == Q_ESCAPE
	|| str[*i] == DOLLAR)
	{
		length++;
		(*i)++;
	}
	(*i)--;
	return (length);
}

void	get_redir_file(t_redir *curr, char *str, int *i)
{
	int	length;
	int	old_i;

	length = 0;
	str[*i] = BLANK;
	if (curr->type == O_APPEND)
	{
		str[*i + 1] = BLANK;
		(*i)++;
	}
	old_i = *i;
	length = get_filename_len(str, i, &old_i);
	if (length)
	{
		curr->file = ft_strsub(str, old_i, length);
		quotes_delimiter(&curr->file);
		search_and_expand(&curr->file);
		quoted_escape(&curr->file);
		expand_tilde(&curr->file);
		remove_escapes(&curr->file, UQ_ESCAPE);
		remove_escapes(&curr->file, Q_ESCAPE);
		remove_quotes(&curr->file);
	}
	ft_memset(str + old_i, BLANK, length);
}
