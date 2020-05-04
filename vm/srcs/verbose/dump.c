/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:10:29 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 08:13:08 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// a refaire

static char		*fill_hex(char *addr, int nb)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		addr[3 - i] = g_base[nb % 16];
		nb /= 16;
		++i;
	}
	addr[4] = 0;
	return (addr);
}

static char		*get_term_color(int color)
{
	if (color == 1)
		return (P1_FCOLOR);
	if (color == 2)
		return (P2_FCOLOR);
	if (color == 3)
		return (P3_FCOLOR);
	if (color == 4)
		return (P4_FCOLOR);
	if (color == RCOLOR - 1)
		return (P1_BCOLOR);
	if (color == RCOLOR - 2)
		return (P2_BCOLOR);
	if (color == RCOLOR - 3)
		return (P3_BCOLOR);
	if (color == RCOLOR - 4)
		return (P4_BCOLOR);
	return ("\033[0m");
}

static void		footer_players(t_vm *vm)
{
	t_champ	*c;
	int			i;
	const char	*colors[] = { P1_BCOLOR, P2_BCOLOR, P3_BCOLOR,
		P4_BCOLOR, 0 };

	i = 1;
	if ((c = vm->champ))
		printer(vm, 1, "%8s", "");
	while (c)
	{
		printer(vm, 1, "%s %s ", colors[i - 1], "\033[0m");
		printer(vm, 1, "Player %d, \"%.33s\"", i, c->header.prog_name);
		if (c->next)
			printer(vm, 1, "\t");
		++i;
		c = c->next;
	}
	printer(vm, 1, "\n");
}

static void			dump(t_vm *vm)
{
	int		pc;
	int		width;
	char	addr[5];

	pc = 0;
	width = 32;
	printer(vm, 1, "0x%s: ", fill_hex(addr, pc));
	while (pc < MEM_SIZE)
	{
		pc %= MEM_SIZE;
		printer(vm, 1, "%s", get_term_color(vm->cells[pc].color));
		printer(vm, 1, "%02x%s ", vm->field[pc], "\033[0m");
		if (!((pc + 1) % width))
			printer(vm, 1, "\n");
		if (!((pc + 1) % width) && pc + 1 < MEM_SIZE)
			printer(vm, 1, "0x%s: ", fill_hex(addr, pc));
		pc++;
	}
	if (vm->options & (VM_OP_V | VM_OP_S))
		footer_players(vm);
}

void	dump_memory(t_vm *vm)
{
	if (vm->options & VM_OP_S
		&& (!(vm->cycle % vm->option_nb) || vm->cycle_to_die <= 0))
	{
		ft_printf("        Cycle %d\n", vm->cycle);
		dump(vm);
		getchar();
	}
	else if (vm->cycle == vm->option_nb || vm->cycle_to_die <= 0)
	{
		ft_printf("        Cycle %d\n", vm->cycle);
		if (vm->options & VM_OP_D)
			dump(vm);
		exit_vm(vm, NULL, 0);
	}
}
