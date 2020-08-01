/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:29:30 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/01 12:19:33 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		printer(t_vm *vm, int force, const char *str, ...)
{
	va_list		ap;
	int			ret;

	ret = 0;
	if (!(vm->options & (VM_OP_V | VM_OP_C)) && !force)
		return (ret);
	va_start(ap, str);
	if (vm->options & VM_OP_C && vm->options & VM_OP_V
		&& vm->cycle > vm->goto_cycle - 100)
	{
		ret = vwprintw(vm->display.wout, str, ap);
		wrefresh(vm->display.wout);
	}
	else if (vm->options & VM_OP_V && !(vm->options & VM_OP_C))
		ret = ft_vprintf(str, ap);
	else if (force && !(vm->options & VM_OP_C))
		ret = ft_vprintf(str, ap);
	va_end(ap);
	return (ret);
}

void	print_coords(t_vm *vm, int force, int addr)
{
	int max;

	if (vm->options & VM_OP_C)
	{
		max = ft_max(vm->display.el_per_line, 1);
		printer(vm, force, "#(%02d,%02d)", addr / max, addr % max);
	}
	else
		printer(vm, force, "#(%d)", addr);
}
