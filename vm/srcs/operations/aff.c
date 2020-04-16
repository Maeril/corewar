/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:52:45 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 16:38:31 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		check_args_types(t_arg *args)
{
	return (args[0].type == T_REG);
}

static void		put_aff(t_vm *vm, t_proc *p, t_arg arg)
{
	if (vm->options & VM_OP_UP_V)
	{
		put_op(vm, p);
		printer(vm, 0, "Le caractère %c a été ajouté !\n", (char)arg.val);
	//	else
	//	printer(vm, 0, "aff -> added character : |%c|\n", (char)arg.val);
	}
}

static void		buff_add_chr(t_vm *vm, t_proc *p, char c)
{
	size_t	new_size;

	if (p->champ->aff.len + 1 > p->champ->aff.max_len)
	{
		new_size = p->champ->aff.max_len;
		while (p->champ->aff.len + 1 >= new_size)
			new_size = new_size * 2 + 1;
		if (!(p->champ->aff.str = realloc(p->champ->aff.str, new_size)))
			exit_vm(vm, "malloc error : realloc aff buffer", 1);
		p->champ->aff.max_len = new_size;
	}
	ft_memset(p->champ->aff.str + p->champ->aff.len++, c, 1);
	p->champ->aff.str[p->champ->aff.len] = 0;
}

void			operate_aff(t_vm *vm, t_proc *p)
{
	t_arg		args[4];

	ft_bzero(&args, sizeof(args));
	set_args_types(args, vm->field[move_pc(p, 1)]);
	if (!check_args_types(args))
		return (move_pc_through_args(p, args, p->op));
	read_arg(vm, p, &args[0]);
	if (!check_regs(args))
		return ;
	read_val(vm, p, &args[0]);
	args[0].val %= 256;
	if (ft_isprint(args[0].val))
		buff_add_chr(vm, p, (char)args[0].val);
	put_aff(vm, p, args[0]);
}
