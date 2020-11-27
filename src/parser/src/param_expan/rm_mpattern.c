/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_mpattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:59:34 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/26 01:57:51 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	aff_err(t_param_expan_st *p_w)
{
	ft_printf_fd(2, "42sh: %s: ", p_w->param);
	if (!p_w->word || !ft_strlen(p_w->word))
		ft_putendl_fd("parameter null or not set", 2);
	else
		ft_putendl_fd(p_w->word, 2);
}

char	*delet_adds_stars(char *str, char c)
{
	int		i;
	char	*tmp1;

	i = 0;
	tmp1 = ft_strnew(0);
	while (str[i])
	{
		if (str[i] != c || (i > 0 && (str[i - 1] == Q_ESCAPE &&
						str[i - 1] == UQ_ESCAPE)))
		{
			tmp1 = ft_join("%f%f", tmp1, ft_strsub(str, i, 1));
			i++;
		}
		else
		{
			tmp1 = ft_join("%f%f", tmp1, ft_strsub(str, i, 1));
			i++;
			while (str[i] == c && str[i])
				i++;
		}
	}
	free(str);
	return (tmp1);
}

char	*rm_ffixers(t_param_expan_st *param_word)
{
	if (param_word->operation_type == 's' ||
			param_word->operation_type == 'S')
		return (rm_suffix(param_word));
	if (param_word->operation_type == 'B' ||
			param_word->operation_type == 'b')
		return (rm_preffix(param_word));
	return (ft_itoa((int)ft_strlen(ft_getvlaue_bykey(param_word->param,
						INTERN)), 10));
}
