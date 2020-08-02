/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:35 by myener            #+#    #+#             */
/*   Updated: 2020/08/02 20:58:31 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char	**append_return(char **in)
{
	int		i;

	i = 0;
	while (in[i])
	{
		in[i] = ft_free_join(in[i], "\n");
		i++;
	}
	if (i == 0)
	{
		in ? tab_free(in) : 0;
		return (NULL);
	}
	return (in);
}

static int	asm_translator(int fd, char **input, char *out, t_tools *tools)
{
	t_header	*header;
	t_line		*struct_tab;

	tools->tablen = (int)ft_tablen((void **)input) - lines_to_deduce(input);
	if (!(header = malloc(sizeof(t_header) * 1)))
		return (0);
	if (!(struct_tab = malloc(sizeof(t_line) * tools->tablen)))
		return (0);
	ft_bzero(header, sizeof(t_header));
	asm_struct_tab_init(struct_tab, tools->tablen);
	if (!struct_tab_fill(input, struct_tab, tools)
		|| !header_fill(header, input, tools))
	{
		remove(out);
		return (asm_struct_tab_free(struct_tab, tools->tablen, header, 0));
	}
	tools->fd = fd;
	if (!write_to_cor(struct_tab, header, tools))
	{
		remove(out);
		return (asm_struct_tab_free(struct_tab, tools->tablen, header, 0));
	}
	return (asm_struct_tab_free(struct_tab, tools->tablen, header, 1));
}

static char	**get_fc(char *file_name)
{
	int		fd;
	char	*tmp;
	char	*line;
	char	*stock;
	char	**content;

	stock = ft_strnew(1);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (NULL);
	while (get_next_line2(fd, &line))
	{
		tmp = line;
		stock = ft_free_join(stock, line);
		stock = ft_free_join(stock, "\n");
		tmp ? free(tmp) : 0;
	}
	close(fd);
	content = ft_strsplit(stock, '\n');
	content = append_return(content);
	stock ? ft_strdel(&stock) : 0;
	return (content);
}

static int	usage_checkup(int ac, char **av)
{
	if (ac < 2 || (av[1] && (!(av[1][ft_strlen(av[1]) - 1] == 's'
		&& av[1][ft_strlen(av[1]) - 2] == '.'))))
		return (1);
	return (0);
}

int			main(int ac, char **av)
{
	int		fd;
	char	*in_fn;
	char	*out_fn;
	char	**in_fc;
	t_tools	tools;

	asm_tools_init(&tools);
	if (usage_checkup(ac, av))
		return (usage_output());
	in_fn = ft_strdup2(av[1]);
	if (!(in_fc = get_fc(in_fn)))
		return (main_free_helper(in_fn, NULL, in_fc, 1));
	if (bad_dot_line(in_fc))
		return (main_free_helper(in_fn, NULL, in_fc, 0));
	out_fn = ft_strsub2(in_fn, 0, ft_strlen(in_fn) - 1);
	out_fn = ft_free_join(out_fn, "cor");
	fd = open(out_fn, O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (main_free_helper(in_fn, out_fn, in_fc, 1));
	if (!asm_translator(fd, in_fc, out_fn, &tools))
		return (main_free_helper(in_fn, out_fn, in_fc, 1));
	close(fd);
	main_free_helper(in_fn, out_fn, in_fc, 0);
	return (0);
}
