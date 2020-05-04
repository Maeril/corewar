/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:02:54 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/14 17:47:38 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		options_stack(int *options)
{
	if (*options & VM_OP_C)
		*options &= ~VM_OP_D | ~VM_OP_S;
	if (*options & VM_OP_S)
		*options &= ~VM_OP_D;
	if (*options & VM_OP_UP_V)
		*options |= VM_OP_V;
}

int	parse_options(int *options, char *arg)
{
	int index;

	if (*arg == '-')
		++arg;
	while (*arg)
	{
		if ((index = ft_indexof(*arg, VM_OPTIONS)) == -1)
			return (invalid_option_error(*arg));
		*options |= 1 << index;
		if (*options & VM_OP_H)
			return (put_usage());
		++arg;
	}
	options_stack(options);
	return (0);
}
