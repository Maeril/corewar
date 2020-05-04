/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakdown.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:02:42 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 20:07:45 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		get_total_lives(t_vm *vm, int last)
{
	t_champ		*c;
	int			total;

	total = 0;
	c = vm->champ;
	while (c)
	{
		total += last ? c->last_lives : c->cur_lives;
		c = c->next;
	}
	return (total);
}

static void		adjust_color(t_vm *vm, int id, int *color, int last)
{
	t_champ		*c;
	int			lives;

	lives = 0;
	c = vm->champ;
	while (c)
	{
		lives = last ? c->last_lives : c->cur_lives;
		if (lives > 0)
			*color = ft_abs(c->id);
		if (c->id == id)
			break ;
		c = c->next;
	}
}

static void		display_default_breakdown(t_vm *vm, int *y, int x, int visible)
{
	int			n;

	n = vm->display.info.col - 6;
	visible = !visible ? A_NORMAL : A_STANDOUT;
	wattron(vm->display.winfo, COLOR_PAIR(20) | A_REVERSE);
	mvwprintw(vm->display.winfo, *y, x++, " ");
	wattroff(vm->display.winfo, COLOR_PAIR(20) | A_REVERSE);
	wattron(vm->display.winfo, COLOR_BLACK | visible);
	mvwprintw(vm->display.winfo, *y, x, "%*s", n, "");
	wattroff(vm->display.winfo, COLOR_BLACK | visible);
	x += n;
	wattron(vm->display.winfo, COLOR_PAIR(20) | A_REVERSE);
	mvwprintw(vm->display.winfo, *y, x, " ");
	wattroff(vm->display.winfo, COLOR_PAIR(20) | A_REVERSE);
}

void			display_current_live_breakdown(t_vm *vm, int *y, int x)
{
	t_champ		*c;
	int			total;
	int			color;
	int			n;

	total = get_total_lives(vm, 0);
	mvwprintw(vm->display.winfo, (*y)++, x, "Répartition des Lives pour la période actuelle :");
	display_default_breakdown(vm, y, x, !total);
	c = vm->champ;
	if (total > 0)
		while (c)
		{
			color = ft_abs(c->id);
			n = (c->cur_lives * (vm->display.info.col - 6) / total);
			n += (!c->next ? vm->display.info.col - 4 - x - n : 0);
			adjust_color(vm, c->id, &color, 0);
			wattron(vm->display.winfo, COLOR_PAIR(RCOLOR - color - 1));
			n = ft_min(n, vm->display.info.col - 4 - x);
			mvwprintw(vm->display.winfo, *y, x + 1, "%*s", n, "");
			x += n;
			wattroff(vm->display.winfo, COLOR_PAIR(RCOLOR - color - 1));
			c = c->next;
		}
	(*y) += 2;
}

void			display_last_live_breakdown(t_vm *vm, int *y, int x)
{
	t_champ		*c;
	int			total;
	int			color;
	int			n;

	total = get_total_lives(vm, 1);
	mvwprintw(vm->display.winfo, (*y)++, x, "Répartition des Lives pour la période précédente :");
	display_default_breakdown(vm, y, x, !total);
	c = vm->champ;
	if (total > 0)
		while (c)
		{
			color = 0;
			n = (c->last_lives * (vm->display.info.col - 6) / total);
			n += (!c->next ? vm->display.info.col - 4 - x - n : 0);
			adjust_color(vm, c->id, &color, 1);
			wattron(vm->display.winfo, COLOR_PAIR(RCOLOR - color - 1));
			n = ft_min(n, vm->display.info.col - 4 - x);
			mvwprintw(vm->display.winfo, *y, x + 1, "%*s", n, "");
			x += n;
			wattroff(vm->display.winfo, COLOR_PAIR(RCOLOR - color - 1));
			c = c->next;
		}
	*y += 2;
}
