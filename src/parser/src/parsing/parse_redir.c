/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 04:19:50 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/23 19:51:03 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		append_redir(t_redir **h, t_redir **c, t_redir **t)
{
	if (!*h)
	{
		*h = *c;
		*t = *c;
	}
	else
	{
		(*t)->next = *c;
		*t = *c;
	}
}

static t_redir	*get_node(void)
{
	t_redir *node;

	if (!(node = (t_redir *)malloc(sizeof(t_redir))))
		exit(2);
	node->type = -1;
	node->src_fd = -1;
	node->dst_fd = -1;
	node->file = NULL;
	node->next = NULL;
	return (node);
}

int				get_redir_info(t_redir *curr, char *str, int *i)
{
	get_redir_type(curr, str, *i);
	if (curr->src_fd != BOTH_FDS)
	{
		if (!get_redir_fds(curr, str, i))
			return (0);
	}
	get_redir_file(curr, str, i);
	return (1);
}

void			check_heredoc(t_process *cmd, char *str, int *i)
{
	if (cmd->heredoc)
		ft_strdel(&cmd->heredoc);
	cmd->heredoc = get_heredoc(str, i, &cmd->heredoc_fd);
}

char			*check_redirections(char *str, t_process *cmd)
{
	int		i;
	t_redir	*curr;
	t_redir	*head;
	t_redir	*tail;

	head = NULL;
	curr = NULL;
	tail = NULL;
	i = 0;
	while (str[i])
	{
		if (IS_REDIRECTION)
		{
			curr = get_node();
			append_redir(&head, &curr, &tail);
			if (!get_redir_info(curr, str, &i))
				continue ;
		}
		else if (str[i] == HEREDOC_OP)
			check_heredoc(cmd, str, &i);
		i++;
	}
	cmd->redir = head;
	return (cmd->heredoc == (char *)-1 ? (char *)-1 : str);
}
