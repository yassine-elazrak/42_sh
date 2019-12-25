/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_first_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:09:44 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 17:11:16 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_if_empty_first_word(char *line, t_init *init, int cursor)
{
	int	i;
	int	new_cursor;

	i = 0;
	new_cursor = init->s_cursor - cursor - (int)ft_promptlen(init->promt);
	if (new_cursor == 0 && line[new_cursor] == '\0')
		return (1);
	while (new_cursor > 0)
	{
		if (line[new_cursor] != ' ' && line[new_cursor] != '\t')
			return (0);
		new_cursor--;
	}
	return (1);
}

int		ft_is_cursor_in_first_word(t_init *init, char *line, int cursor)
{
	int	new_cursor;

	new_cursor = 0;
	if (ft_if_empty_first_word(line, init, cursor + 1) == 1)
		return (1);
	new_cursor = init->s_cursor - cursor - (int)ft_promptlen(init->promt) - 1;
	if (ft_cursor_position(line, new_cursor) == 1)
		return (1);
	return (0);
}

char	*ft_take_new_line(char *input, t_init *init, int *cursor, char *line)
{
	char	*str;
	char	c;
	int		i;
	int		len;

	i = 0;
	len = 0;
	str = NULL;
	while (*cursor > 0)
	{
		c = line[*cursor];
		if (c == SEMI_COL || c == PIPE || c == OR || c == AND || c == BG)
		{
			i = 1;
			break ;
		}
		(*cursor)--;
	}
	if (i == 1)
	{
		len = init->s_cursor - *cursor - (int)ft_promptlen(init->promt);
		str = ft_strsub(input, *cursor + 1, len);
	}
	(*cursor)++;
	return (str);
}

int		ft_is_first_cmd(char *input, t_init *init)
{
	char	*line;
	int		cursor;
	char	*new_line;

	new_line = NULL;
	cursor = init->s_cursor - (int)ft_promptlen(init->promt);
	line = ft_strdup(input);
	mark_operators(line);
	mark_bg_op(line);
	if (line[cursor] == '\0')
		cursor--;
	new_line = ft_take_new_line(input, init, &cursor, line);
	if (new_line)
	{
		if (ft_is_cursor_in_first_word(init, new_line, cursor) == 1)
		{
			ft_strdel(&new_line);
			ft_strdel(&line);
			return (1);
		}
		ft_strdel(&new_line);
	}
	ft_strdel(&line);
	return (0);
}

int		ft_is_first_word_42(char *line, t_init *init)
{
	int	i;
	int	j;

	j = 0;
	i = init->s_cursor - ft_promptlen(init->promt);
	if (init->out_put[init->s_cursor] == '\0' &&
		init->s_cursor == (int)ft_promptlen(init->promt))
		return (0);
	i--;
	while (i > 0)
	{
		if (line[i] != ' ' && line[i] != '\t')
			j = 1;
		i--;
	}
	if (j == 0)
		return (2);
	if (ft_cursor_position(line, init->s_cursor -
	(int)ft_promptlen(init->promt)) == 1)
		return (0);
	if (ft_is_first_cmd(line, init) == 1)
		return (0);
	return (1);
}
