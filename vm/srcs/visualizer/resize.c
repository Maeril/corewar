/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:16:01 by hben-yah          #+#    #+#             */
/*   Updated: 2020/06/18 08:40:54 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		display_message(t_vm *vm, int y, int x)
{
	int ymax;
	int xmax;
	int	i;
	int	j;

	ymax = vm->display.leg.y + vm->display.leg.row;
	xmax = vm->display.info.x + vm->display.info.col
		+ (vm->options & VM_OP_V ? OUT_WIDTH_MIN : 0);
	attron(COLOR_PAIR(RCOLOR - ERR_COLOR) - 1);
	i = 0;
	while (i <= vm->display.head.row)
	{
		j = 0;
		while (j < x)
			mvprintw(i, j++, " ");
		++i;
	}
	mvprintw(1, 1, "FENETRE TROP PETITE", 0x1F624);
	if (x < xmax)
		mvprintw(3, 1, "%d colonnes nécessaires", xmax - x);
	if (y < ymax)
		mvprintw(4, 1, "%d lignes nécessaires", ymax - y);
	attroff(A_BLINK | COLOR_PAIR(RCOLOR - ERR_COLOR) - 1);
}

void			display_resize(t_vm *vm)
{
	int	y;
	int	x;
	int ymax;
	int xmax;

	ymax = vm->display.leg.y + vm->display.leg.row;
	xmax = vm->display.info.x + vm->display.info.col
		+ (vm->options & VM_OP_V ? OUT_WIDTH_MIN : 0);
	getmaxyx(stdscr, y, x);
	if (y < ymax || x < xmax)
	{
		vm->display.run = PAUSE;
		display_message(vm, y, x);
	}
	else
	{
		clear();
		reset_windows(&vm->display);
		init_windows(vm, &vm->display);
		display_colrow(&vm->display);
		display_header(vm);
		display_legend(vm);
		display_borders(&vm->display);
	}
}
