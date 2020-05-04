/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:15:08 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 20:38:03 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "vm.h"

void	display_header(t_vm *vm)
{
	int		fd;
	int		ret;
	char	*line;
	int		len;

	line = NULL;
	vm->display.head.row = 0;
	vm->display.head.col = 0;
	vm->display.head.x = 0;
	vm->display.head.y = 0;
	if ((fd = open(HEADER_PATH, O_RDONLY | O_NOFOLLOW | O_NOCTTY | O_NONBLOCK, S_IRUSR)) == -1)
		exit_vm(vm, "header file opening error", 1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		len = ft_strlen(line);
		vm->display.head.col = vm->display.head.col == 0 ? len : vm->display.head.col;
		vm->display.head.x = vm->display.head.x == 0 ? ft_sqrt(MEM_SIZE) + 15 : vm->display.head.x;
		mvprintw(vm->display.head.row++, vm->display.head.x, "%s\n", line);
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	if (ret < 0 || (close(fd) == -1))
		exit_vm(vm, "header file reading error", 1);

}
