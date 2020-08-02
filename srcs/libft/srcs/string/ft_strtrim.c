/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:20:58 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 20:40:02 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	char	*res;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (ft_isspace_wnt(s[len - 1]))
		--len;
	while (ft_isspace_wnt(*s) && len--)
		++s;
	if ((int)len < 0)
		len = 0;
	if (!(res = ft_stralloc(len)))
		return (NULL);
	ft_strncpy(res, s, len);
	return (res);
}
