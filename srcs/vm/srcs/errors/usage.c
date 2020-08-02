/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 08:50:53 by hben-yah          #+#    #+#             */
/*   Updated: 2020/07/28 11:00:41 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		put_usage(void)
{
	ft_putstr_fd("Usage:  ./corewar [-havVc] ", 2);
	ft_putstr_fd("[-ds nbr_cycles] [[-n number] champion1.cor] ...\n", 2);
	ft_putstr_fd("-h    helper\n", 2);
	ft_putstr_fd("-a    display aff command\n", 2);
	ft_putstr_fd("-v    verbose\n", 2);
	ft_putstr_fd("-V    verbose in french\n", 2);
	ft_putstr_fd("-c    visualizer ncurse\n", 2);
	ft_putstr_fd("-d    dump the battlefield at nbr_cycles\n", 2);
	ft_putstr_fd("-s    dump the battlefield each nbr_cycles and sleep\n", 2);
	ft_putstr_fd("-n    number of the champion\n", 2);
	return (1);
}
