/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:40:01 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 02:54:08 by myener           ###   ########.fr       */
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

int		get_coding_byte(t_line *tab, int i)
{
	int		j;
	int		counter;
	char	*byte;

	counter = 0;
	byte = ft_strnew(1);
	if (tab[i].param1 > 0)
	{
		if (tab[i].param1[0] == '%')
			byte = ft_free_join(byte, "10");
		else
			byte = ft_free_join(byte, tab[i].param1_sz == 1 ? "01" : "11");
		counter += 2;
	}
	if (tab[i].param2 > 0)
	{
		if (tab[i].param2[0] == '%')
			byte = ft_free_join(byte, "10");
		else
			byte = ft_free_join(byte, tab[i].param2_sz == 1 ? "01" : "11");
		counter += 2;
	}
	if (tab[i].param3 > 0)
	{
		if (tab[i].param3[0] == '%')
			byte = ft_free_join(byte, "10");
		else
			byte = ft_free_join(byte, tab[i].param3_sz == 1 ? "01" : "11");
		counter += 2;
	}
	j = 0;
	while (j < (8 - counter))
	{
		byte = ft_free_join(byte, "0");
		j++;
	}
	return (ft_atoi(base_converter(byte, BIN, DECI)));
}

void	write_called_label(t_tools *tools, int i, t_line *tab, int write_size)
{
	int					j;
	int					value;

	j = 0;
	while (j < tools->tablen)
	{
		if (tab[j].label && !(ft_strcmp(tab[j].label, tab[i].called_label)))
			break ;
		j++;
	}
	value = tab[j].relative_cor_addr - tab[i].relative_cor_addr;
	if (write_size > 1)
	{
		value = swap_uint32(value);
		value = write_size == 2 ? (value << 16) | (value >> 16) : value;
	}
	write(tools->fd, &value, write_size);
}

void	write_param(int fd, char *str, int write_size)
{
	int		dec;
	char	*tmp;

	tmp = NULL;
	if (write_size == 1)
	{
		tmp = ft_strsub(str, 1, ft_strlen(str) - 1);
		dec = ft_atoi(tmp);
		tmp ? free(tmp) : 0;
		if (write_size > 1)
		{
			dec = swap_uint32(dec);
			dec = write_size == 2 ? (dec << 16) | (dec >> 16) : dec;
		}
		write(fd, &dec, write_size);
	}
	else
	{
		tmp = str[0] == '%' ? ft_strsub(str, 1, ft_strlen(str) - 1) : NULL;
		dec = str[0] == '%' ? ft_atoi(tmp) : ft_atoi(str);
		if (write_size > 1)
		{
			dec = swap_uint32(dec);
			dec = write_size == 2 ? (dec << 16) | (dec >> 16) : dec;
		}
		write(fd, &dec, write_size);
	}
}

int		write_to_cor(t_line *tab, t_header *header, t_tools *tools)
{
	int i;
	int	opcode;
	int	coding_byte;

	i = 0;
	coding_byte = 0;
	opcode = 0;
	write(tools->fd, header, sizeof(t_header));
	while (i < tools->tablen)
	{
		if (tab[i].instruc)
		{
			opcode = get_opcode(tab[i].instruc);
			write(tools->fd, &opcode, 1);
			if (has_coding_byte(tab[i].instruc))
			{
				coding_byte = get_coding_byte(tab, i);
				write(tools->fd, &coding_byte, 1);
			}
			if (tab[i].param1)
			{
				is_called_label(tab[i].param1, tab[i].param1_sz) ?
				write_called_label(tools, i, tab, tab[i].param1_sz) :
				write_param(tools->fd, tab[i].param1, tab[i].param1_sz);
			}
			if (tab[i].param2)
			{
				is_called_label(tab[i].param2, tab[i].param2_sz) ?
				write_called_label(tools, i, tab, tab[i].param2_sz) :
				write_param(tools->fd, tab[i].param2, tab[i].param2_sz);
			}
			if (tab[i].param3)
			{
				is_called_label(tab[i].param3, tab[i].param3_sz) ?
				write_called_label(tools, i, tab, tab[i].param2_sz) :
				write_param(tools->fd, tab[i].param3, tab[i].param3_sz);
			}
		}
		i++;
	}
	return (1);
}
