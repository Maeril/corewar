/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:57:15 by myener            #+#    #+#             */
/*   Updated: 2020/06/20 21:39:33 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 4096
# define MAX_FD 8192
# define BIN "01"
# define OCT "01234567"
# define DECI "0123456789"
# define HEXL "0123456789abcdef"
# define HEXU "0123456789ABCDEF"
# define UINT_MAX 4294967296
# define INT_MAX 2147483647
# define INT_MIN -2147483648

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include "ft_printf/ft_printf.h"

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

char			*base_converter(char *nb, char *base_in, char *base_out);
int				ft_abs(int nb);
int				ft_atoi(const char *str);
int				ft_atoi_base(char *str, char *base);
long long int	ft_atoll(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_baselen(long long int n, int len);
char			*ft_free_join(const char *s1, const char *s2);
int				ft_intlen(long long int n);
int				ft_uintlen(unsigned long long int n);
int				ft_octlen(unsigned long long int n);
char			*ft_grabword(char *str, int start, int upper, int lower,
							int lownum);
int				ft_hexlen(unsigned long long int n);
float			ft_floatmod(float x, float y);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isalphalow(int c);
int				ft_isalphaup(int c);
int				ft_isascii(int c);
int				ft_isblank(int c);
int				ft_isdigit(int c);
int				ft_islownum(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
char			*ft_itoa_base(long long int n, const char *base);
char			ft_itoc(int n);
int				ft_linelen(char *stock);
char			*ft_lltoa(long long int n);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int nb);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr_base(long long int nb, const char *base);
void			ft_putnbr_base_fd(int fd, long long int nb, const char *base);
void			ft_putunbr_base(unsigned long long int nb, const char *base);
void			ft_putunbr_base_fd(int fd, unsigned long long int nb,
									const char *base);
void			ft_putstr(char *str);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putnbr_long(long long int nb);
void			ft_putunbr_long(unsigned long long int nb);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *str);
int				ft_strequ(const char *s1, const char *s2);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlcat(char *src, const char *dest, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *dest, const char *src, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strndup(const char *str, size_t n);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
size_t			ft_strnlen(const char *s, size_t maxlen);
char			*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strrev(char *str);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *str, const char *find);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strtrim(const char *s);
int				ft_tablen(char **tab);
int				ft_tablen_ignore_empty_lines(char **tab);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				get_next_line(const int fd, char **line);
void			tab_free(char **tab);
float			roundit_awayzero(float f);
float			roundit_towardzero(float f);
float			roundit_halfeven(float f);

#endif
