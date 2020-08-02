/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:47:05 by myener            #+#    #+#             */
/*   Updated: 2020/08/02 20:15:36 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	fill_name(t_header *header, char **input, t_tools *tools, int i)
{
	int		j;
	int		beg;
	char	*str;

	str = NULL;
	j = 6;
	while (input[i][j] && input[i][j] != '"')
		j++;
	j++;
	input[i][j] == '"' ? ft_strcpy(header->prog_name, "") : 0;
	if (input[i][j] == '"')
		return (tools->name_empty = 1);
	beg = j++;
	while (input[i][j] && input[i][j] != '"')
		j++;
	if ((j - beg) > PROG_NAME_LENGTH)
		return (0);
	str = ft_strsub2(input[i], beg, j - beg);
	ft_strchr(str, '\n') && str ? ft_strdel(&str) : 0;
	if (!str)
		return (0);
	ft_strcpy(header->prog_name, str);
	tools->name_filled = 1;
	str ? ft_strdel(&str) : 0;
	return (1);
}

static int	fill_com(t_header *header, char **input, t_tools *tools, int i)
{
	int		j;
	int		beg;
	char	*str;

	str = NULL;
	j = 9;
	while (input[i][j] && input[i][j] != '"')
		j++;
	j++;
	input[i][j] == '"' ? ft_strcpy(header->comment, "") : 0;
	if (input[i][j] == '"')
		return (tools->com_empty = 1);
	beg = j++;
	while (input[i][j] && input[i][j] != '"')
		j++;
	if ((j - beg) > COMMENT_LENGTH)
		return (0);
	str = ft_strsub2(input[i], beg, j - beg);
	ft_strchr(str, '\n') && str ? ft_strdel(&str) : 0;
	if (!str)
		return (0);
	ft_strcpy(header->comment, str);
	str ? ft_strdel(&str) : 0;
	tools->com_filled = 1;
	return (1);
}

int			header_fill(t_header *header, char **input, t_tools *t)
{
	int		i;

	header->magic = COREWAR_EXEC_MAGIC;
	header->magic = swap_uint32(header->magic);
	i = 0;
	while (input[i])
	{
		if (!ft_strncmp(input[i], NAME_CMD_STRING, 5)
			&& t->name_filled == 0)
		{
			if (!fill_name(header, input, t, i))
				return (0);
		}
		else if (!ft_strncmp(input[i], COMMENT_CMD_STRING, 8)
			&& t->com_filled == 0)
		{
			if (!fill_com(header, input, t, i))
				return (0);
		}
		i++;
	}
	header->prog_size = t->prog_size;
	header->prog_size = swap_uint32(header->prog_size);
	return (bad_dot_line(input) || (!t->name_filled && !t->name_empty)
		|| (!t->com_filled && !t->com_empty) ? 0 : 1);
}
