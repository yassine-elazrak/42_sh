/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 11:20:45 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H
# include "libft.h"
# include <termios.h>
# define BUILTINS_COUNT 15
# define TESTFUNCTIONS_COUNT 20
# include <sys/stat.h>

typedef struct			s_auto
{
	char				*str;
	struct s_auto		*next;
	struct s_auto		*prev;
}						t_auto;

typedef struct			s_sle_c
{
	int		cp;
	int		cpd;
	int		s_t;
	int		e_d;
	int		pass;
	int		cp_end;
	int		cp_st;
	int		selection;
}						t_sle_c;

typedef struct			s_history
{
	char				*str;
	int					index;
	struct s_history	*next;
	struct s_history	*prvet;
}						t_history;

typedef struct			s_init
{
	char			*to_complete;
	int				skip_read;
	int				s_col;
	int				s_l;
	int				s_line;
	int				x0;
	int				y0;
	int				qoute;
	char			*kote;
	char			qt;
	int				search;
	char			*str_search;
	int				esq;
	char			*key;
	int				s_cursor;
	char			*out_put;
	t_sle_c			s;
	char			*tmp;
	struct termios	term_copy;
	int				heredoc_int;
	char			*heredoc_str;
	t_history		*history;
	t_history		*history_postoin;
	t_history		*last_history;
	int				index;
	int				auto_comlpetion;
	t_auto			*completion_lst;
	t_auto			*completion_lst_position;
	char			*promt;
	int				z0;
}						t_init;

typedef struct			s_redir
{
	int				type;
	int				src_fd;
	int				dst_fd;
	char			*file;
	struct s_redir	*next;
}						t_redir;

typedef struct			s_process
{
	char				**arg;
	char				**ass;
	char				**holder;
	pid_t				pid;
	int					status;
	t_redir				*redir;
	int					flag;
	char				*heredoc;
	int					heredoc_fd;
	char				exited;
	char				stoped;
	char				*name;
	char				signaled;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	t_process		*processes;
	pid_t			pgid;
	char			*command;
	int				return_val;
	int				flag;
	int				id;
	char			suspended;
	char			killed;
	char			foreground;
	char			notified;
	char			sub;
	struct s_job	*next;
}						t_job;

typedef struct			s_map
{
	void	*key;
	void	*value;
	int		hits;
	char	type;
	char	exported;
}						t_map;

typedef struct			s_shell
{
	char				interractive;
	char				subshell;
	char				*pwd;
	t_map				builtins[BUILTINS_COUNT];
	t_list				**hashmap;
	t_job				*jobs;
	t_init				*init;
	int					last_exit;
	char				abort;
	t_list				**tmpvars;
	t_list				*newmaps;
}						t_shell;

typedef struct			s_params
{
	int				forkbuiltins;
	int				pipe_stdin;
	int				fdscopy[2];
	t_job			*job;
}						t_params;

typedef struct			s_container
{
	t_list			*list;
	t_job			*current;
	t_list			*notify;
	t_job			*prev;
	uint8_t			last_status;
	char			time_to_exit;
	int				stdcopy;
	t_list			*last_aliases;
	t_params		*params;
	t_list			*env;
	t_job			*jobs;
	char			**test_operators;
	t_map			testfunctions[20];
	int				test[8];
	struct termios	*term;
}						t_container;

typedef struct			s_recipes
{
	char			*oldpwd;
	char			*pwd;
	char			*home;
	char			*cdpath;
	char			*second_curpath;
	char			*curpath;
	char			options;
	char			*cwd;
	char			*tmp;
	char			**paths;
	int				mute;
	int				error;
	struct stat		buf;
}						t_recipes;

#endif
