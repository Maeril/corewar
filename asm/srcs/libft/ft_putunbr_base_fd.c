/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:41:32 by myener            #+#    #+#             */
/*   Updated: 2020/05/08 17:05:48 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_base_fd(int fd, unsigned long long int nb, const char *base)
{
	unsigned int	bl;

	bl = ft_strlen(base);
	if (nb >= bl)
		ft_putunbr_base_fd(fd, (nb / bl), base);
	ft_putchar_fd(base[(nb % bl)], fd);
}
