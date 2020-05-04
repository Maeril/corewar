/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 19:43:25 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 19:43:36 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			display_end_loop(t_vm *vm)
{
	int	key;

	if (vm->options & VM_OP_C)
	{
		vm->display.run = STOP;
		display_refresh(vm);
		while ((key = getkey()) != KEY_END)
		{
			if (key == KEY_RESIZE)
			{
				display_resize(vm);
				vm->display.run = STOP;
			}
			display_refresh(vm);
		}
	}
}
