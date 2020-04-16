/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 14:53:05 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 20:18:01 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_boxes(t_display *d)
{
	d->el_per_line = ft_sqrt(MEM_SIZE);
	d->field.row = d->el_per_line + 2;
	d->field.col = (d->el_per_line * 3) + 3;
	d->field.x = 3;
	d->field.y = d->head.y + d->head.row + 2;
	d->info.row = d->field.row;
	d->info.col = 60;
	d->info.x = d->field.x + d->field.col;
	d->info.y = d->field.y;
	d->leg.row = 9;
	d->leg.col = d->field.col + d->info.col;
	d->leg.x = d->field.x;
	d->leg.y = d->field.y + d->field.row;
	d->out.row = d->info.row + d->leg.row;
	d->out.col = OUT_WIDTH;
	d->out.x = d->info.x + d->info.col + 2;
	d->out.y = d->field.y;
}

void	init_windows(t_vm *vm, t_display *d)
{
	if (!(d->wfield = newwin(d->field.row, d->field.col, d->field.y, d->field.x)))
		exit_vm(vm, "init_windows ~> newwin error : d->wfield == NULL", 1);
	if (!(d->winfo = newwin(d->info.row, d->info.col, d->info.y, d->info.x)))
		exit_vm(vm, "init_windows ~> newwin error : d->winfo == NULL", 1);
	if (!(d->wleg = newwin(d->leg.row, d->leg.col, d->leg.y, d->leg.x)))
		exit_vm(vm, "init_windows ~> newwin error : d->wleg == NULL", 1);
	if (!(d->wout = newwin(d->out.row, d->out.col, d->out.y, d->out.x)))
		exit_vm(vm, "init_windows ~> newwin error : d->wout == NULL", 1);
    scrollok(d->wout,TRUE);
}

void	init_visualizer(t_vm *vm)
{
	if (vm && vm->options & VM_OP_C)
	{
		setlocale(LC_ALL, "");
		vm->display.run = vm->goto_cycle ? FW : PAUSE;
		vm->display.speed = DFLT_SPEED;
		initscr();
		curs_set(0);
		keypad(stdscr, TRUE);
		nodelay(stdscr, TRUE);
		use_default_colors();
		display_colrow(&vm->display);
		display_header(vm);
		init_boxes(&vm->display);
		init_windows(vm, &vm->display);
		display_borders(&vm->display);
		display_legend(vm);
		init_colors();
		display_resize(vm);
	}
}
