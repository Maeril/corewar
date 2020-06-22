/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 00:12:13 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 01:47:17 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int				empty_or_comment_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			break ;
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				is_instruc(char *word)
{
	if (!ft_strcmp(word, "live") || !ft_strcmp(word, "ld")
	|| !ft_strcmp(word, "st") || !ft_strcmp(word, "add")
	|| !ft_strcmp(word, "sub") || !ft_strcmp(word, "and")
	|| !ft_strcmp(word, "or") || !ft_strcmp(word, "xor")
	|| !ft_strcmp(word, "zjmp") || !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "fork")
	|| !ft_strcmp(word, "lld") || !ft_strcmp(word, "lldi")
	|| !ft_strcmp(word, "lfork") || !ft_strcmp(word, "aff"))
		return (1);
	return (0);
}

int				is_called_label(char *str, int write_size)
{
	if (write_size == 1)
		return (0);
	else if (write_size == 2 || write_size == 4)
		return (str[0] == ':' || (str[0] == '%' && str[1] == ':') ? 1 : 0);
	return (0);
}

int				is_legit_label(char *label, t_line *tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (tab[i].label && !ft_strcmp(label, tab[i].label))
			return (1);
		i++;
	}
	return (0);
}

unsigned int	swap_uint32(unsigned int nb)
{
	int	swap;

	swap = ((nb >> 24) & 0xFF) | ((nb >> 8) & 0xFF00)\
		| ((nb << 8) & 0xFF0000) | ((nb << 24) & 0xFF000000);
	return (swap);
}
