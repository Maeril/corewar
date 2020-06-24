/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 01:08:34 by myener            #+#    #+#             */
/*   Updated: 2020/06/24 20:35:48 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

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

char	*string_cleaner(char *str)
{
	char	*out;
	char	*tmp;

	out = NULL;
	tmp = NULL;
	str = ft_strtrim(str);
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
