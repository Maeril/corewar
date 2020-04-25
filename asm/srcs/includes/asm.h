/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 23:01:01 by myener            #+#    #+#             */
/*   Updated: 2020/04/26 01:05:03 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "op.h"

typedef	struct		s_tools
{
	bool	name_filled;
	bool	com_filled;
}					t_tools;

typedef struct		s_line
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
}					t_line;

void	asm_header_init(header_t *header);
void	asm_struct_tab_init(t_line *line);
void	asm_tools_init(t_tools *tools);
void	asm_translator(int fd, char **input, t_tools *tools);
char	**get_file_content(char *file_name);
int		has_one_param(char *word);
int		has_two_params(char *word);
int		has_three_params(char *word);
int		is_instruc(char *word);

#endif



