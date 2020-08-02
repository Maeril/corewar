/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:18:19 by myener            #+#    #+#             */
/*   Updated: 2020/08/02 20:20:51 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup2(const char *str, size_t n)
{
	size_t	i;
	char	*dest;

	if (!(dest = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	i = 0;
	while (i < n && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}
