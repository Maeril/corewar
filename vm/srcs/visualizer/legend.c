/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:15:46 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 19:00:33 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	display_keys_legend(t_vm *vm, int y, int *tabx)
{
	int	i;
	int	d;

	i = 0;
	d = 2;
	mvwprintw(vm->display.wleg, y, tabx[i], "Play / Pause");
	mvwprintw(vm->display.wleg, y, tabx[i += d], "Ralentir   -10");
	mvwprintw(vm->display.wleg, y, tabx[i += d], "Accélérer +10");
	mvwprintw(vm->display.wleg, y, tabx[i += d], "Ralentir   -1");
	mvwprintw(vm->display.wleg, y, tabx[i += d], "Accélérer  +1");
	mvwprintw(vm->display.wleg, y, tabx[i += d], "Aller au cycle ...");
	mvwprintw(vm->display.wleg, y, tabx[i += d], "Quitter");
	i = 0;
	wattron(vm->display.wleg, A_STANDOUT);
	mvwprintw(vm->display.wleg, ++y, tabx[i], "   ESPACE   ");
	mvwprintw(vm->display.wleg, y, tabx[i += d], "      %C       ", 8592);
	mvwprintw(vm->display.wleg, y, tabx[i += d], "      %C      ", 8594);
	mvwprintw(vm->display.wleg, y, tabx[i += d], "      %C      ", 8595);
	mvwprintw(vm->display.wleg, y, tabx[i += d], "      %C      ", 8593);
	mvwprintw(vm->display.wleg, y, tabx[i += d], "         @         ");
	mvwprintw(vm->display.wleg, y, tabx[i += d], "     END     ");
	wattroff(vm->display.wleg, A_STANDOUT);
}

static void	display_operation_legend(t_vm *vm, int y, int *tabx)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	while (g_op_tab[i].op_code)
	{
		wattron(vm->display.wleg, A_STANDOUT);
		mvwprintw(vm->display.wleg, y, tabx[x], " %02x ", g_op_tab[i].op_code);
		wattroff(vm->display.wleg, A_STANDOUT);
		mvwprintw(vm->display.wleg, y, tabx[x] + 5, "%s", g_op_tab[i].name);
		tabx[x + 1] = tabx[x] + 10 + ft_strlen(g_op_tab[i].name);
		++x;
		++i;
	}
}

void		display_legend(t_vm *vm)
{
	int	y;
	int	tabx[21];

	y = 2;
	tabx[0] = 3;
	tabx[20] = 0;
	display_operation_legend(vm, y, tabx);
	y += 3;
	display_keys_legend(vm, y, tabx);
}