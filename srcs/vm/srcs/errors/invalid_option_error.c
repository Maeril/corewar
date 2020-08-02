/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_option_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 08:33:22 by hben-yah          #+#    #+#             */
/*   Updated: 2019/11/24 09:35:34 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int		invalid_option_error(char arg)
{
	ft_putstr_fd(VM_NAME": invalid option -- ", 2);
	ft_putchar_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	return (put_usage());
}
