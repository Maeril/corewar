/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 07:28:31 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/14 07:39:24 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		visualizer_handle_events(t_vm *vm)
{
	int		key;

	if (vm->options & VM_OP_C)
	{
		while (!vm->goto_cycle && ((key = getkey()) != ERR
			|| !vm->display.run))
		{
			visualizer_handle_keys(vm, key);
			display_refresh(vm);
		}
	}
}

void		visualizer_refresh_events(t_vm *vm)
{
	if (vm->cycle < vm->goto_cycle)
	{
		if (!(vm->cycle % 500))
			display_refresh(vm);
	}
	else if (vm->cycle && vm->cycle == vm->goto_cycle)
	{
		wclear(vm->display.winfo);
		display_borders(&vm->display);
		vm->display.run = PAUSE;
		vm->goto_cycle = 0;
		visualizer_handle_events(vm);
		display_refresh(vm);
	}
	else
	{
		napms(1000 / vm->display.speed);
		display_refresh(vm);
	}
}
