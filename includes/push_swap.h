/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:35:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/29 13:12:12 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef enum e_error
{
	INVALID_ARGS,
	INVALID_NUMBER,
	NOT_INT_ERROR,
	NOT_NUMBER,
}					t_error;

typedef enum e_moves
{
	NONE = -1,
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
}					t_moves;

typedef enum e_chunk
{
	ALL,
	LOWERS,
	AVERAGE,
	HIGHERS,
}					t_chunk;

typedef enum e_side
{
	TOP_A,
	BOT_A,
	TOP_B,
	BOT_B,
}					t_side;

typedef struct s_ilist
{
	int				num;
	struct s_ilist	*next;
	struct s_ilist	*prev;
	int				r_pos;
}					t_ilist;

typedef struct s_meta_ilist
{
	t_ilist			*head;
	t_ilist			*tail;
	t_side			w_side;
	int				size;
	t_chunk			w_chunk;
}					t_meta_ilist;

typedef struct s_core
{
	t_meta_ilist	*stack_a;
	t_meta_ilist	*stack_b;
	t_moves			last_move;
	int				cont;
}					t_core;

typedef struct s_divides
{
	t_chunk			w_chunk;
	t_side			w_side;
	int				num_init;
	int				num_final;
	int				size;
	int				mod;
}					t_divides;

typedef struct s_all_chunks
{
	t_divides		side[4];
}					t_all_chunks;

int					handle_error(void);
t_meta_ilist		*parsing_args(char **args);
int					verify_dup(t_meta_ilist **rtn);
t_core				*core_utils(void);
int					swap(t_meta_ilist **stack);
int					push(t_meta_ilist **stack_1, t_meta_ilist **stack_2);
void				rotate(t_meta_ilist **stack);
void				reverse_rotate(t_meta_ilist **stack);
void				control_moves(t_moves new_move, t_core *core);
int					handle_moves(t_moves move);
int					init_sorting(t_meta_ilist *stack);
int					sorting(t_divides chunk, t_core *stack);
t_all_chunks		create_chunks(t_divides chunk, t_core *stack,
						t_all_chunks others);
t_divides			aux_create_chunks(t_divides chunk, t_chunk w_chunk);
void				print_moves(t_core *core);
t_divides			resolve_mod(t_divides chunk);
void				calculate_move(t_core *core, t_side from, t_divides chunk);
void				verify_chunks(t_divides *chunk, t_core **stack,
						t_all_chunks *others);
void				sorting_final(t_core *core, t_side from, t_divides chunk,
						int qt);
void				last_sort(t_core *core, t_divides chunk);

#endif
