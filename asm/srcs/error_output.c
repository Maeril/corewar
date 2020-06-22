/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 01:05:51 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 01:49:29 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		error_output(void)
{
	ft_printf("ERROR\n");
	return (0);
}

int		usage_output(void)
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	return (0);
}

int		bad_dot_line(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i][0] == '.' && ft_strncmp(input[i], NAME_CMD_STRING, 5)
		&& ft_strncmp(input[i], COMMENT_CMD_STRING, 8))
		{
			ft_printf("Lexical error at [%d:1]\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}
