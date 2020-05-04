/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_file_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 12:35:42 by hben-yah          #+#    #+#             */
/*   Updated: 2019/11/24 12:37:51 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int		invalid_file_error(void)
{
	ft_putendl_fd(VM_NAME": invalid file",
		2);
	return (put_usage());
}
