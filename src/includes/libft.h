/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 01:23:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 17:46:15 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# define _CHAR 1
# define _INT 3
# define BUFF_SIZE 8192

typedef struct			s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}						t_list;

typedef struct			s_printf_params
{
	va_list	*list;
	char	*str;
	char	*format;
	int		padding;
	char	leading;
}						t_printf_params;

typedef struct			s_line
{
	int				fd;
	char			*str1;
	struct s_line	*next;
}						t_line;

size_t					ft_arraylen(char **ptr);
char					ft_isalphanum(char *str);
char					*ft_join(char *f, ...);
size_t					ft_nbrlen(long long int n, int base);
int						ft_isspace(char c);
char					*ft_strrepeat(char const *str, size_t count);
int						ft_strpos(char const *s1, char const *s2);
size_t					ft_strcount(char const *s, char const *s2);
t_list					*ft_lstrev(t_list *list);
int						ft_lstfold(t_list *list);
size_t					ft_lstcount(t_list *list);
char					*ft_strrev(char *str);
char					*ft_strrep(char const *s, char const *pattern,
							char const *replace);
char					*ft_strctrim(char const *str, char c);
void					ft_lstprint(t_list *list, int type);
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void					ft_lstadd(t_list **alst, t_list *new);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
char					*ft_strmapi(char const *s,
									char(*f)(unsigned int, char));
void					ft_putnbr_fd(int n, int fd);
void					ft_putendl_fd(char const *s, int fd);
int						ft_putstr_fd(char const *s, int fd);
int						ft_putchar_fd(char c, int fd);
void					ft_putnbr(int n);
void					ft_putendl(char const *s);
int						ft_putstr(char const *s);
void					ft_putchar(char c);
char					*ft_itoa(long long int n, int base);
char					**ft_strsplit(char const *s, char c);
char					*ft_strtrim(char const *s);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_fstrjoin(char const *s1, char const *s2);
char					*ft_strsub(char const *s, unsigned int start,
									size_t len);
char					*ft_fstrsub(char const *s, unsigned int start,
									size_t len);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strmap(char const *s, char (*f)(char));
void					ft_striteri(char *s, void(*f)(unsigned int, char *));
void					ft_striter(char *s, void(*f)(char *));
void					ft_strclr(char *s);
void					ft_strdel(char **as);
char					*ft_strnew(size_t size);
void					ft_memdel(void **ap);
void					*ft_memalloc(size_t size);
long long int			ft_atoi(const char *str);
int						ft_isprint(int c);
int						ft_isascii(int c);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_tolower(int c);
int						ft_toupper(int c);
int						ft_strcmp(const char *s1, const char *s2);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
									size_t n);
char					ft_isnumber(char *str);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strchr(const char *s, int c);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strncat(char *s1, const char *s2, size_t n);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strrchr(const char *s, int c);
char					*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strcpy(char *dst, const char *src);
size_t					ft_strlen(char const *s);
char					*ft_strdup(const char *s1);
char					*ft_strndup(const char *s1, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
int						get_next_line(int fd, char c, char **line);
int						ft_printf_fd(int fd, char *format, ...);
int						ft_getstr(t_printf_params *param, char fr);
void					ft_gethex(t_printf_params *param);
void					ft_getchar(t_printf_params *param);
void					ft_getint(t_printf_params *param);
int						ft_csd(t_printf_params *param);
void					ft_append(t_printf_params *param);
t_printf_params			*ft_init_printf(char *format);
int						ft_printf(char *format, ...);
int						ft_vprintf(int fd, va_list *list, char *format);
void					ft_getflags(t_printf_params *params);
void					ft_padding(int padding, char **str, char leading);
void					free_array(char **arr);
#endif
