/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_not_found_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 12:35:26 by hben-yah          #+#    #+#             */
/*   Updated: 2019/11/24 12:37:44 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int		file_not_found_error(void)
{
	ft_putendl_fd(VM_NAME": file not found",
		2);
	return (put_usage());
}
