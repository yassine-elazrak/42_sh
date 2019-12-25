/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:46:41 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 10:01:37 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <sys/wait.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include "datatypes.h"
# include "param_expan.h"
# define SEMI_COL -1
# define BLANK -2
# define PIPE -3
# define AND -4
# define OR -5
# define BOTH_FDS -6
# define CLOSE_FD -7
# define HEREDOC -8
# define QUOTE -9
# define D_QUOTE -10
# define OUT_RED_OP -11
# define IN_RED_OP -12
# define APP_OUT_RED_OP -13
# define HEREDOC_OP -14
# define FD_AGGR -15
# define UQ_ESCAPE -16
# define Q_ESCAPE -17
# define DOLLAR -18
# define TILDE -19
# define BG -20
# define IS_REDIRECTION str[i] == -11 || str[i] == -12 || str[i] == -13
# define _OR ||
# define _AND &&
# define _EQ ==
# define _NEQ !=
# define S -1
# define P -3
# define O -11
# define R -12
# define B -20
# define A -13
# define H -14
# define L line
# define TCO(i, _O, C) L[i] C -4 _O L[i] C -5 _O L[i] C -13 _O L[i] C -14
# define OCO(i, _O, C) L[i] C S _O L[i] C P _O L[i] C O _O L[i] C R _O L[i] C B
# define IS_OPERATOR(i, _O, C) TCO(i, _O, C) _O OCO(i, _O, C)
# define IS_REDIR_OP(i, _O, C) L[i] C O _O L[i] C R _O L[i] C A _O L[i] C H
# define AT(i) (i - 1 > 0) ? i - 1 : 0
# define NEQ_ESCAPE(i) L[AT(i)] != -16 && L[AT(i)] != -17
# define LEFT_OPR 0b00000001
# define RIGHT_OPR 0b00000010
# define PARAMS (void *)head, (void *)&curr, (void *)tail
# define APPEND(type) append_lst(PARAMS, type)
# define SETFLAG(type) set_flag(curr, token[j], type)
# define DUPL(str) ft_strdup(str)
# define _PARAM(x) get_dollar_var(tmp, &i, x)
# define INDEX(i) (i - 1 > 0) ? i - 1 : 0
# define IS_DOLLAR(dq) is_dollar(L, i, dq)
# define IS_EMPTY (!(*i) || str[*i - 1] == BLANK || ft_isalpha(str[*i - 1]))
# define T str
# define PR ft_isprint
# define PART_OF_EOF (PR(T[*i]) || T[*i] == -16 || T[*i] == -17 || T[*i] == -18)

typedef	struct	s_token
{
	char			**list;
	char			type;
	struct s_token	*sub;
	struct s_token	*next;
}				t_token;

typedef	struct	s_arg
{
	char			**arg;
	struct s_arg	*next;
}				t_arg;

typedef	struct	s_alias
{
	char			*key;
	struct s_alias	*next;
}				t_alias;

char			*pre_parse(char *line);
void			highlight_ops(char *line);
int				syntax_error(char **line);
void			mark_operators(char *line);
int				dc_operator(char *line, int i);
int				sc_operator(char *line, int i);
int				get_bg_jobs(char *line);
void			mark_bg_op(char *line);
t_job			*parse(char *input);
void			check_wildcard_c(char **line);
int				dquotes_checker(char **line, char *dq, int *i, int *j);
int				squotes_checker(char **line, char *q, int *i);
int				check_syntax_errors(char *line);
int				correct_syntax(char *param);
int				valid_parameter(char *param, char type);
int				subst_syntax(char *line);
t_job			*get_jobs(char **cmd_chain, int	bg);
t_process		*get_process_list(char *cmd_chain, char type);
void			append_lst(void **h, void **c, void **t, char type);
int				set_flag(void *curr, int flag, char type);
char			*skip_operators(char type, char *token, int *start, int *j);
int				get_list_node(char type, void **curr, char *str);
char			*check_redirections(char *str, t_process *cmd);
char			escape_char(char c);
void			get_redir_type(t_redir *curr, char *str, int i);
int				get_redir_fds(t_redir *curr, char *str, int *i);
void			get_redir_file(t_redir *curr, char *str, int *i);
char			*get_heredoc(char *str, int *i, int *hd_fd);
void			remove_unwanted_chars(char **eof,
				char *str, int old_i, int i);
int				is_not_blank(char *line, int j, int i);
void			apply_expansions(t_process *process);
char			**get_assignments(char ***args);
void			free_arg_list(t_arg **h);
void			valid_assignment(char *args, char *flag, int pos);
int				expand_and_append(t_arg **h, t_arg **t, char ***args);
void			store_args(t_arg *c, char **args, int *size);
char			**convert_args(t_arg *h, int size);
int				expand(char **args, t_arg *c);
void			search_and_expand(char **s);
char			*get_param(char **param, char op);
char			*get_dollar_var(char *tmp, int *i, char op);
t_token			*alias_expansion(char *line);
char			*gather_tokens(t_token *tokens);
char			*rc(t_token *tokens);
void			ctl_subst(char *s, char *tmp, char **str, char type);
char			*control_subtitution(char *token, char type);
void			expand_param(char **s);
int				apply_glob_expansion(char *gl_pattern, char **args);
void			quotes_delimiter(char **tmp);
int				is_not_blank(char *line, int j, int i);
int				is_word(char *word);
char			*get_esc_char(char *str, char c);
char			*get_substring(char *str, int *k, char type);
void			expand_dollar(char *dollar, char **args, int *j, int length);
void			expand_tilde(char **args);
void			quoted_escape(char **arg);
void			remove_quotes(char **args);
void			remove_escapes(char **str, char escape);
char			*tild_expan(char *tild_str);
void			join_char(char **str, char c);
void			update_string(char **str, int *j);
void			add_spaces(char **str);
void			combine(t_token *tokens, char **str);
int				is_quoted(char *s, int len);
int				match(t_alias *h, t_alias *t);
void			free_list(t_alias *h, t_alias **t);
void			free_tokens(t_token *tokens);
char			*extact_arg(t_token *tokens, int *i);
void			replace(t_token *tokens, t_alias *t, int i);
t_token			*get_tokens(t_token **head, char *cmd_chain);

#endif
