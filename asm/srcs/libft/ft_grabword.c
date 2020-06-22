/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grabword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 23:57:20 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 01:40:08 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int (*g_pf)(int);

char	*ft_grabword(char *str, int start, int upper, int lower)
{
	int		i;
	char	*word;

	word = NULL;
	i = start;
	g_pf = upper && lower ? ft_isalpha : NULL;
	g_pf = upper ? ft_isalphaup : ft_isalphalow;
	while (str[i] && g_pf(str[i]))
		i++;
	word = ft_strsub(str, start, i - start + 1);
	return (word);
}
