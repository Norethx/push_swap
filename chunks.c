/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:52:04 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/29 13:49:59 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_all_chunks	create_chunks(t_divides chunk, t_core *stack,
		t_all_chunks others)
{
	int	i[2];

	others.side[LOWERS] = aux_create_chunks(chunk, LOWERS);
	others.side[AVERAGE] = aux_create_chunks(others.side[LOWERS], AVERAGE);
	others.side[HIGHERS] = aux_create_chunks(others.side[AVERAGE], HIGHERS);
	verify_chunks(&chunk, &stack, &others);
	while (chunk.size-- > 0)
	{
		i[1] = AVERAGE;
		i[0] = stack->stack_a->head->r_pos;
		if (chunk.w_side == BOT_A)
			i[0] = stack->stack_a->tail->r_pos;
		else if (chunk.w_side == TOP_B)
			i[0] = stack->stack_b->head->r_pos;
		else if (chunk.w_side == BOT_B)
			i[0] = stack->stack_b->tail->r_pos;
		if (i[0] > others.side[AVERAGE].num_final)
			i[1] = HIGHERS;
		else if (i[0] < others.side[AVERAGE].num_init)
			i[1] = LOWERS;
		calculate_move(stack, chunk.w_side, others.side[i[1]]);
	}
	return (others);
}

void	verify_chunks(t_divides *chunk, t_core **stack, t_all_chunks *others)
{
	int	i;

	i = stack[0]->stack_a->head->r_pos;
	if (chunk->w_side == BOT_A && (i >= chunk->num_init
			&& i <= chunk->num_final))
		chunk->w_side = TOP_A;
	if (stack[0]->stack_b->head)
		i = stack[0]->stack_b->head->r_pos;
	if (chunk->w_side == BOT_B && (i >= chunk->num_init
			&& i <= chunk->num_final))
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
	return (chunk);
}
