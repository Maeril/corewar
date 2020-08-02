/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:08:29 by myener            #+#    #+#             */
/*   Updated: 2020/08/02 18:45:48 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		asm_struct_tab_init(t_line *line, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		line[i].label = NULL;
		line[i].instruc = NULL;
		line[i].p1 = NULL;
		line[i].p2 = NULL;
		line[i].p3 = NULL;
		line[i].nb_param = 0;
		line[i].p1_sz = 0;
		line[i].p2_sz = 0;
		line[i].p3_sz = 0;
		line[i].line_cor_ln = 0;
		line[i].called_label = NULL;
		line[i].relative_cor_addr = 0;
		i++;
	}
}

int			main_free_helper(char *str1, char *str2, char **tab1, int err_out)
{
	str1 ? free(str1) : 0;
	str2 ? free(str2) : 0;
	tab1 ? tab_free(tab1) : 0;
	return (err_out ? error_output() : 0);
}

int			asm_struct_tab_free(t_line *l, int len, t_header *h, int r)
{
	int i;

	i = 0;
	h ? free(h) : 0;
	while (i < len)
	{
		l[i].label ? free(l[i].label) : 0;
		l[i].instruc ? free(l[i].instruc) : 0;
		l[i].p1 ? free(l[i].p1) : 0;
		l[i].p2 ? free(l[i].p2) : 0;
		l[i].p3 ? free(l[i].p3) : 0;
		l[i].called_label ? free(l[i].called_label) : 0;
		i++;
	}
	l ? free(l) : 0;
	return (r);
}

void		asm_tools_init(t_tools *tools)
{
	tools->name_filled = 0;
	tools->name_empty = 0;
	tools->com_filled = 0;
	tools->com_empty = 0;
	tools->bad_label = 0;
	tools->cor_line_counter = 0;
	tools->prog_size = 0;
	tools->tablen = 0;
	tools->fd = 0;
	tools->coding_byte = 0;
	tools->opcode = 0;
	tools->j = 0;
	tools->k = 0;
	tools->start = 0;
}
