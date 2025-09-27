/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:39:09 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/27 13:41:38 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				check_order(t_meta_ilist *nums);
void			init_sorting(t_core *stack);
int				sorting(t_divides chunk, t_core *stack);
t_all_chunks	create_chunks(t_divides chunk, t_core *stack, t_all_chunks others);
t_divides		aux_create_chunks(t_divides chunk, t_chunk w_chunk);
void			print_moves(t_core *core);
t_divides		resolve_mod(t_divides chunk);
void			calculate_move(t_core *core, t_side from, t_divides chunk);
void			verify_chunks(t_divides *chunk, t_core **stack, t_all_chunks	*others);
void			sorting_final(t_core *core, t_side from, t_divides chunk, int qt);
void			last_sort(t_core *core, t_divides chunk);

int	main(int argc, char **argv)
{
	t_meta_ilist	*nums;
	t_core			*core;

	if (argc <= 1)
		return (0);
	if (ft_gc_init())
		return (handle_error());
	nums = parsing_args(argv);
	if (!nums)
		return (1);
	if (check_order(nums))
	{
		if (!core_utils())
			return (handle_error());
		core = core_utils();
		init_sorting(core);
	}
	ft_gc_end();
	return (0);
}
void	init_sorting(t_core *stack)
{
	t_divides	main;

	main.num_final = stack->stack_a->size;
	main.num_init = 1;
	main.size = stack->stack_a->size;
	main.w_chunk = ALL;
	main.w_side = TOP_A;
	main.mod = 0;
	sorting(main, stack);
	control_moves(NONE, stack);
}

int	sorting(t_divides chunk, t_core *stack)
{
	t_all_chunks	others;

	if (chunk.size <= 3)
	{
		t_side aux; 
		
		aux = chunk.w_side;
		chunk.w_side = TOP_A;
		if (chunk.size == 3)
			sorting_final(stack, aux, chunk, 3);
		else if (chunk.size == 2)
			sorting_final(stack, aux, chunk, 2);
		else if (chunk.size == 1)
			calculate_move(stack, aux, chunk);
		return (0);
	}
	others = create_chunks(chunk, stack, others);
	sorting(others.side[HIGHERS], stack);
	sorting(others.side[AVERAGE], stack);
	sorting(others.side[LOWERS], stack);
	return (0);
}

void	sorting_final(t_core *core, t_side from, t_divides chunk, int qt)
{
	if (qt == 2)
	{
		calculate_move(core, from, chunk);
		calculate_move(core, from, chunk);
	}
	if (qt == 3)
	{
		calculate_move(core, from, chunk);
		calculate_move(core, from, chunk);
		calculate_move(core, from, chunk);
	}
}

t_all_chunks	create_chunks(t_divides chunk, t_core *stack, t_all_chunks others)
{
	int				i[2];

	others.side[LOWERS] = aux_create_chunks(chunk, LOWERS);
	others.side[AVERAGE] = aux_create_chunks(others.side[LOWERS], AVERAGE);
	others.side[HIGHERS] = aux_create_chunks(others.side[AVERAGE], HIGHERS);
	verify_chunks(&chunk, &stack, &others);
	while (chunk.size-- > 0)
	{
		if (chunk.w_side == TOP_A)
			i[0] = stack->stack_a->head->r_pos;
		else if (chunk.w_side == BOT_A)
			i[0] = stack->stack_a->tail->r_pos;
		else if (chunk.w_side == TOP_B)
			i[0] = stack->stack_b->head->r_pos;
		else if (chunk.w_side == BOT_B)
			i[0] = stack->stack_b->tail->r_pos;
		if (i[0] > others.side[AVERAGE].num_final)
			i[1] = HIGHERS;
		else if (i[0] < others.side[AVERAGE].num_init)
			i[1] = LOWERS;
		else
			i[1] = AVERAGE;
		calculate_move(stack, chunk.w_side, others.side[i[1]]);
	}
	return(others);
}

void	verify_chunks(t_divides *chunk, t_core **stack, t_all_chunks	*others)
{
	int				i;

	i = stack[0]->stack_a->head->r_pos;
	if (chunk->w_side == BOT_A && (i >= chunk->num_init && i <= chunk->num_final))
		chunk->w_side = TOP_A;
	if (stack[0]->stack_b->head)
		i = stack[0]->stack_b->head->r_pos;
	if (chunk->w_side == BOT_B && (i >= chunk->num_init && i <= chunk->num_final))
		chunk->w_side = TOP_B;
	if (others->side[LOWERS].w_side == chunk->w_side)
		others->side[LOWERS].w_side++;
	if (others->side[AVERAGE].w_side == chunk->w_side)
	{
		others->side[AVERAGE].w_side++;
		others->side[LOWERS].w_side++;
	}
	if (others->side[HIGHERS].w_side == chunk->w_side)
	{
		others->side[HIGHERS].w_side++;
		others->side[AVERAGE].w_side++;
		others->side[LOWERS].w_side++;
	}
}

void	calculate_move(t_core *core, t_side from, t_divides chunk)
{
	if (from == TOP_A && chunk.w_side == BOT_A)
		control_moves(RA, core);
	else if (from == TOP_A && (chunk.w_side > 1))
		control_moves(PB, core);
	if (from == TOP_A && chunk.w_side == BOT_B)
		control_moves(RB, core);
	if (from == BOT_A)
		control_moves(RRA, core);
	if (from == BOT_A && (chunk.w_side > 1))
		control_moves(PB, core);
	if (from == BOT_A && chunk.w_side == BOT_B)
		control_moves(RB, core);
	if (from == TOP_B && chunk.w_side == BOT_B)
		control_moves(RB, core);
	else if (from == TOP_B && (chunk.w_side < 2))
		control_moves(PA, core);
	if (from == TOP_B && chunk.w_side == BOT_A)
		control_moves(RA, core);
	if (from == BOT_B)
		control_moves(RRB, core);
	if (from == BOT_B && (chunk.w_side < 2))
		control_moves(PA, core);
	if (from == BOT_B && chunk.w_side == BOT_A)
		control_moves(RA, core);
	last_sort(core, chunk);
}

