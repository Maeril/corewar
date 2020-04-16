/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:15:36 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/08 10:35:00 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		reset_windows(t_display *display)
{
	if (display->wfield)
		delwin(display->wfield);
	if (display->winfo)
		delwin(display->winfo);
	if (display->wleg)
		delwin(display->wleg);
	if (display->wout)
		delwin(display->wout);
}

void		reset_visualizer(t_vm *vm)
{
	if (vm->options & VM_OP_C)
	{
		reset_windows(&vm->display);
		endwin();
	}
}
