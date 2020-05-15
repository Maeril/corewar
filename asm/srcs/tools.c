/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 00:12:13 by myener            #+#    #+#             */
/*   Updated: 2020/05/15 22:50:54 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		empty_or_comment_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			break;
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		is_instruc(char *word)
{
	if (!ft_strcmp(word, "live") || !ft_strcmp(word, "ld")
	|| !ft_strcmp(word, "st") || !ft_strcmp(word, "add")
	|| !ft_strcmp(word, "sub") || !ft_strcmp(word, "and")
	|| !ft_strcmp(word, "or") || !ft_strcmp(word, "xor")
	|| !ft_strcmp(word, "zjmp")	|| !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "fork")
	|| !ft_strcmp(word, "lld") || !ft_strcmp(word, "lldi")
	|| !ft_strcmp(word, "lfork")	|| !ft_strcmp(word, "aff"))
		return (1);
	return (0);
}

int		is_called_label(char *str, int write_size)
{
	if (write_size == 1)
		return (0);
	else if (write_size == 2 || write_size == 4)
		return (str[0] == ':' || (str[0] == '%' && str[1] == ':') ? 1 : 0);
	return (0);
}

int		is_legit_label(char *label, line_t *tab, int len)
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

char			*string_cleaner(char *str)
{
	char	*out;
	char	*tmp;

	out = NULL;
	tmp = NULL;
	str = ft_strtrim(str); // start by removing all whitespaces around the string
	if (str[0] == ',') // remove possible preceeding comma
	{
		out = ft_strsub(str, 1, ft_strlen(str) - 1);
	}
	if (str[ft_strlen(str) - 1] == ',') // remove possible succeeding comma
	{
		if (out)
			tmp = ft_strsub(str, 0, ft_strlen(out) - 1);
		else
			out = ft_strsub(str, 0, ft_strlen(str) - 1);
	}
	if (tmp)
	{
		str ? free(str) : 0;
		out ? free(out) : 0;
		return (tmp);
	}
	else if(!tmp && out)
	{
		str? free(str) : 0;
		return (out);
	}
	return (str);
}

unsigned int     swap_uint32(unsigned int nb) // for little to big endian conversion
{
    int	swap;

    swap = ((nb >> 24) & 0xFF) | ((nb >> 8) & 0xFF00)\
        | ((nb << 8) & 0xFF0000) | ((nb << 24) & 0xFF000000);
    return (swap);
}

int		has_label_size(char *word)
{
	if (!ft_strcmp(word, "zjmp") || !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "fork")
	|| !ft_strcmp(word, "lldi") || !ft_strcmp(word, "lfork"))
		return (1);
	return (0);
}

int		has_coding_byte(char *word)
{
	if (ft_strcmp(word, "live") && ft_strcmp(word, "zjmp")
	&& ft_strcmp(word, "fork") && ft_strcmp(word, "lfork"))
		return (1);
	return (0);
}

int		has_one_param(char *word)
{
	if (!ft_strcmp(word, "live") || !ft_strcmp(word, "zjmp")
	|| !ft_strcmp(word, "fork") || !ft_strcmp(word, "lfork")
	|| !ft_strcmp(word, "aff"))
		return (1);
	return (0);
}

int		has_two_params(char *word)
{
	if (!ft_strcmp(word, "ld") || !ft_strcmp(word, "st")
	|| !ft_strcmp(word, "lld"))
		return (1);
	return (0);
}

int		has_three_params(char *word)
{
	if (!ft_strcmp(word, "add") || !ft_strcmp(word, "sub")
	|| !ft_strcmp(word, "and") || !ft_strcmp(word, "or")
	|| !ft_strcmp(word, "xor") || !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "lldi"))
		return (1);
	return (0);
}
