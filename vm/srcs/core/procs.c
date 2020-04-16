/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 07:44:25 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 15:52:13 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	kill_proc(t_vm *vm, t_proc *p)
{
	t_proc		*cur;
	t_proc		*prev;

	cur = vm->proc;
	prev = NULL;
	while (cur)
	{
		if (cur->id == p->id)
		{
			if (prev)
				prev->next = cur->next;
			else
				vm->proc = cur->next;
			--cur->champ->n_procs;
			display_kill_pc(vm, cur);
			put_kill_pc(vm, cur);
			ft_memdel((void**)&cur);
			--vm->n_procs;
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void		check_procs(t_vm *vm)
{
	t_proc	*cur;
	t_proc	*next;

	cur = vm->proc;
	while (cur)
	{
		next = cur->next;
		if (!cur->lives)
			kill_proc(vm, cur);
		else
			cur->lives = 0;
		cur = next;
	}
}


void			exec_operation(t_vm *vm, t_proc *p)
{
	g_op_func_tab[p->op->op_code](vm, p);
	if (p->op->op_code != 9 || !p->carry)
	{
		++p->pc;
		put_move(vm, p);
	}
	p->op = NULL;
}

void			set_next_operation(t_vm *vm, t_proc *p)
{
	int op_code;

	p->prev_pc = p->pc;
	op_code = (int)vm->field[p->pc];
	if (op_code < 1 || op_code > 16)
	{
		p->prev_pc = p->pc++;
		p->sleep = 0;
	}
	else
	{
		p->op = &g_op_tab[op_code];
		p->sleep = p->op->nb_cycles - 2;
	}
}

void		exec_procs(t_vm *vm)
{
	t_proc	*p;

	p = vm->proc;
	while (p)
	{
		if (p->sleep < 1)
		{
			if (p->op)
				exec_operation(vm, p);
			else
				set_next_operation(vm, p);
			display_move_pc(vm, p);
		}
		else
			--p->sleep;
		p->pc %= MEM_SIZE;
		p = p->next;
	}
}
