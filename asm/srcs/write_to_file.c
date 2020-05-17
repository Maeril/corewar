/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:40:01 by myener            #+#    #+#             */
/*   Updated: 2020/05/18 01:09:14 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		get_opcode(char *instruc)
{
	if (!ft_strcmp(instruc, "live"))
		return (1);
	else if (!ft_strcmp(instruc, "ld"))
		return (2);
	else if (!ft_strcmp(instruc, "st"))
		return (3);
	else if (!ft_strcmp(instruc, "add"))
		return (4);
	else if (!ft_strcmp(instruc, "sub"))
		return (5);
	else if (!ft_strcmp(instruc, "and"))
		return (6);
	else if (!ft_strcmp(instruc, "or"))
		return (7);
	else if (!ft_strcmp(instruc, "xor"))
		return (8);
	else if (!ft_strcmp(instruc, "zjmp"))
		return (9);
	else if (!ft_strcmp(instruc, "ldi"))
		return (10);
	else if (!ft_strcmp(instruc, "sti"))
		return (11);
	else if (!ft_strcmp(instruc, "fork"))
		return (12);
	else if (!ft_strcmp(instruc, "lld"))
		return (13);
	else if (!ft_strcmp(instruc, "lldi"))
		return (14);
	else if (!ft_strcmp(instruc, "lfork"))
		return (15);
	else if (!ft_strcmp(instruc, "aff"))
		return (16);
	return (0);
}

int		get_coding_byte(line_t *tab, int i)
{
	int		j;
	int		counter;
	char	*byte;

	// 1: build coding byte binary from data in struc
	counter = 0;
	byte = ft_strnew(1);
	if (tab[i].param1 > 0)
	{
		if (tab[i].param1[0] == '%') // if yes then it's a direct
			byte = ft_free_join(byte, "10");
		else // else it's: a register if sz = 1, an indirect otherwise.
			byte = ft_free_join(byte, tab[i].param1_sz == 1 ? "01" : "11");
		counter += 2;
	}
	if (tab[i].param2 > 0)
	{
		if (tab[i].param2[0] == '%') // if yes then it's a direct
			byte = ft_free_join(byte, "10");
		else // else it's: a register if sz = 1, an indirect otherwise.
			byte = ft_free_join(byte, tab[i].param2_sz == 1 ? "01" : "11");
		counter += 2;
	}
	if (tab[i].param3 > 0)
	{
		if (tab[i].param3[0] == '%') // if yes then it's a direct
			byte = ft_free_join(byte, "10");
		else // else it's: a register if sz = 1, an indirect otherwise.
			byte = ft_free_join(byte, tab[i].param3_sz == 1 ? "01" : "11");
		counter += 2;
	}
	j = 0;
	while (j < (8 - counter))
	{
		byte = ft_free_join(byte, "0");
		j++;
	}
	return (ft_atoi(base_converter(byte, BIN, DECI))); // probably not right
}

void	write_called_label(int fd, int j, int len, line_t *tab, int write_size) // here we assume param's been confirmed legit, and there's only one per instruction
{
	int					i;
	int					value;

	i = 0;
	// find corresponding label in struct_tab
	while (i < len)
	{
		if (tab[i].label && tab[j].called_label
			&& !(ft_strcmp(tab[i].label, tab[j].called_label)))
			break;
		i++;
	}
	// calculate target relative address - current relative address

	value = tab[i].relative_cor_addr - tab[j].relative_cor_addr;
	value += value < 0 ? 1 : 0; // maybe too easy to be true
	if (write_size > 1)
	{
		value = swap_uint32(value);
		value = write_size == 2 ? (value << 16) | (value >> 16) : value;
	}
	write(fd, &value, write_size);
}

void	write_param(int fd, char *str, int write_size)
{
	int		dec;
	char	*tmp;

	tmp = NULL;
	if (write_size == 1) // if it's a register
	{
		tmp = ft_strsub(str, 1, ft_strlen(str) - 1); // start is at 1 to jump over the 'r'
		dec = ft_atoi(tmp);
		// free(tmp);
		// dec <= 16 && dec >= 0 ? write(fd, "0", 1): 0; // for leading zeros
		if (write_size > 1)
		{
			dec = swap_uint32(dec);
			dec = write_size == 2 ? (dec << 16) | (dec >> 16) : dec;
		}
		write(fd, &dec, write_size);
		// ft_putnbr_base_fd(fd, dec, HEXL);
	}
	else // else it's a direct or indirect, so write it accordingly w/o the prefixed special characters
	{
		tmp = str[0] == '%' ? ft_strsub(str, 1, ft_strlen(str) - 1) : NULL;
		dec = str[0] == '%' ? ft_atoi(tmp) : ft_atoi(str);
		// write_size == 2 ? write(fd, "00", 2) : write(fd, "000000", 6); // write the correct amount of leading zeros
		// dec <= 16 && dec >= 0 ? write(fd, "0", 1): 0; // for leading zeros
		if (write_size > 1)
		{
			dec = swap_uint32(dec);
			dec = write_size == 2 ? (dec << 16) | (dec >> 16) : dec;
		}
		write(fd, &dec, write_size);
		// ft_putnbr_base_fd(fd, dec, HEXL);
	}
}

int		write_to_cor(line_t *tab, header_t *header, int len, int fd)
{
	int i;
	int	opcode;
	int	coding_byte;

	// write_header();
	i = 0;
	coding_byte = 0;
	opcode = 0;
	write(fd, header, sizeof(header_t));
	while (i < len)
	{
		if (tab[i].instruc)
		{
			// ft_printf("instruc = %s & get opcode = %d\n", tab[i].instruc, get_opcode(tab[i].instruc));
			opcode = get_opcode(tab[i].instruc);
			// ft_printf("opcode = %d\n", opcode);
			write(fd, &opcode, 1);
			// ft_putchar_fd(' ', fd); // DEBUG
			if (has_coding_byte(tab[i].instruc))
			{
				coding_byte = get_coding_byte(tab, i);
				write(fd, &coding_byte, 1);
				// ft_putchar_fd(' ', fd); // DEBUG
			}
			if (tab[i].param1)
			{
				is_called_label(tab[i].param1, tab[i].param1_sz) ?
				write_called_label(fd, i, len, tab, tab[i].param1_sz) :
				write_param(fd, tab[i].param1, tab[i].param1_sz);
				// ft_putchar_fd(' ', fd); // DEBUG
			}
			if (tab[i].param2)
			{
				is_called_label(tab[i].param2, tab[i].param2_sz) ?
				write_called_label(fd, i, len, tab, tab[i].param2_sz) :
				write_param(fd, tab[i].param2, tab[i].param2_sz);
				// ft_putchar_fd(' ', fd); // DEBUG
			}
			if (tab[i].param3)
			{
				is_called_label(tab[i].param3, tab[i].param3_sz) ?
				write_called_label(fd, i, len, tab, tab[i].param2_sz) :
				write_param(fd, tab[i].param3, tab[i].param3_sz);
				// ft_putchar_fd(' ', fd); // DEBUG
			}
		}
		// if (tab[i].called_label)
		i++;
	}
	return (1);
}
