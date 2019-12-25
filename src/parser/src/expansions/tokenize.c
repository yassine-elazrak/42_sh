/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:57 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/16 18:34:50 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		append(t_token **head, t_token **tail, t_token **token)
{
	if (!*head)
		*head = *token;
	else
		(*tail)->next = *token;
	*tail = *token;
	*token = NULL;
}

static t_token	*get_node(char *cmd_chain, int *old_i, int *i)
{
	t_token	*token;
	char	*str;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		exit(EXIT_FAILURE);
	token->type = 0;
	token->list = NULL;
	token->sub = NULL;
	token->next = NULL;
	if ((str = skip_operators(4, cmd_chain, old_i, i)))
	{
		add_spaces(&str);
		token->list = ft_strsplit(str, BLANK);
		free(str);
	}
	return (token);
}

t_token			*get_tokens(t_token **head, char *cmd_chain)
{
	int		i;
	int		old_i;
	t_token	*token;
	t_token	*tail;

	tail = NULL;
	token = NULL;
	i = 0;
	old_i = 0;
	while (cmd_chain[i])
	{
		if (token && (cmd_chain[i] == BG || cmd_chain[i] == AND ||
		cmd_chain[i] == OR || cmd_chain[i] == PIPE || cmd_chain[i] == SEMI_COL))
		{
			old_i += i - old_i;
			token->type = cmd_chain[i];
			i = (cmd_chain[i] == AND || cmd_chain[i] == OR) ? i + 2 : i + 1;
			append(head, &tail, &token);
		}
		else
			token = get_node(cmd_chain, &old_i, &i);
	}
	if (token)
		append(head, &tail, &token);
	return (*head);
}
