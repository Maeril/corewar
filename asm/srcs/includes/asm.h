/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 23:01:01 by myener            #+#    #+#             */
/*   Updated: 2020/07/01 06:01:18 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "op.h"

typedef	struct		s_tools
{
	bool			name_filled;
	bool			com_filled;
	int				cor_line_counter;
	int				prog_size;
	int				tablen;
	int				fd;
	int				coding_byte;
	int				opcode;
	int				j;
	int				k;
	int				start;
}					t_tools;

typedef struct		s_line
{
	char			*label;
	char			*instruc;
	char			*p1;
	char			*p2;
	char			*p3;
	int				nb_param;
	int				p1_sz;
	int				p2_sz;
	int				p3_sz;
	int				line_cor_ln;
	char			*called_label;
	int				relative_cor_addr;
}					t_line;

void				asm_header_init(t_header *header);
void				asm_struct_tab_init(t_line *line, int len);
void				asm_struct_tab_free(t_line *line, int len, t_header	*head);
void				asm_tools_init(t_tools *tools);
int					asm_translator(int fd, char **input, t_tools *tools);
int					bad_dot_line(char **input);
void				decimal_to_hex_2scomplement(int fd, int value);
int					empty_or_comment_line(char *str);
int					error_output(void);
int					fill_tab_input(char **input, t_line *struct_tab,
					t_tools *tools);
int					fill_tab_sizes(t_line *tab, t_tools *tools);
char				*get_coding_byte_helper(char *byte, char c, int sz);
char				**get_file_content(char *file_name);
char				*get_param(t_line *tab, int i, char *param);
int					get_param_sz(char *param, int label_size);
int					has_cb(char *word);
int					has_label_size(char *word);
int					has_one_param(char *word);
int					has_two_params(char *word);
int					has_three_params(char *word);
int					header_fill(t_header *header, char **input, t_tools *tools);
int					is_called_label(char *str, int write_size);
int					is_instruc(char *word);
int					is_legit_label(char *label, t_line *tab, int len);
int					lines_to_deduce(char **input);
int					main_free_helper(char *str1, char *str2, char **tab1,
					int err_out);
int					stock_instruct_clean_free(char *n, int ret);
char				*string_cleaner(char *str);
int					struct_tab_fill(char **input, t_line *struct_tab,
					t_tools *tools);
unsigned int		swap_uint32(unsigned int nb);
int					usage_output(void);
int					write_to_cor(t_line *tab, t_header *header, t_tools *tools);

#endif
