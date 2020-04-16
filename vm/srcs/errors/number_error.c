/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 12:40:00 by hben-yah          #+#    #+#             */
/*   Updated: 2019/11/24 12:40:13 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int		already_attributed_number_error(void)
{
	ft_putendl_fd(VM_NAME": already attributed champion number",
		2);
	return (put_usage());
}

int		n_arg_error(void)
{
	ft_putendl_fd(VM_NAME": champion number has to be a positive number",
		2);
	return (put_usage());
}
