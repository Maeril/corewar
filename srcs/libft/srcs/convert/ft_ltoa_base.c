/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:14:34 by hben-yah          #+#    #+#             */
/*   Updated: 2019/11/20 07:47:51 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa_base(long n, char *base)
{
	char			*s;
	size_t			len;
	size_t			base_len;
	unsigned long	nbr;

	base_len = ft_strlen(base);
	nbr = (n < 0 ? (unsigned long)-n : (unsigned long)n);
	len = ft_nbrlen(n, base_len);
	if (!(s = ft_stralloc(len)))
		return (NULL);
	s[--len] = base[nbr % base_len];
	while (nbr /= base_len)
		s[--len] = base[nbr % base_len];
	if (n < 0)
		*s = '-';
	return (s);
}
