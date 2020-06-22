/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 01:03:42 by myener            #+#    #+#             */
/*   Updated: 2020/06/23 01:51:33 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		has_label_size(char *word)
{
	if (!ft_strcmp(word, "zjmp") || !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "fork")
	|| !ft_strcmp(word, "lldi") || !ft_strcmp(word, "lfork"))
		return (1);
	return (0);
}

int		has_cb(char *word)
{
	if (ft_strcmp(word, "live") && ft_strcmp(word, "zjmp")
	&& ft_strcmp(word, "fork") && ft_strcmp(word, "lfork"))
		return (1);
	return (0);
}

int		has_one_param(char *word)
{
	if (!ft_strcmp(word, "live") || !ft_strcmp(word, "zjmp")
	|| !ft_strcmp(word, "fork") || !ft_strcmp(word, "lfork")
	|| !ft_strcmp(word, "aff"))
		return (1);
	return (0);
}

int		has_two_params(char *word)
{
	if (!ft_strcmp(word, "ld") || !ft_strcmp(word, "st")
	|| !ft_strcmp(word, "lld"))
		return (1);
	return (0);
}

int		has_three_params(char *word)
{
	if (!ft_strcmp(word, "add") || !ft_strcmp(word, "sub")
	|| !ft_strcmp(word, "and") || !ft_strcmp(word, "or")
	|| !ft_strcmp(word, "xor") || !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "lldi"))
		return (1);
	return (0);
}
