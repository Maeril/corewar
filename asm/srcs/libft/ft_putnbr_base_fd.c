/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:41:32 by myener            #+#    #+#             */
/*   Updated: 2020/05/07 13:49:01 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(int fd, long long int nb, const char *base)
{
	int		bl;

	bl = ft_strlen(base);
	if (nb < 0)
	{
		ft_putchar_fd(fd, '-');
		nb = -nb;
	}
	if (nb >= bl)
		ft_putnbr_base_fd(fd, (nb / bl), base);
	ft_putchar_fd(fd, base[nb % bl]);
}
