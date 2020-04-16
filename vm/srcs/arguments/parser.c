/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:03:13 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/18 06:34:49 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	parse_cycle(t_vm *vm, int *ac, char ***av, char flag)
{
	--*ac;
	++*av;
	if (!*ac || !ft_isbase(10, **av))
	{
		if (flag != 'c')
			return (cycle_arg_error());
		else
		{
			++*ac;
			--*av;
		}
	}
	else
	{
		vm->option_nb = ft_atoi(**av);
		vm->goto_cycle = vm->option_nb;
	}
	vm->options |= 1 << ft_indexof(flag, VM_OPTIONS);
	return (0);
}

static int	parse_n(t_vm *vm, int *ac, char ***av)
{
	int	id;

	--*ac;
	++*av;
	if (!*ac || !ft_isbase(10, **av))
		return (n_arg_error());
	id = ft_atoi(**av);
	--*ac;
	++*av;
	if (!*ac)
		return (missing_champion_error());
	return (parse_champion(vm, id, **av));
}

int			parse_arguments(t_vm *vm, int ac, char **av)
{
	int ret;
	int	number;

	number = -1;
	while (ac)
	{
		if (**av == '-')
		{
			if (ft_strequ(*av + 1, "d") || ft_strequ(*av + 1, "s") || ft_strequ(*av + 1, "c"))
				ret = parse_cycle(vm, &ac, &av, *(*av + 1));
			else if (ft_strequ(*av + 1, "n"))
				ret = parse_n(vm, &ac, &av);
			else
				ret = parse_options(&vm->options, *av);
		}
		else
			ret = parse_champion(vm, number--, *av);
		if (vm->n_champs > MAX_PLAYERS)
			return (too_many_champions_error());
		if (ret)
			return (1);
		--ac;
		++av;
	}
	return (0);
}
