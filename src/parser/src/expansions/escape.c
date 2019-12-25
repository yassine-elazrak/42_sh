/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:26:26 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/20 18:28:35 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_esc_char(char *str, char c)
{
	if (c == 'n')
		join_char(&str, '\n');
	else if (c == 't')
		join_char(&str, '\t');
	else if (c == 'r')
		join_char(&str, '\r');
	else if (c == 'v')
		join_char(&str, '\v');
	else if (c == 'f')
		join_char(&str, '\f');
	else
		join_char(&str, c);
	return (str);
}
