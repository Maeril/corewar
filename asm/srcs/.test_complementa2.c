/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .test_complementa2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 21:14:56 by myener            #+#    #+#             */
/*   Updated: 2020/05/08 21:25:48 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*generate_binary(int value)
{
	int		i;
	int		counter;
	char	*str;
	char	*tmp;

	i = 0;
	counter = 0;
	str = base_converter(ft_itoa(ft_abs(value)), DECI, BIN);
	// ft_printf("len = %d\n", ft_strlen(str));
	if (ft_strlen(str) < 9) // if the binary isn't "long enough" (we need 8 digits)
	{
		counter = 9 - ft_strlen(str);
		// ft_printf("counter = %d\n", counter);
		tmp = ft_strnew(counter);
		i = 0;
		while (i < counter)
		{
			tmp[i] = '0';
			i++;
		}
		// ft_printf("tmp = %s\n", tmp);
		tmp = ft_free_join(tmp, str);
		// free(str);
		return (tmp);
	}
	return (str);
}

char	*binary_add1(char *str)
{
	int	i;

	i = ft_strlen(str) - 1; // put i on the last character
	if (str[i] == '1')
	{
		ft_printf("last char has a value of 1\n");
		str[i] = '0';
		i--;
		while (i >= 0 && str[i] != '0')
		{
			str[i] = '0';
			i--;
		}
		if (i >= 0)
			str[i] = '1';
	}
	else if (str[i] == '0')
		str[i] = '1';
	return (str);
}

char	*decimal_to_bin_2scomplement(int value)
{
	size_t		i;
	char		*str;

	str = generate_binary(value);
	i = 0;
	ft_printf("avant: %s\n", str);
	while (str[i])
	{
		str[i] = (str[i] == '1') ? '0' : '1';
		i++;
	}
	ft_printf("apres1: %s\n\n", str);
	str = binary_add1(str);
	ft_printf("apres2: %s\n\n", str);
	return (str);
}

int		main(int ac, char **av) // TEST REUSSI :) tout fonctionne
{
	if (ac < 2)
		return (0);
	ft_printf("decimal = %s, binary = %s\n", av[1], decimal_to_bin_2scomplement(ft_atoi(av[1])));
	return (0);
}