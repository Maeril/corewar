/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 10:58:26 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 14:13:19 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_refresh(t_vm *vm)
{
	if (vm->options & VM_OP_C)
	{
		display_field(vm);
		display_info(vm);
		wrefresh(vm->display.wfield);
		wrefresh(vm->display.winfo);
		wrefresh(vm->display.wleg);
	}
}
