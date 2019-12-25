/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:47:49 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/22 16:41:03 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				circular(t_alias *h, t_alias **t, char *alias)
{
	t_alias	*c;

	c = NULL;
	if (!(c = malloc(sizeof(t_alias))))
		exit(EXIT_FAILURE);
	c->key = ft_strdup(alias);
	c->next = NULL;
	if (!h->next)
		h->next = c;
	else
		(*t)->next = c;
	*t = c;
	if (match(h, *t))
		return (1);
	return (0);
}

static t_token	*get_sub_token(t_token *token, char *alias, char **str)
{
	mark_operators(alias);
	mark_bg_op(alias);
	token->sub = get_tokens(&token->sub, alias);
	*str = ft_strnew(0);
	return (token->sub);
}

char			*expand_alias(t_token *token, char *alias,
t_alias *h, t_alias **t)
{
	char	*arg;
	t_token *tokens;
	char	*str;
	char	*tmp;
	int		i;

	tokens = get_sub_token(token, alias, &str);
	while (tokens)
	{
		if ((tmp = ft_getvlaue_bykey(
		(arg = extact_arg(tokens, &i)), ALIAS)) && !circular(h, t, arg))
		{
			arg = expand_alias(tokens, DUPL(tmp), h, t);
			free(tokens->list[i]);
			tokens->list[i] = arg;
		}
		else if (tmp)
			replace(tokens, *t, i);
		combine(tokens, &str);
		free_list(h, t);
		tokens = tokens->next;
	}
	free(alias);
	free_tokens(token->sub);
	return (str);
}

void			update_token(t_token *tokens, char *alias, char **arg, int i)
{
	t_alias			*h;
	t_alias			*t;

	h = NULL;
	t = NULL;
	if (!(h = (t_alias *)malloc(sizeof(t_alias))))
		exit(EXIT_FAILURE);
	h->key = ft_strdup(*arg);
	h->next = NULL;
	*arg = expand_alias(tokens, DUPL(alias), h, &t);
	free(tokens->list[i]);
	tokens->list[i] = *arg;
	free(alias);
	free(h->key);
	free(h);
}

t_token			*alias_expansion(char *line)
{
	t_token			*tokens;
	char			*arg;
	char			*alias;
	int				i;
	t_token			*tmp;

	tokens = NULL;
	arg = NULL;
	tokens = get_tokens(&tokens, line);
	tmp = tokens;
	while (tokens)
	{
		arg = tokens->list[0];
		i = 0;
		while (*(tokens->list) && arg && ft_strchr(arg, '='))
			arg = tokens->list[++i];
		if (arg)
		{
			if ((alias = ft_getvlaue_bykey(arg, ALIAS)))
				update_token(tokens, ft_strdup(alias), &arg, i);
		}
		tokens = tokens->next;
	}
	return (tmp);
}
