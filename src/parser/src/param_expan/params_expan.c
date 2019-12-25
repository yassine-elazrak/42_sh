/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:46:25 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/25 15:22:59 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_param(char *param)
{
	int		i;

	i = 0;
	if (param[ft_strlen(param) - 1] == ':')
	{
		ft_putstr_fd("42 : bad substitution\n", 2);
		return (-1);
	}
	while (param[i])
	{
		if (param[i] == ':' &&
			(param[i + 1] != '-' && param[i + 1] != '+' &&
			param[i + 1] != '=' && param[i + 1] != '?'))
			return (-1);
		else
			return (0);
		i++;
	}
	return (0);
}

void	param_word_init(t_param_expan_st *param_word)
{
	param_word->word = NULL;
	param_word->param = NULL;
	param_word->type = 0;
	param_word->operation_type = 0;
}

char	*get_param_expan(char *param_expan)
{
	t_param_expan_st	param_word;
	char				*res;

	param_word_init(&param_word);
	if (!ft_strcmp("?", param_expan))
		return (ft_itoa(ft_get_last_rvalue(), 10));
	if (check_param(param_expan) < 0)
		return (NULL);
	split_param_expan(param_expan, &param_word);
	if (ft_isdigit(param_word.param[0]) && ft_isalphanum(param_word.param))
	{
		ft_strdel(&param_word.param);
		ft_strdel(&param_word.word);
		return (NULL);
	}
	res = operators_manager(&param_word);
	ft_strdel(&param_word.param);
	ft_strdel(&param_word.word);
	return (res);
}
