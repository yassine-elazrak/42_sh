/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expan.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:15:28 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/24 19:32:15 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_EXPAN_H
# define PARAM_EXPAN_H
# include "libft.h"
# include "datatypes.h"

typedef struct	s_param_expan_st
{
	char	*word;
	char	*param;
	t_map	*map;
	char	type;
	char	operation_type;
}				t_param_expan_st;

typedef struct	s_mtools
{
	char	pattern_size;
	int		i_src;
	int		i_preffix;
	int		i_suffix;
	int		ret;
	char	*src;
	char	*preffix;
	char	*suffix;
}				t_mtools;

char			*delet_adds_stars(char *str, char c);
char			*rm_suffix(t_param_expan_st *p_w);
char			*rm_preffix(t_param_expan_st *p_w);
char			*rm_ffixers(t_param_expan_st *param_word);
char			*operators_manager(t_param_expan_st *param_word);
void			split_param_expan(char *param_expan,
					t_param_expan_st *param_word);
char			*get_param_expan(char *param_expan);

#endif
