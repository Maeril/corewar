/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:35 by myener            #+#    #+#             */
/*   Updated: 2020/04/13 18:43:20 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

// void	asm_translator(int fd, char **input); // to be created (principal function)
// {
// 	int		i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		i++;
// 	}
// }

char	**get_file_content(char *file_name)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*line;
	char	*stock;
	char	**content;

	i = 0;
	stock = ft_strnew(1);
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tmp = line;
		stock = ft_free_join(stock, line);
		stock = ft_free_join(stock, "\n");
		free(tmp);
		i++;
	}
	close(fd);
	content = ft_strsplit(stock, '\0');
	ft_strdel(&stock);
	return (content);
}

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
	ft_printf("out_file_name = %s\n", out_file_name);
	fd = open(out_file_name, O_WRONLY | O_CREAT); // opens out_file: it doesn't exists, so it creates it. open to WRITE in it.
	// asm_translator(fd, in_file_content); // writes the content of in_file in out_file, translated in machinelang.
	// close(fd);
	free(in_file_name);
	free(out_file_name);
	tab_free(in_file_content);
	return (0);
}
