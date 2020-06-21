/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:47:05 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 00:36:15 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int			header_fill(header_t *header, char **input, tools_t *tools)
{
	int		i;
	int		j;
	int		beg;
	char	*str;

	str = NULL;
	header->magic = COREWAR_EXEC_MAGIC;
	header->magic = swap_uint32(header->magic);
	i = 0;
	j = 0;
	if (bad_dot_line(input))
		return (0);
	while (input[i])
	{
		if (!ft_strncmp(input[i], NAME_CMD_STRING, 5) && tools->name_filled == 0)
		{
			j = 6;
			while (input[i][j] && input[i][j] != '"')
				j++;
			j++;
			beg = j++;
			while (input[i][j] && input[i][j] != '"')
				j++;
			if (j - beg > PROG_NAME_LENGTH)
				return(error_output()) ;
			str = ft_strsub(input[i], beg, j - beg);
			ft_strcpy(header->prog_name, str);
			tools->name_filled = 1;
		}
		else if (!ft_strncmp(input[i], COMMENT_CMD_STRING, 8) && tools->com_filled == 0)
		{
			str = NULL;
			j = 9;
			while (input[i][j] && input[i][j] != '"')
				j++;
			j++;
			beg = j++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
			while (input[i][j] && input[i][j] != '"')
				j++;
			if ((j - beg) > COMMENT_LENGTH)
				return (0); // OUTPUT ERROR AND EXIT
			str = ft_strsub(input[i], beg, j - beg);
			// ft_printf("comment = %s\n", str);
			ft_strcpy(header->comment, str);
			tools->com_filled = 1;
		}
		i++;
	}
	header->prog_size = tools->prog_size;
	header->prog_size = swap_uint32(header->prog_size);
	//else, do nothing. gotta check whether encountering >1 name or comment = error.
	return (1);
}
