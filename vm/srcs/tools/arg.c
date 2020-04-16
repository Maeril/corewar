/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:29:17 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/15 09:58:23 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_arg_type	get_arg_type(unsigned char ocp)
{
	if (ocp == REG_CODE)
		return (T_REG);
	else if (ocp == DIR_CODE)
		return (T_DIR);
	else if (ocp == IND_CODE)
		return (T_IND);
	return (0);
}

void	set_args_types(t_arg *args, unsigned char ocp)
{
	args[0].type = get_arg_type((ocp >> 6) & 0x3);
	args[1].type = get_arg_type((ocp >> 4) & 0x3);
	args[2].type = get_arg_type((ocp >> 2) & 0x3);
	args[3].type = 0;
}