void	last_sort(t_core *core, t_divides chunk)
{
	int i[2];
	if(chunk.size <= 3)
	{
		if (chunk.w_side == TOP_A && core->stack_a->head
			&& core->stack_a->head->next)
		{
			i[0] = core->stack_a->head->r_pos;
			i[1] = core->stack_a->head->next->r_pos;
			if(i[0] > i[1])
				control_moves(SA, core);
		}
		if (chunk.w_side == TOP_A && core->stack_a->head
			&& core->stack_a->head->next && core->stack_a->head->next->next)
		{
			i[0] = core->stack_a->head->next->r_pos;
			i[1] = core->stack_a->head->next->next->r_pos;
			if(i[0] > i[1])
			{
				control_moves(RA, core);
				control_moves(SA, core);
				control_moves(RRA, core);
			}
		}
	}
}

t_divides	aux_create_chunks(t_divides chunk, t_chunk w_chunk)
{
	if (w_chunk == LOWERS)
	{
		chunk.mod = chunk.size % 3;
		chunk.size /= 3;
		chunk.w_side = TOP_B;
		chunk.num_final = chunk.num_init + chunk.size - 1;
	}
	else
	{
		if (w_chunk == HIGHERS)
			chunk.w_side = TOP_A;
		if (w_chunk == AVERAGE)
			chunk.w_side = BOT_A;
		chunk.num_init = chunk.num_final + 1;
		chunk.num_final = chunk.num_init + chunk.size - 1;
	}
	chunk.w_chunk = w_chunk;
	chunk = resolve_mod(chunk);
	return (chunk);
}

t_divides	resolve_mod(t_divides chunk)
{
	if (chunk.mod > 0 && chunk.w_chunk == LOWERS)
		chunk.size++;
	if (chunk.mod > 0 && chunk.w_chunk == LOWERS)
		chunk.num_final++;
	if (chunk.mod == 1 && chunk.w_chunk == AVERAGE)
		chunk.size--;
	if (chunk.mod == 1 && chunk.w_chunk == AVERAGE)
		chunk.num_final--;
	if (chunk.mod == 2 && chunk.w_chunk == HIGHERS)
		chunk.size--;
	if (chunk.mod == 2 && chunk.w_chunk == HIGHERS)
		chunk.num_final--;
	return(chunk);
}

void			control_moves(t_moves new_move, t_core *core)
{
	t_moves att_move;

	att_move = new_move;
	if (new_move != NONE)
		core->func[new_move]();
	if ((new_move == SA && core->last_move == SB) || (new_move == SB &&
		core->last_move == SA))
		att_move = SS;
	else if ((new_move == RA && core->last_move == RB) || (new_move == RB &&
		core->last_move == RA))
		att_move = RR;
	else if ((new_move == RRA && core->last_move == RRB) || (new_move == RRB &&
		core->last_move == RRA))
		att_move = RRR;
	if ((new_move == RRA && core->last_move == RA) || (new_move == RA &&
		core->last_move == RRA) || (new_move == RRB && core->last_move == RB)
		|| (new_move == RB && core->last_move == RRB))
	{
			att_move = NONE;
			core->last_move = NONE;
	}
	if (att_move == new_move)
		print_moves(core);
	new_move = att_move;
	core->last_move = new_move;
}

void	print_moves(t_core *core)
{
	if (core->last_move == SA)
		ft_printf("sa\n");
	else if (core->last_move == SB)
		ft_printf("sb\n");
	else if (core->last_move == SS)
		ft_printf("ss\n");
	else if (core->last_move == PA)
		ft_printf("pa\n");
	else if (core->last_move == PB)
		ft_printf("pb\n");
	else if (core->last_move == RA)
		ft_printf("ra\n");
	else if (core->last_move == RB)
		ft_printf("rb\n");
	else if (core->last_move == RR)
		ft_printf("rr\n");
	else if (core->last_move == RRA)
		ft_printf("rra\n");
	else if (core->last_move == RRB)
		ft_printf("rrb\n");
	else if (core->last_move == RRR)
		ft_printf("rrr\n");
}

t_core	*core_utils(void)
{
	static t_core	*stacks = NULL;

	if (!stacks)
	{
		stacks = ft_gc_calloc_root(1, sizeof(t_core), GC_DATA, "history");
		stacks->stack_a = ((t_gc_list *)ft_gc_content_root("stack_a")->content)->content;
		stacks->stack_b = ft_gc_calloc_root(1, sizeof(t_meta_ilist), GC_DATA,
				"stack_b");
		stacks->stack_b->w_side = TOP_B;
		stacks->stack_b->w_chunk = ALL;
		stacks->last_move = NONE;
		stacks->func[0] = &sa;
		stacks->func[1] = &sb;
		stacks->func[2] = &ss;
		stacks->func[3] = &pa;
		stacks->func[4] = &pb;
		stacks->func[5] = &ra;
		stacks->func[6] = &rb;
		stacks->func[7] = &rr;
		stacks->func[8] = &rra;
		stacks->func[9] = &rrb;
		stacks->func[10] = &rrr;
	}
	return (stacks);
}

int	check_order(t_meta_ilist *nums)
{
	t_ilist	*aux;

	if (!nums)
		return (1);
	aux = nums->head;
	while (aux->next)
	{
		if (aux->num > aux->next->num)
			return (1);
		aux = aux->next;
	}
	return (0);
}
