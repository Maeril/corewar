/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:40:01 by myener            #+#    #+#             */
/*   Updated: 2020/06/24 20:44:04 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		get_opcode(char *instruc)
{
	if (!ft_strcmp(instruc, "live") || !ft_strcmp(instruc, "ld"))
		return (!ft_strcmp(instruc, "live") ? 1 : 2);
	else if (!ft_strcmp(instruc, "st") || !ft_strcmp(instruc, "add"))
		return (!ft_strcmp(instruc, "st") ? 3 : 4);
	else if (!ft_strcmp(instruc, "sub") || !ft_strcmp(instruc, "and"))
		return (!ft_strcmp(instruc, "sub") ? 5 : 6);
	else if (!ft_strcmp(instruc, "or") || !ft_strcmp(instruc, "xor"))
		return (!ft_strcmp(instruc, "or") ? 7 : 8);
	else if (!ft_strcmp(instruc, "zjmp") || !ft_strcmp(instruc, "ldi"))
		return (!ft_strcmp(instruc, "zjmp") ? 9 : 10);
	else if (!ft_strcmp(instruc, "sti") || !ft_strcmp(instruc, "fork"))
		return (!ft_strcmp(instruc, "sti") ? 11 : 12);
	else if (!ft_strcmp(instruc, "lld") || !ft_strcmp(instruc, "lldi"))
		return (!ft_strcmp(instruc, "lld") ? 13 : 14);
	else if (!ft_strcmp(instruc, "lfork") || !ft_strcmp(instruc, "aff"))
		return (!ft_strcmp(instruc, "lfork") ? 15 : 16);
	return (0);
}

int		get_cb(t_line *tab, int i)
{
	int		j;
	int		counter;
	char	*byte;
	char	*tmp;
	int		ret;

	counter = 2;
	byte = ft_strnew(1);
	if (tab[i].p1 > 0)
		byte = get_coding_byte_helper(byte, tab[i].p1[0], tab[i].p1_sz);
	if (tab[i].p2 > 0)
		byte = get_coding_byte_helper(byte, tab[i].p2[0], tab[i].p2_sz);
	if (tab[i].p3 > 0)
		byte = get_coding_byte_helper(byte, tab[i].p3[0], tab[i].p3_sz);
	counter += (tab[i].p2 > 0) ? 2 : 0;
	counter += (tab[i].p3 > 0) ? 2 : 0;
	j = -1;
	while (++j < (8 - counter))
		byte = ft_free_join(byte, "0");
	tmp = base_converter(byte, BIN, DECI);
	ret = ft_atoi(tmp);
	tmp ? free(tmp) : 0;
	return (ret);
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
	}
	else
	{
		tmp = str[0] == '%' ? ft_strsub(str, 1, ft_strlen(str) - 1) : NULL;
		dec = str[0] == '%' ? ft_atoi(tmp) : ft_atoi(str);
		tmp ? free(tmp) : 0;
	}
	if (write_size > 1)
	{
		dec = swap_uint32(dec);
		dec = write_size == 2 ? (dec << 16) | (dec >> 16) : dec;
	}
	write(fd, &dec, write_size);
}

int		write_to_cor(t_line *tab, t_header *header, t_tools *tools)
{
	int i;

	write(tools->fd, header, sizeof(t_header));
	i = -1;
	while (++i < tools->tablen)
		if (tab[i].instruc)
		{
			tools->opcode = get_opcode(tab[i].instruc);
			write(tools->fd, &tools->opcode, 1);
			tools->coding_byte = (has_cb(tab[i].instruc)) ? get_cb(tab, i) : 0;
			tools->coding_byte ? write(tools->fd, &tools->coding_byte, 1) : 0;
			if (tab[i].p1)
				is_called_label(tab[i].p1, tab[i].p1_sz) ?
				write_called_label(tools, i, tab, tab[i].p1_sz) :
				write_param(tools->fd, tab[i].p1, tab[i].p1_sz);
			if (tab[i].p2)
				is_called_label(tab[i].p2, tab[i].p2_sz) ?
				write_called_label(tools, i, tab, tab[i].p2_sz) :
				write_param(tools->fd, tab[i].p2, tab[i].p2_sz);
			if (tab[i].p3)
				is_called_label(tab[i].p3, tab[i].p3_sz) ?
				write_called_label(tools, i, tab, tab[i].p2_sz) :
				write_param(tools->fd, tab[i].p3, tab[i].p3_sz);
		}
	return (1);
}
