/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 12:10:07 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/08 18:00:05 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "vm.h"
#include "libft.h"

static int	check_numbers(t_header *header)
{
	unsigned char 	*m1;

	m1 = (unsigned char*)&header->prog_size;
	header->prog_size = (m1[0] << 24) + (m1[1] << 16) + (m1[2] << 8) + m1[3];
	m1 = (unsigned char*)&header->magic;
	header->magic = (m1[0] << 24) + (m1[1] << 16) + (m1[2] << 8) + m1[3];
	return (header->magic != COREWAR_EXEC_MAGIC);
}

static int	read_champion(t_champ *champ)
{
	int		fd;

	if ((fd = open(champ->file, O_RDONLY)) < 0)
		return (file_not_found_error());
	if (read(fd, (void *)&champ->header, sizeof(t_header))
		< (int)sizeof(t_header) || check_numbers(&champ->header))
	{
		close(fd);
		return (invalid_file_error());
	}
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
	{
		close(fd);
		return (champion_size_too_big());
	}
	if (read(fd, (void *)&champ->prog[0], champ->header.prog_size)
		< (int)champ->header.prog_size)
	{
		close(fd);
		return (invalid_file_error());
	}
	close(fd);
	return (0);
}

int			read_champions(t_vm *vm)
{
	t_champ *champ;

	champ = vm->champ;
	while (champ)
	{
		if (read_champion(champ))
			return (1);
		champ = champ->next;
	}
	return (0);
}
