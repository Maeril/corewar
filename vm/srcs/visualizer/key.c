/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:00:57 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/14 17:01:32 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				getkey(void)
{
	int		key;

	noecho();
	key = getch();
	echo();
	return (key);
}

static void		handle_space(t_vm *vm)
{
	if (vm->display.run == PAUSE)
		vm->display.run = RUN;
	else if (vm->display.run == RUN)
		vm->display.run = PAUSE;
	else if (vm->display.run == FW)
	{
		vm->goto_cycle = 0;
		vm->display.run = PAUSE;
	}
	//display_refresh(vm);
}

static void		handle_at(t_vm *vm)
{
	int		c;

	mvwprintw(vm->display.winfo, 8, 2, "%38s", "");
	wattron(vm->display.winfo, A_BOLD);
	curs_set(2);
	mvwprintw(vm->display.winfo, 8, 2, "Go to (5-digits)%10s", "");
	c = 0;
	wscanw(vm->display.winfo, "%5d", &c);
	curs_set(0);
	if (c <= vm->cycle)
	{
		wattron(vm->display.winfo, COLOR_PAIR(ERR_COLOR));
		mvwprintw(vm->display.winfo, 8, 2, "ERROR : ");
		wprintw(vm->display.winfo, "Must be an number bigger than %d", vm->cycle);
		wattroff(vm->display.winfo, COLOR_PAIR(ERR_COLOR));
		c = 0;
	}
	else
	{
		mvwprintw(vm->display.winfo, 8, 2, "Going to %d%22s", c, "");
		vm->display.run = FW;
	}
	wattroff(vm->display.winfo, A_BOLD);
	//display_refresh(vm);
	vm->goto_cycle = c;
}

void			visualizer_handle_keys(t_vm *vm, int key)
{
	if (key == KEY_RESIZE)
		display_resize(vm);
	else if (key == ' ')
		handle_space(vm);
	else if (key == '@')
		handle_at(vm);
	else if (key == KEY_UP && vm->display.speed < 1000)
		vm->display.speed += 1;
	else if (key == KEY_RIGHT)
		vm->display.speed += ft_min(10, 1000 - vm->display.speed);
	else if (key == KEY_DOWN && vm->display.speed > 1)
		vm->display.speed -= 1;
	else if (key == KEY_LEFT)
		vm->display.speed -= ft_min(10, vm->display.speed - 1);
	else if (key == KEY_END)
		exit_vm(vm, NULL, 0);
}
