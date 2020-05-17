/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen_ignore_empty_lines.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 21:10:56 by myener            #+#    #+#             */
/*   Updated: 2020/05/17 21:22:04 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tablen_ignore_empty_lines(char **tab)
{
	int i;
	int	nb_empty_lines;

	i = 0;
	nb_empty_lines = 0;
	while (tab[i])
	{
		if (tab[i][0] == '\n' && !tab[i][1])
			nb_empty_lines += 1;
		i++;
	}
	return (i - nb_empty_lines);
}
