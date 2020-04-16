/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 08:09:19 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 16:16:54 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <stdint.h>
# include <curses.h>
# include <errno.h>
# include <locale.h>
# include <limits.h>
# include "op.h"
# include "libft.h"

/*
** Defines
*/

# define VM_NAME				"Corewar"
# define HEADER_PATH			"./header"

# define VM_OPTIONS				"havVdsc"
# define VM_OP_H				1	// helper
# define VM_OP_A				2	// aff
# define VM_OP_V				4	// verbose
# define VM_OP_UP_V				8	// verbose fr
# define VM_OP_D				16	// dump
# define VM_OP_S				32	// sleep
# define VM_OP_C				64	// visu ncurse

/*
** Display
*/

# define OUT_WIDTH			102
# define OUT_WIDTH_MIN		70

# define PAUSE				0
# define RUN				1
# define FW					2
# define STOP				3

# define DFLT_SPEED			50

/*
** Colors
*/

# define P1_COLOR		COLOR_GREEN
# define P2_COLOR		COLOR_BLUE
# define P3_COLOR		COLOR_RED
# define P4_COLOR		COLOR_CYAN
# define P1_FCOLOR		"\033[1;32m" // green
# define P2_FCOLOR		"\033[1;36m" // cyan
# define P3_FCOLOR		"\033[1;35m" // purple
# define P4_FCOLOR		"\033[1;33m" // Yellow
# define P1_BCOLOR		"\033[0;30;42m"
# define P2_BCOLOR		"\033[0;30;46m"
# define P3_BCOLOR		"\033[0;30;45m"
# define P4_BCOLOR		"\033[0;30;43m"
# define ERR_COLOR		99
# define NORMAL_COLOR	100
# define RCOLOR			256
# define WCOLOR			128


/*
** Structures
*/



typedef struct			s_arg
{
	t_arg_type		type;
	uint8_t			reg;
	int				index;
	uintmax_t		val;
}						t_arg;


typedef struct			s_buff
{
	char	*str;
	size_t	len;
	size_t	max_len;
}						t_buff;

typedef struct			s_champ
{
	int				id;
	int				number;
	char			*file;
	t_header		header;

	int				alive;
	int				n_procs;
	int				last_live;
	int				cur_lives;
	int				last_lives;

	unsigned char	prog[CHAMP_MAX_SIZE];

	t_buff			aff;

	struct s_champ	*next;
}						t_champ;

typedef struct			s_proc
{
	//int					id;
	//char				*name;

	int					id;
	int					number;

	int					prev_pc;
	int					pc; // program counter
	int					oc; // operation counter
	
	char				carry;
	int					lives;
	int					last_live;
	int					sleep;

	intmax_t			regs[REG_NUMBER];
	t_op				*op;

	t_champ				*champ;
	struct s_proc		*next;
}						t_proc;

typedef struct			s_box
{
	int					row;
	int					col;
	int					x;
	int					y;
}						t_box;

typedef struct			s_display
{
	int					run;
	int					speed;
	int					el_per_line;
	
	t_box				head;
	t_box				field;
	t_box				info;
	t_box				leg;
	t_box				out;

	WINDOW				*wfield;
	WINDOW				*winfo;
	WINDOW				*wleg;
	WINDOW				*wout;
}						t_display;


typedef struct			s_cell
{
	unsigned char		color;
	unsigned char		modified;
	unsigned char		live;
	unsigned char		reverse;
	int					cycle;
}						t_cell;

typedef struct			s_vm
{
	char				**av;
	int					ac;

	int					options;
	int					option_nb;
	int					dump;
	//int				debug;

	// int					affd;
	// int					affx;
	// int					affx2;

	int					cycle;
	int					cycle_ctd;
	int					cycle_to_die;
	int					checks;
	int					goto_cycle;
	int					nbr_live;
	int					max_checks;
	int					total_lives;
	
	int					lives;
	int					last_live;
	char				*last_name;
	t_champ				*last_live_champ;

	unsigned char		field[MEM_SIZE];
	t_cell				cells[MEM_SIZE];

	int					n_champs;
	t_champ				*champ;

	int					id_procs;
	int					n_procs;
	t_proc				*proc;
	
	t_display			display;

	char				*err;

	t_champ				*survivor;
}						t_vm;

extern void				(*g_op_func_tab[18])(t_vm *, t_proc *);
extern char				*g_base;

typedef void			(*t_operation_code)(t_vm *vm, t_proc *ps);

/*
** Prototypes
*/

# include "prototypes.h"

#endif
