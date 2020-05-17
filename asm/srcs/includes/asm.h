/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 23:01:01 by myener            #+#    #+#             */
/*   Updated: 2020/05/18 00:19:54 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "op.h"

typedef	struct		tools_s
{
	bool	name_filled;
	bool	com_filled;
	int		cor_line_counter;
	int		prog_size;
}					tools_t;

typedef struct		line_s
{
	char			*label;
	char			*instruc; // instruction name
	char			*param1;
	char			*param2;
	char			*param3;
	int				nb_param;
	int				param1_sz; // (in bytes - namely 2 or 4)
	int				param2_sz;
	int				param3_sz;
	int				line_cor_ln; // line length in the cor file (that is, w/o the label)
	char			*called_label; // if another label is called on this line
	int				relative_cor_addr; // current line's relative address in the cor file (which will allow us to deduce the relative address of the called label if there is one)
}					line_t;

void			asm_header_init(header_t *header);
void			asm_struct_tab_init(line_t *line, int len);
void			asm_tools_init(tools_t *tools);
int				asm_translator(int fd, char **input, tools_t *tools);
int				bad_dot_line(char **input);
void			decimal_to_hex_2scomplement(int fd, int value);
int				empty_or_comment_line(char *str);
int				error_output(void);
int				fill_tab_input(char **input, line_t *struct_tab, header_t *header, tools_t *tools);
int				fill_tab_sizes(line_t *tab, int len, tools_t *tools);
char			**get_file_content(char *file_name);
int				has_coding_byte(char *word);
int				has_label_size(char *word);
int				has_one_param(char *word);
int				has_two_params(char *word);
int				has_three_params(char *word);
int				header_fill(header_t *header, char **input, tools_t *tools);
int				is_called_label(char *str, int write_size);
int				is_instruc(char *word);
int				is_legit_label(char *label, line_t *tab, int len);
char			*string_cleaner(char *str);
int				struct_tab_fill(char **input, line_t *struct_tab, header_t *header, tools_t *tools);
unsigned int	swap_uint32(unsigned int nb); // for little to big endian conversion
int				usage_output(void);
int				write_to_cor(line_t *tab, header_t *header, int len, int fd);


#endif



