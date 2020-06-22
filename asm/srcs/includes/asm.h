/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 23:01:01 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 02:52:03 by myener           ###   ########.fr       */
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
}					t_tools;

typedef struct		s_line
{
	char			*label;
	char			*instruc;
	char			*param1;
	char			*param2;
	char			*param3;
	int				nb_param;
	int				param1_sz;
	int				param2_sz;
	int				param3_sz;
	int				line_cor_ln;
	char			*called_label;
	int				relative_cor_addr;
}					t_line;

void				asm_header_init(t_header *header);
void				asm_struct_tab_init(t_line *line, int len);
void				asm_tools_init(t_tools *tools);
int					asm_translator(int fd, char **input, t_tools *tools);
int					bad_dot_line(char **input);
void				decimal_to_hex_2scomplement(int fd, int value);
int					empty_or_comment_line(char *str);
int					error_output(void);
int					fill_tab_input(char **input, t_line *struct_tab,
					t_header *header, t_tools *tools);
int					fill_tab_sizes(t_line *tab, int len, t_tools *tools);
char				**get_file_content(char *file_name);
int					has_coding_byte(char *word);
int					has_label_size(char *word);
int					has_one_param(char *word);
int					has_two_params(char *word);
int					has_three_params(char *word);
int					header_fill(t_header *header, char **input, t_tools *tools);
int					is_called_label(char *str, int write_size);
int					is_instruc(char *word);
int					is_legit_label(char *label, t_line *tab, int len);
char				*string_cleaner(char *str);
int					struct_tab_fill(char **input, t_line *struct_tab,
					t_header *header, t_tools *tools);
unsigned int		swap_uint32(unsigned int nb);
int					usage_output(void);
int					write_to_cor(t_line *tab, t_header *header, t_tools *tools);

#endif
