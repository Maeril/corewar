/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .debug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 21:14:56 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 00:53:36 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/*trucs probablements inutiles datant de quand je pensais qu'il fallait écrire
tout en hexa version texte ptdr quelle conne*/

void	print_struct_tab(line_t *struct_tab, int len) // DEBUG ONLY
{
	int	i;

	i = 0;
	// len = 5; // TEST
	while (i < len)
	{
		struct_tab[i].instruc || struct_tab[i].label ? ft_printf("\033[1;36mLINE %d:\033[0m\n", i) : 0;
		struct_tab[i].label ? ft_printf("\033[1;31mlabel =\033[0m \"%s\"\n", struct_tab[i].label) : 0;
		struct_tab[i].instruc ? ft_printf("instruc = \"%s\"\n", struct_tab[i].instruc) : 0;
		ft_printf("\033[1;35mparam1 =\033[0m \"%s\"\n", struct_tab[i].param1);
		// struct_tab[i].param1 ? ft_printf("\033[1;35mparam1 =\033[0m \"%s\"\n", struct_tab[i].param1) : 0;
		struct_tab[i].param2 ? ft_printf("\033[1;35mparam2 =\033[0m \"%s\"\n", struct_tab[i].param2) : 0;
		struct_tab[i].param3 ? ft_printf("\033[1;35mparam3 =\033[0m \"%s\"\n", struct_tab[i].param3) : 0;
		struct_tab[i].param1 ? ft_printf("nb_params = [%d]\n", struct_tab[i].nb_param) : 0;
		struct_tab[i].param1 ? ft_printf("\033[1;32mparam1_sz =\033[0m [%d]\n", struct_tab[i].param1_sz) : 0;
		struct_tab[i].param2 ? ft_printf("\033[1;32mparam2_sz =\033[0m [%d]\n", struct_tab[i].param2_sz) : 0;
		struct_tab[i].param3 ?ft_printf("\033[1;32mparam3_sz =\033[0m [%d]\n", struct_tab[i].param3_sz) : 0;
		struct_tab[i].instruc ?ft_printf("\033[1;34mline_cor_length =\033[0m [%d]\n", struct_tab[i].line_cor_ln) : 0;
		struct_tab[i].called_label ? ft_printf("\033[1;31mcalled_label =\033[0m \"%s\"\n", struct_tab[i].called_label) : 0;
		ft_printf("\033[1;33mrelative cor address =\033[0m [%d]\n", struct_tab[i].relative_cor_addr);
		ft_putchar('\n');
		i++;
	}
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

void	header_printer_debug(header_t *header) // DEBUG ONLY
{
	ft_printf("comment = %s\n", header->comment);
	ft_printf("magic = %x\n", header->magic);
	ft_printf("prog name = %s\n", header->prog_name);
	ft_printf("prog size = %x\n", header->prog_size);
}


void	check_cor_addr(line_t *tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		ft_printf("label = %s, instruc = %s, cor addr = %d\n", tab[i].label, tab[i].instruc, tab[i].relative_cor_addr);
		i++;
	}
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
	sum > 1 ? ft_putnbr_base_fd(fd, sum, HEXL) : 0; // temporary solution as im not sure if this is the way to go
	// hex = (ft_strdup(ft_itoa_base(sum, HEXL)));
	sum = 0;
	sum += part2[0] == '1' ? 8 : 0;
	sum += part2[1] == '1' ? 4 : 0;
	sum += part2[2] == '1' ? 2 : 0;
	sum += part2[3] == '1' ? 1 : 0;
	// hex = ft_free_join(hex, ft_itoa_base(sum, HEXL));
	// ft_printf("sum = %d\n", sum);
	sum > 1 ? ft_putnbr_base_fd(fd, sum, HEXL) : 0; // temporary solution as im not sure if this is the way to go
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
	// ft_printf("decimal: %d binary: %s\n", value, bin);
	// ft_printf("bin = %s\n", bin);
	bin_to_hex(fd, bin);
	// ft_printf("apres2: %s\n\n", bin);
}

void	check_cor_addr(line_t *tab, int len) // DEBUG
{
	int i;

	i = 0;
	while (i < len)
	{
		if (tab[i].instruc)
			ft_print("instruc = %s, cor addr = %d", tab[i].instruc, tab[i].relative_cor_addr);
	}
}
