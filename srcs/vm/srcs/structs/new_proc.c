/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 07:47:45 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/12 07:56:36 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_proc			*new_proc(t_vm *vm)
{
	t_proc		*new;

	if (!(new = (t_proc*)ft_memalloc(sizeof(t_proc))))
		exit_vm(vm, "malloc error : new proc", 1);
	return (new);
}
