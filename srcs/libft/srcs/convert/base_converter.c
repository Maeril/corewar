/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:28:04 by myener            #+#    #+#             */
/*   Updated: 2020/06/24 20:39:09 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*base_converter(char *nb, char *base_in, char *base_out)
{
	char	*tmp;

	tmp = NULL;
	if ((!(nb && base_in && base_out)))
	{
		return (NULL);
	}
	tmp = ft_itoa_base(ft_atoi_base(nb, base_in), base_out);
	return (tmp);
}
