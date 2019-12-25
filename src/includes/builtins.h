/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:18:09 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 22:01:05 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "shell.h"
# define COUNT 1000
# define INTERN 1
# define ALIAS 2
# define COMMANDS 3
# define ANYHASH 4
# define EXPORTED 0
# define INCLUDE_UNEXPORTED 1
# define EXPORTED_ONLY 2
# define KEYS_ONLY 4
# define BINARY 0
# define UNARY 1
# define MAXNBR "9223372036854775807"

typedef int			t_function(char **args);

t_function			*ft_is_builtin(char *arg);
void				ft_init_builtins(char **env);
char				*ft_getenv(char *key);
char				ft_isalphanum(char *str);

/*
** ft_getopt
*/

int					ft_getopt(char **args, char *buffer, char *valid);

/*
** ft_serialize_env():
** @param {exportd}: [INCLUDE_UNEXPORTED | EXPORTED_ONLY | KEYS_ONLY]
** get a (char **) version of the envirenment , return value may
** include unexported intern variables when `INCLUDE_UNEXPORTED` is specified
*/

char				**ft_serialize_env(char exported);

int					ft_export(char **args);
int					ft_printenv(char *options);
int					ft_set(void);
int					ft_unset(char **args);

/*
** HASHMAP
*/

int					ft_hash_calc(char *key);
void				ft_empty(char freeall);
void				ft_init_hash(void);
void				ft_hashdelete_one(char *key, char type);
int					ft_hash(char **args);
int					ft_print_hash_list(void);
t_map				*ft_addtohashmap(char *key, char *value, char type);
t_map				*ft_getbykey(char *key, char type);
char				*ft_getvlaue_bykey(char *key, char type);
void				ft_get_kv(char *str, char **key, char **val);

/*
** CD
*/

char				*cdpath_concatenation(char *cdpath, char *directory);
int					cd_wheels(t_recipes *recipes);
void				recipes_preparations(t_recipes *recipes);
char				check_param_for_cd(char *param);
int					errors_container(char *curpath, int err);
int					chdir_operations(t_recipes *recipes);
int					ft_cd(char **args);

/*
** EXIT
*/

int					ft_exit(char **argv);
char				ft_exitcode(char *arg, uint8_t *code);

/*
** FC
*/

int					ft_run_fc_editor(char **args);
int					ft_fc(char **args);
int					ft_test(char **args);

/*
** ALIAS
*/

void				ft_show_aliases(char *key);
int					ft_alias(char **args);
int					ft_unalias(char **cmd);
char				**ft_getaliaskeys(void);

/*
** ECHO
*/

int					ft_echo(char **args);

/*
** JOBCONTROL BUILTINS
*/

int					ft_fg(char **arg);
int					ft_bg(char **arg);
int					ft_jobs(char **args);

/*
** TEST
*/

int					ft_type(char **args);
int					ft_usergroup(int id, char *file);
int					ft_rwx(int id, char *file);
int					ft_getoperator_id(char *oper, char type);
int					ft_getoprators(char **args,
						char **l_oper, char **oper, char **r_oper);
char				*ft_isnbr(char *str);
int					ft_eval(int id, char *file);
void				ft_setoprations(void);
int					ft_strtest(int id, char *l_oper, char *r_oper);
int					ft_sizetest(char *file);
int					ft_mathcmp(int id, char *n1, char *n2);
int					ft_expression(char *expr);
int					ft_maxinteger(char *nb, int sign);
/*
** intern
*/

char				ft_isintern(char *cmd);
void				ft_getinterns(t_process *process, char type);
void				ft_cpyenv(t_params *p);
void				ft_add_to_tmp_map(t_params *p, char *key, char *value);

#endif
