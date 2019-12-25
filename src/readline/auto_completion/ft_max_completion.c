/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 16:29:20 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 17:12:21 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_get_the_max_completion(char *max_completion,
	char *tilda, char *path, char **completion)
{
	if (tilda)
		*completion = ft_strjoin(tilda, max_completion);
	else
		*completion = ft_strjoin(path, max_completion);
	ft_strdel(&path);
	ft_strdel(&tilda);
}

char	*ft_min_completion(t_auto *lst)
{
	char	*str;
	size_t	min_len;

	str = lst->str;
	min_len = ft_strlen(lst->str);
	while (lst)
	{
		if (ft_strlen(lst->str) < min_len)
		{
			min_len = ft_strlen(lst->str);
			str = lst->str;
		}
		lst = lst->next;
	}
	return (str);
}

char	*ft_max_completion(t_auto *lst)
{
	char	*min_cplt;
	int		i;
	char	*str;

	i = 0;
	min_cplt = ft_min_completion(lst);
	while (min_cplt && min_cplt[i])
	{
		if (ft_char_exist(lst, i, min_cplt))
			i++;
		else
			break ;
	}
	if (i)
	{
		str = ft_strsub(min_cplt, 0, i);
		return (str);
	}
	return (NULL);
}

void	ft_if_is_var(char *to_complete,
	char **completion, char *max_completion)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (to_complete[i] && to_complete[i] != '$')
		i++;
	if (to_complete[i] && to_complete[i] == '$' &&
	to_complete[i + 1] == '{')
		i++;
	str = ft_strsub(to_complete, 0, i + 1);
	*completion = ft_strjoin(str, (max_completion));
	ft_strdel(&str);
}

void	ft_print_max_completion(t_init *init,
	char *to_complete, char *max_completion)
{
	char	*completion;
	char	*str;
	char	*path;
	char	*tilda;

	completion = NULL;
	str = NULL;
	tilda = NULL;
	if (ft_is_var(to_complete) == 1)
		ft_if_is_var(to_complete, &completion, max_completion);
	else if (ft_if_is_dir_2(&to_complete, &path, &str, &tilda) == 1)
		ft_get_the_max_completion(max_completion, tilda, path, &completion);
	else
		completion = ft_strdup(max_completion);
	ft_strdel(&to_complete);
	replace_the_auto_comlete_42(init, completion);
	ft_strdel(&completion);
}
