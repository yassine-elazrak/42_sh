/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:50:04 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/22 15:15:10 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	append_lst(void **h, void **c, void **t, char type)
{
	if (!*h)
	{
		*h = *c;
		*t = *c;
	}
	else
	{
		if (type == 1)
			((t_job *)(*t))->next = *c;
		else
			((t_process *)(*t))->next = *c;
		*t = *c;
	}
}

int		set_flag(void *curr, int flag, char type)
{
	if (!type || type == 1)
	{
		((t_process *)curr)->flag = flag;
		((t_process *)curr)->status = 0;
		((t_process *)curr)->next = NULL;
		return (flag == PIPE ? 1 : 2);
	}
	else
	{
		((t_job *)curr)->flag = flag;
		((t_job *)curr)->next = NULL;
		return (flag == BG ? 1 : 2);
	}
}

char	*skip_operators(char type, char *token, int *start, int *j)
{
	(*start) += (*j) - (*start);
	if (type == 1)
		while (token[*j] && token[*j] != AND && token[*j] != OR)
			(*j)++;
	else if (type == 2)
		while (token[*j] && token[*j] != BG)
			(*j)++;
	else if (type == 3)
		while (token[*j]
		&& token[*j] != PIPE && token[*j] != AND && token[*j] != OR)
			(*j)++;
	else if (type == 4)
		while (token[*j] && token[*j] != BG
		&& token[*j] != PIPE && token[*j] != AND && token[*j] != OR)
			(*j)++;
	else
		while (token[*j] && token[*j] != PIPE)
			(*j)++;
	if (!token[(*j) - (*start)])
		return (ft_strsub(token, *start, (*j) - (*start) + 1));
	return (ft_strsub(token, *start, (*j) - (*start)));
}

char	*get_cmd_string(char *s)
{
	char	*str;
	int		i;

	str = ft_strdup(s);
	i = 0;
	while (s[i])
	{
		if (s[i] == BLANK)
			str[i] = ' ';
		else if (s[i] == PIPE || s[i] == OR)
			str[i] = '|';
		else if (s[i] == OUT_RED_OP || s[i] == APP_OUT_RED_OP)
			str[i] = '>';
		else if (s[i] == IN_RED_OP || s[i] == HEREDOC_OP)
			str[i] = '<';
		else if (s[i] == AND)
			str[i] = '&';
		else if (s[i] == Q_ESCAPE || s[i] == UQ_ESCAPE)
			str[i] = '\\';
		else if (s[i] == DOLLAR)
			s[i] = '$';
		i++;
	}
	return (str);
}

int		get_list_node(char type, void **curr, char *str)
{
	if (type)
	{
		if (!(*curr = (t_job *)ft_memalloc(sizeof(t_job))))
			exit(EXIT_FAILURE);
		if (!(((t_job *)*curr)->processes = get_process_list(str, type)))
		{
			free(*curr);
			return (0);
		}
		((t_job *)*curr)->command = get_cmd_string(str);
	}
	else
	{
		if (!(*curr = (t_process *)ft_memalloc(sizeof(t_process))))
			exit(EXIT_FAILURE);
		((t_process *)*curr)->heredoc_fd = -1;
		if ((check_redirections(str, ((t_process *)*curr))) == (char *)-1)
		{
			free(*curr);
			return (0);
		}
		if (str && str != (char *)-1)
			((t_process *)*curr)->holder = ft_strsplit(str, BLANK);
	}
	return (1);
}
