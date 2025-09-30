/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:55:26 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/30 10:58:47 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sorting(t_divides chunk, t_core *stack)
{
	t_all_chunks	others;
	t_side			aux;

	ft_bzero(&others, sizeof(t_all_chunks));
	if (chunk.size <= 3)
	{
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

void	last_sort(t_core *core, t_divides chunk)
{
	int	i[2];

	if (core->stack_a->size == 3 && chunk.size <= 3 && chunk.w_side == TOP_A)
		return (sort_three(core->stack_a));
	if (chunk.size <= 3 && chunk.w_side == TOP_A && core->stack_a->head
		&& core->stack_a->head->next)
	{
		i[0] = core->stack_a->head->r_pos;
		i[1] = core->stack_a->head->next->r_pos;
		if (i[0] > i[1])
			control_moves(SA, core);
	}
	if (chunk.size <= 3 && chunk.w_side == TOP_A && core->stack_a->head
		&& core->stack_a->head->next && core->stack_a->head->next->next)
	{
		i[0] = core->stack_a->head->next->r_pos;
		i[1] = core->stack_a->head->next->next->r_pos;
		if (i[0] > i[1])
		{
			control_moves(RA, core);
			control_moves(SA, core);
			control_moves(RRA, core);
		}
	}
}

t_core	*core_utils(void)
{
	static t_core	*stacks = NULL;

	if (!stacks)
	{
		stacks = ft_gc_calloc_root(1, sizeof(t_core), GC_DATA, "history");
		stacks->stack_a = ft_gc_content_root("stack_a")->content;
		stacks->stack_a = ((t_gc_list *)stacks->stack_a)->content;
		stacks->stack_b = ft_gc_calloc_root(1, sizeof(t_meta_ilist), GC_DATA,
				"stack_b");
		stacks->stack_b->w_side = TOP_B;
		stacks->stack_b->w_chunk = ALL;
		stacks->last_move = NONE;
	}
	return (stacks);
}
