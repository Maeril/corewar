/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:02:48 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 14:51:51 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	champ_lst_rev(t_champ **alst)
{
	t_champ	*prev;
	t_champ	*cur;
	t_champ	*next;

	cur = *alst;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

int		check_vm(t_vm *vm)
{
	if (!vm->champ)
		return (no_champion_error());
	champ_lst_rev(&vm->champ);
	return (0);
}

int		handle_arguments(t_vm *vm, int ac, char **av)
{
	return (parse_arguments(vm, ac, av) || check_vm(vm));
}
