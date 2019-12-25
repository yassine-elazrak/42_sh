/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utility_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:40:07 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/20 18:51:44 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*gather_tokens(t_token *tokens)
{
	char	*str;
	int		j;
	int		n;

	str = NULL;
	n = 1;
	while (tokens)
	{
		j = 0;
		while (tokens->list[j])
		{
			if (!str)
				str = tokens->list[j];
			else
				str = ft_join("%f %f", str, tokens->list[j]);
			j++;
		}
		if (tokens->type == AND || tokens->type == OR)
			join_char(&str, tokens->type);
		join_char(&str, tokens->type);
		tokens = tokens->next;
	}
	return (str);
}

int		match(t_alias *h, t_alias *t)
{
	t_alias	*iter;

	iter = h;
	while (iter)
	{
		if (!iter->next)
			break ;
		if (ft_strequ(iter->key, t->key))
			return (1);
		iter = iter->next;
	}
	return (0);
}

void	free_list(t_alias *h, t_alias **t)
{
	t_alias	*iter;
	t_alias	*next;

	iter = h->next;
	while (iter)
	{
		next = iter->next;
		free(iter->key);
		iter->key = NULL;
		free(iter);
		iter = NULL;
		iter = next;
	}
	h->next = NULL;
	*t = NULL;
}

char	*extact_arg(t_token *tokens, int *i)
{
	char	*arg;

	arg = tokens->list[0];
	*i = 0;
	while (*(tokens->list) && arg && ft_strchr(arg, '='))
		arg = tokens->list[++(*i)];
	return (arg);
}

void	replace(t_token *tokens, t_alias *t, int i)
{
	free(tokens->list[i]);
	tokens->list[i] = ft_strdup(t->key);
}
