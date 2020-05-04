/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:44:06 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/18 06:41:10 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*g_base = "0123456789abcdef";

int			main(int ac, char **av)
{
	t_vm	vm;
	int		ret;

	if (ac < 2)
		return (put_usage());
	init_vm(&vm);
	vm.ac = --ac;
	vm.av = ++av;
	if (!(ret = handle_arguments(&vm, ac, av)))
	{
		if (!(ret = read_champions(&vm)))
		{
			if (!vm.goto_cycle)
				init_visualizer(&vm);
			init_procs(&vm);
			run_vm(&vm);
			reset_visualizer(&vm);
		}
	}
	del_vm(&vm);
	exit_vm(&vm, NULL, 0);
}