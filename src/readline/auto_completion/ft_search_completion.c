/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_completion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:50:19 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 16:44:14 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_loup_to_env_var(char **env, char *to_complete, t_auto **lst)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(to_complete);
	while (env[i])
	{
		if (ft_strncmp(env[i], to_complete, len) == 0)
			(*lst) = add_to_auto_42((*lst), env[i]);
		i++;
	}
}

t_auto	*ft_get_completion_env_var_42(t_init *init)
{
	t_auto	*lst;
	char	**env;
	int		i;
	int		n;
	char	*to_complete;

	to_complete = init->to_complete;
	n = ft_is_var(to_complete);
	i = 0;
	lst = NULL;
	if (n == 1)
	{
		env = ft_serialize_env(INCLUDE_UNEXPORTED | KEYS_ONLY);
		while (to_complete[i] && to_complete[i] != '$')
			i++;
		if (to_complete[i] && to_complete[i] == '$' &&
			to_complete[i + 1] == '{')
			i++;
		to_complete = &(to_complete[i + 1]);
		i = 0;
		ft_loup_to_env_var(env, to_complete, &lst);
		ft_free_array(env);
	}
	return (lst);
}

void	ft_get_completion_42(t_init *init, char from)
{
	if (from == 'C')
	{
		init->completion_lst = ft_get_completion_path_42(init);
		init->completion_lst =
		ft_get_completion_built_42(init, &(init->completion_lst));
	}
	else if (from == 'V')
		init->completion_lst = ft_get_completion_env_var_42(init);
	else if (from == 'D')
		ft_get_completion_dir_42(init);
}

void	ft_get_completion_as_cmd(t_init *init)
{
	ft_get_completion_42(init, 'D');
	if (init->completion_lst == NULL)
	{
		ft_get_completion_42(init, 'V');
		if (init->completion_lst == NULL)
			if (init->to_complete != NULL)
				ft_get_completion_42(init, 'C');
	}
}

void	ft_get_completion_from_x(t_init *init, char *line)
{
	char	*tmp;
	int		ret;

	ret = ft_is_first_word_42(line, init);
	if (ret != 1)
	{
		if (ret == 2)
		{
			tmp = init->to_complete;
			init->to_complete = ft_strtrim(init->to_complete);
			ft_strdel(&tmp);
		}
		ft_get_completion_as_cmd(init);
	}
	else
	{
		ft_get_completion_42(init, 'D');
		if (init->completion_lst == NULL)
		{
			ft_get_completion_42(init, 'V');
			if (init->completion_lst == NULL)
				init->completion_lst =
				ft_search_complete_dir_42(init->to_complete, ".");
		}
	}
}
