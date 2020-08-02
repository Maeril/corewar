/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 01:08:34 by myener            #+#    #+#             */
/*   Updated: 2020/08/02 21:06:58 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	*get_coding_byte_helper(char *byte, char c, int sz)
{
	char	*tmp;

	tmp = NULL;
	if (c == '%')
		tmp = ft_free_join(byte, "10");
	else
		tmp = ft_free_join(byte, sz == 1 ? "01" : "11");
	return (tmp);
}

int		easyfree(char *st)
{
	st ? free(st) : 0;
	return (0);
}

char	*quickclean(char *st, char *tmp)
{
	st ? free(st) : 0;
	st = string_cleaner(tmp);
	tmp ? free(tmp) : 0;
	return (st);
}

int		lines_to_deduce(char **input)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (i < (int)ft_tablen((void **)input))
	{
		if (input[i][0] == '.' || input[i][0] == '#')
			nb++;
		i++;
	}
	return (nb);
}

char	*string_cleaner(char *in)
{
	char	*out;
	char	*tmp;
	char	*str;

	out = NULL;
	tmp = NULL;
	str = NULL;
	str = ft_strtrim(in);
	in ? free(in) : 0;
	if (str[0] == ',')
		out = ft_strsub(str, 1, ft_strlen(str) - 1);
	if (str[ft_strlen(str) - 1] == ',')
	{
		if (out)
			tmp = ft_strsub(str, 0, ft_strlen(out) - 1);
		else
			out = ft_strsub(str, 0, ft_strlen(str) - 1);
	}
	if (tmp || (!tmp && out))
	{
		str ? free(str) : 0;
		return (tmp ? tmp : out);
	}
	return (str);
}
