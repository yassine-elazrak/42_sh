/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:06:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 17:54:58 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H
# include "datatypes.h"
# define M tmp
# define ONE_C(i) M[i] != -2 && M[i] != -3 && M[i] != -1 && M[i] != BG
# define TWO_C(i) M[i] != -5 && M[i] != -4
# define IS_STOP_CHAR(i) TWO_C(i) && ONE_C(i)

void	ft_autocomplete_42(t_init *init);
char	*ft_take_to_complte_42(t_init *init);
int		ft_is_first_word_42(char *line, t_init *init);
int		ft_if_is_dir(char *to_complete, char **path,
	char **new_to_complete, char **tilda);
int		ft_if_is_dir_2(char **to_complete, char **path,
	char **new_to_complete, char **tilda);
t_auto	*ft_get_completion_path_42(t_init *init);
t_auto	*add_to_auto_42(t_auto *lst, char *str);
t_auto	*ft_get_completion_built_42(t_init *init, t_auto **lst);
void	ft_get_completion_from_x(t_init *init, char *line);
t_auto	*ft_get_completion_env_var_42(t_init *init);
int		ft_is_var(char *to_complete);
void	ft_get_completion_dir_42(t_init *init);
t_auto	*ft_search_complete_dir_42(char *to_complete, char *directory);
int		ft_max_len_lst_42(t_auto *lst, int *lst_len);
void	ft_print_completion_42(t_init *init);
void	replace_the_auto_comlete_42(t_init *init, char *completion);
void	ft_ls_print_42(t_auto *lst, int print_len, int lst_len);
int		ft_8_multipl(int l);
char	*ft_max_completion(t_auto *lst);
void	ft_print_max_completion(t_init *init, char *to_complete,
	char *max_completion);
int		ft_cursor_position(char *s, int cursor);
int		ft_char_exist(t_auto *lst, int i, char *min_completion);
void	ft_free_auto_lst(t_auto **lst);
int		ft_free_return(char **to_complete, int ret);
int		ft_free_return_2(char **tmp, char *to_complete, int ret);

#endif
