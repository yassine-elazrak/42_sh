# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:55:55 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/24 09:59:10 by yoyassin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libparser.a
SRC = src
BUILD = .build
INC = ../includes
HDRS = ../includes/shell.h ../includes/parser.h ../includes/param_expan.h
LIB = libft
CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDE = -I$(INC) -I$(LIB)/includes
SRC_SUBDIRS = expansions parsing param_expan

SRC_PARAM_EXPAN = $(addprefix param_expan/, params_expan.c rm_mpattern.c params_expan_operaters.c split_param_word.c rm_preffix.c rm_suffix.c)
SRC_EXPANSION = $(addprefix expansions/, assignments.c alias_utility_funcs.c param_subst.c param_exp_utils.c convert_args.c misc.c tokenize.c control_substitution.c alias_expansion.c tild_expansion.c escape.c exp_helper_funcs.c exp_helper_funcs2.c expansions.c)
SRC_PARSING = $(addprefix parsing/, subst_syntax.c syntax_check_utils.c operators.c build_job_list.c build_parse_list.c parse.c parse_heredoc.c parse_redir.c parse_redir2.c pre_parsing.c special_chars.c syntax_checking.c utility_funcs.c)
SRCS = $(SRC_EXPANSION) $(SRC_PARSING) $(SRC_PARAM_EXPAN)
OBJECT = $(addprefix $(BUILD)/, $(SRCS:.c=.o))
OBJ_DIRS = $(addprefix $(BUILD)/, $(SRC_SUBDIRS))

# all:
# 	$(info $$OBJ_DIRS is [${OBJ_DIRS}])

all: $(NAME)

$(NAME): $(OBJECT)
	ar rc $(NAME) $(OBJECT)

$(OBJECT): $(BUILD)/%.o : $(SRC)/%.c $(HDRS) | $(BUILD)
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(BUILD):
	mkdir $(BUILD)
	mkdir $(OBJ_DIRS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -rf $(NAME)

re : fclean all
