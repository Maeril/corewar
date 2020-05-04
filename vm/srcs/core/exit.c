/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:57:12 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/08 10:16:27 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exit_vm(t_vm *vm, char *details, int perr)
{
	if (vm->options & VM_OP_C)
		reset_visualizer(vm);
	if (details)
		ft_putendl2_fd("Error\n", details, 2);
	if (vm->err)
		ft_putendl_fd(vm->err, 2);
	if (perr)
		perror(NULL);
	del_vm(vm);
	exit(errno);
}
