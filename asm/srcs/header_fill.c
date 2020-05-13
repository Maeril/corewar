/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:47:05 by myener            #+#    #+#             */
/*   Updated: 2020/05/13 03:23:45 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void			header_fill(header_t *header, char **input, tools_t *tools)
{
	int		i;
	int		beg;
	char	*str;

	str = NULL;
	header->magic = COREWAR_EXEC_MAGIC;
	header->magic = swap_uint32(header->magic);
	i = 0;
	if (!ft_strncmp(input[0], NAME_CMD_STRING, 5) && tools->name_filled == 0)
	{
		i = 6;
		while (input[0][i] && input[0][i] != '"')
			i++;
		i++;
		beg = i++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
		while (input[0][i] && input[0][i] != '"')
			i++;
		if (i - beg > PROG_NAME_LENGTH)
			return ; // OUTPUT ERROR AND EXIT
		str = ft_strsub(input[0], beg, i - beg);
		ft_strcpy(header->prog_name, str);
		tools->name_filled = 1;
	}
	if (!ft_strncmp(input[1], COMMENT_CMD_STRING, 8) && tools->com_filled == 0)
	{
		str = NULL;
		i = 9;
		while (input[1][i] && input[1][i] != '"')
			i++;
		i++;
		beg = i++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
		while (input[1][i] && input[1][i] != '"')
			i++;
		if ((i - beg) > COMMENT_LENGTH)
			return ; // OUTPUT ERROR AND EXIT
		str = ft_strsub(input[1], beg, i - beg);
		ft_strcpy(header->comment, str);
		tools->com_filled = 1;
	}
	header->prog_size = tools->prog_size;
	header->prog_size = swap_uint32(header->prog_size);
	//else, do nothing. gotta check whether encountering >1 name or comment = error.
}
