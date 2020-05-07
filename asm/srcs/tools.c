/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 00:12:13 by myener            #+#    #+#             */
/*   Updated: 2020/05/06 17:56:57 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		empty_or_comment_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			break;
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		is_instruc(char *word)
{
	if (!ft_strcmp(word, "live") || !ft_strcmp(word, "ld")
	|| !ft_strcmp(word, "st") || !ft_strcmp(word, "add")
	|| !ft_strcmp(word, "sub") || !ft_strcmp(word, "and")
	|| !ft_strcmp(word, "or") || !ft_strcmp(word, "xor")
	|| !ft_strcmp(word, "zjmp")	|| !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "fork")
	|| !ft_strcmp(word, "lld") || !ft_strcmp(word, "lldi")
	|| !ft_strcmp(word, "lfork")	|| !ft_strcmp(word, "aff"))
		return (1);
	return (0);
}

int		has_label_size(char *word)
{
	if (!ft_strcmp(word, "zjmp") || !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "fork")
	|| !ft_strcmp(word, "lldi") || !ft_strcmp(word, "lfork"))
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
