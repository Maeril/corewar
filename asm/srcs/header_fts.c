/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:47:05 by myener            #+#    #+#             */
/*   Updated: 2020/05/08 16:48:42 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"


// void	name_comment_stock(header_t *header, char *line, tools_t *tools)
// {
// 	int		i;
// 	int		beg;

// 	i = 0;
// 	if (!ft_strncmp(line, NAME_CMD_STRING, 5) && tools->name_filled == 0)
// 	{
// 		i = 6;
// 		while (line[i] && line[i] != '"')
// 			i++;
// 		beg = i++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
// 		while (line[i] && line[i] != '"')
// 			i++;
// 		if (i - beg > PROG_NAME_LENGTH)
// 			return ; // OUTPUT ERROR AND EXIT
// 		header->prog_name = ft_strsub(line, beg, i - beg + 1);
// 		// ft_printf("prog_name = %s\n", header->prog_name) // for proofreading only
// 		tools->name_filled = 1;
// 	}
// 	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8) && tools->com_filled == 0)
// 	{
// 		i = 9;
// 		while (line[i] && line[i] != '"')
// 			i++;
// 		beg = i++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
// 		while (line[i] && line[i] != '"')
// 			i++;
// 		if ((i - beg) > COMMENT_LENGTH)
// 			return ; // OUTPUT ERROR AND EXIT
// 		header->comment = ft_strsub(line, beg, i - beg + 1);
// 		// ft_printf("comment = %s\n", header->comment) // for proofreading only
// 		tools->com_filled = 1;
// 	}
// 	//else, do nothing. gotta check whether encountering >1 name or comment = error.
// }
