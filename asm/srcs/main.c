/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:35 by myener            #+#    #+#             */
/*   Updated: 2020/04/11 20:07:56 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

char	**get_file_content(char *file_name); // to be created (will use GNL)

void	asm_translator(int fd); // to be created (principal function)

int		main(int ac, char **av)
{
	int		fd;
	char	*in_file_name;
	char	*out_file_name;
	char	**in_file_content;

	if (ac < 2)
		return (-1); // temporary error output
	in_file_name = ft_strdup(av[1]); // copies input file's name for later
	in_file_content = get_file_content(in_file_name);
	out_file_name = ft_strsub(in_file_name, 0, ft_strlen(in_file_name) - 1); //copies input file name except "s"; "file.s" becomes "file."
	out_file_name = ft_free_join(out_file_name, "cor"); // adds "cor" extension to file name; "file." becomes "file.cor"
	fd = open(out_file_name, O_WRONLY); // opens out_file: it doesn't exists, so it creates it. open to WRITE in it.
	asm_translator(fd); // writes in out_file (using the fd) the content of in_file but in machinelang.
	free(in_file_name);
	free(out_file_name);
	tab_free(in_file_content);
	return (0);
}
