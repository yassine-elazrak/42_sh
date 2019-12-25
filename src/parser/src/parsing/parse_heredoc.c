/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:33:24 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/23 20:27:35 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	store_heredoc(char **heredoc, char **buf)
{
	int		i;

	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '$' && (*buf)[i + 1] && (ft_isalnum((*buf)[i + 1]) ||
		(*buf)[i + 1] == '{' || (*buf)[i + 1] == '(' ||
		(*buf)[i + 1] == '_' || (*buf)[i + 1] == '?'))
			(*buf)[i] = DOLLAR;
		i++;
	}
	search_and_expand(buf);
	i = -1;
	while ((*buf)[++i])
		if ((*buf)[i] == BLANK)
			(*buf)[i] = '\n';
	if (!ft_strlen(*heredoc))
	{
		free(*heredoc);
		*heredoc = ft_strdup(*buf);
		free(*buf);
	}
	else
		*heredoc = ft_fstrjoin(ft_fstrjoin(*heredoc, ft_strdup("\n")), *buf);
}

void	get_input(t_init *in, char **heredoc, char *eof, char *sig_int)
{
	char	*buf;
	char	eol[2];

	buf = NULL;
	eol[0] = 4;
	eol[1] = 0;
	while (1)
	{
		buf = readline(in, "heredoc> ");
		if (!buf)
		{
			*sig_int = 1;
			break ;
		}
		ft_putchar('\n');
		if (ft_strequ(buf, eof) || ft_strequ(buf, eol))
			break ;
		store_heredoc(heredoc, &buf);
	}
	if (buf)
		free(buf);
}

char	*get_heredoc_string(char *eof)
{
	t_init	*in;
	char	*heredoc;
	char	sig_int;

	sig_int = 0;
	in = get_shell_cfg(0)->init;
	in->heredoc_int = 1;
	heredoc = ft_strnew(0);
	get_input(in, &heredoc, eof, &sig_int);
	in->heredoc_int = 0;
	free(eof);
	if (sig_int)
		free(heredoc);
	return (!sig_int ? heredoc : (char *)-1);
}

int		get_heredoc_fd(char *str, int *i)
{
	(*i) -= 1;
	while (str[*i] && ft_isdigit(str[*i]))
		(*i)--;
	(*i) += 1;
	return (ft_atoi(str + (*i)));
}

char	*get_heredoc(char *str, int *i, int *hd_fd)
{
	char	*eof;
	int		old_i;
	int		j;

	old_i = *i;
	*hd_fd = IS_EMPTY ? 0 : get_heredoc_fd(str, i);
	ft_memset(str + *i, BLANK, old_i - (*i) + 2);
	*i = old_i + 2;
	old_i = *i;
	while (str[*i] && (str[*i] == BLANK || str[*i] == HEREDOC_OP))
	{
		if (str[*i] == HEREDOC_OP)
			str[*i] = BLANK;
		old_i++;
		(*i)++;
	}
	while (str[*i] && PART_OF_EOF)
		(*i)++;
	eof = ft_strsub(str, old_i, *i - old_i);
	j = -1;
	while (eof && eof[++j])
		if (eof[j] == DOLLAR)
			eof[j] = '$';
	remove_unwanted_chars(&eof, str, old_i, *i);
	return (get_heredoc_string(eof));
}
