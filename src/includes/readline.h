/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 19:33:17 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/24 14:59:46 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H
# include "autocomplete.h"
# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <termios.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include "datatypes.h"

int				g_sig;
int				g_sig_win;
void			ft_init_free(void);
char			*ft_cmd_mangement__(char *str, t_init *init);
char			*call_esqp(char *str, t_init *init);
int				ft_cke_c_eskip(int i, char *str);
void			ft_string_cmd(int flg, t_init *init);
void			ft_name(char **line);
int				my_putchar(int c);
int				key_4_of_cursor(char *str, t_init *init);
char			*move_cursor_and_mangemant_fonction(char *str,
t_init *init);
void			ft_init_output(t_init *init);
void			ft_init_cmd(t_init *init);
void			ft_init_output(t_init *init);
char			*ft_read(char *buffer, int position, t_init *init);
void			del_char_of_line(char **line, t_init *init);
void			ft_cat_string_of_line(t_init *init, char *str);
void			ft_catch_sig();
void			ft_init_terminal();
int				key_slect(char *str, t_init *init);
void			ft_exec_ket_s(t_init *init);
void			ft_move_mul_line(t_init *init, char *str);
void			ft_put_clor(t_init *init, char *str);
void			ft_size_terminal(t_init *init);
char			*readline(t_init *init, char *promt);
void			end_cursor(t_init *init);
void			home_cursor(t_init *init);
void			ft_move(t_init *init, char *str, int a);
int				line_lfet(t_init *init, int e_d);
void			ft_alt_up_2(int *x, int *a, t_init *init);
void			ft_refrech(t_init *init);
int				get_strat(t_init *init, int e_d);
void			end_cursor_2(t_init *init);
void			home_cursor_2(t_init *init);
int				get_end(t_init *init, int e_d);
void			ft_put_move(t_init *init, int i);
char			*ft_qoute(char *str, t_init *init);
void			ft_init_qote(t_init *init);
char			*ft_take_move(t_init *init,
char *buffer, int position);
void			ft_init_s_00(t_init *init);
void			ft_del_str(t_init *init, int a);
void			ft_alt_down(int *x, int *a, t_init *init);
void			ft_alt_up(int *x, int *x1, int *a, t_init *init);
int				ft_check_key(t_init *init, char *str);
void			ft_str_line(char *str, t_init *init);
char			*call_qote(t_init *init, char c, char *str);
void			ft_print_(char *str, t_init *init);
int				ft_tab_(t_init *init, int e_d);
void			ft_init_readline(t_init *init);
void			ft_write_file(t_init *init);
void			ft_read_file_(t_init *init);
void			ft_add_history_(t_init *init, char *line, int i);
char			*ft_expansion(t_init *init, char *str);
char			*get_arg(char *key);
int				ft_print___(char *options, char **args, int fd);
char			*ft_rep_lace(char *str, char *dst);
char			*readline_(t_init *init, char *promt);
char			*ft_qoute__fin(t_init *init);
char			*ft_check_qout(char *str, t_init *init);
char			*ft_search_(char *str, t_init *init);
void			ft_move_left(t_init *init);
void			ft_move_right(t_init *init);
int				get_(char *str);
char			*ft_get_data(t_init *init, char *str);
void			ft_new_history_(t_init *init, char *line);
int				read_file_(char *fille);
char			*get_name_randm(void);
int				ft_printusage(int c);
int				ft_printerror(void);
void			ft_chang_size(void);
int				get_start_end(int *s, int *e, char **args);

#endif
