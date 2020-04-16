/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 08:33:22 by hben-yah          #+#    #+#             */
/*   Updated: 2019/11/24 12:39:53 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int		no_champion_error(void)
{
	ft_putendl_fd(VM_NAME": no champion",
		2);
	return (1);
}

int		too_many_champions_error(void)
{
	ft_putendl_fd(VM_NAME": too many champions",
		2);
	return (1);
}

int		missing_champion_error(void)
{
	ft_putendl_fd(VM_NAME": the champion file argument is missing",
		2);
	return (put_usage());
}

int		champion_size_too_big(void)
{
	ft_putendl_fd(VM_NAME": champion size too big",
		2);
	return (put_usage());
}