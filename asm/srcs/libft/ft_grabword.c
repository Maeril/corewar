/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grabword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 23:57:20 by myener            #+#    #+#             */
/*   Updated: 2020/05/01 21:09:45 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int (*pf)(int);

char	*ft_grabword(char *str, int start, int upper, int lower)
{
	int		i;
	char	*word;

	word = NULL;
	i = start;
	pf = upper && lower ? ft_isalpha : NULL;
	pf = upper ? ft_isalphaup : ft_isalphalow;
	// (void)upper;
	// (void)lower;
	// while (str[i] && ft_isalphalow(str[i]))
	while (str[i] && pf(str[i]))
			i++;
	word = ft_strsub(str, start, i - start + 1);
	return (word);
}
