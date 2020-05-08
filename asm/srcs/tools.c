/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 00:12:13 by myener            #+#    #+#             */
/*   Updated: 2020/05/08 22:21:05 by myener           ###   ########.fr       */
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

int		is_called_label(char *str, int write_size)
{
	if (write_size == 1)
		return (0);
	else if (write_size == 2 || write_size == 4)
		return (str[0] == ':' || (str[0] == '%' && str[1] == ':') ? 1 : 0);
	return (0);
}

int		is_legit_label(char *label, line_t *tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (tab[i].label && !ft_strcmp(label, tab[i].label))
			return (1);
		i++;
	}
	return (0);
}

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
		counter = 8 - ft_strlen(str);
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

void	binary_add1(char *str)
{
	int	i;

	i = ft_strlen(str) - 1; // put i on the last character
	if (str[i] == '1')
	{
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
}

void	*bin_to_hex(int fd, char *bin)
{
	int		sum;
	char	*part1;
	char	*part2;
	char	*hex;

	hex = ft_strnew(1);
	sum = 0;
	part1 = ft_strsub(bin, 0, 4);
	part2 = ft_strsub(bin, 4, 4);
	// ft_printf("part1 = %s, part2 = %s\n", part1, part2);
	sum += part1[0] == '1' ? 8 : 0;
	sum += part1[1] == '1' ? 4 : 0;
	sum += part1[2] == '1' ? 2 : 0;
	sum += part1[3] == '1' ? 1 : 0;
	// ft_printf("sum1 = %d\n", sum);
	ft_putnbr_base_fd(fd, sum, HEXL);
	// hex = (ft_strdup(ft_itoa_base(sum, HEXL)));
	sum = 0;
	sum += part2[0] == '1' ? 8 : 0;
	sum += part2[1] == '1' ? 4 : 0;
	sum += part2[2] == '1' ? 2 : 0;
	sum += part2[3] == '1' ? 1 : 0;
	// hex = ft_free_join(hex, ft_itoa_base(sum, HEXL));
	ft_putnbr_base_fd(fd, sum, HEXL);
	// ft_printf("sum2 = %d, hex = %s\n\n", sum, hex);
	// free(bin);
	return (hex);
}

void	decimal_to_hex_2scomplement(int fd, int value)
{
	size_t		i;
	char		*bin;

	bin = generate_binary(value);
	i = 0;
	while (bin[i])
	{
		bin[i] = (bin[i] == '1') ? '0' : '1';
		i++;
	}
	binary_add1(bin);
	ft_printf("decimal: %d binary: %s\n", value, bin);
	ft_printf("bin = %s\n", bin);
	bin_to_hex(fd, bin);
	// ft_printf("apres2: %s\n\n", bin);
}

int		has_label_size(char *word)
{
	if (!ft_strcmp(word, "zjmp") || !ft_strcmp(word, "ldi")
	|| !ft_strcmp(word, "sti") || !ft_strcmp(word, "fork")
	|| !ft_strcmp(word, "lldi") || !ft_strcmp(word, "lfork"))
		return (1);
	return (0);
}

int		has_coding_byte(char *word)
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
