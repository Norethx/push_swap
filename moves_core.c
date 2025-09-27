/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:31:24 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/27 14:10:27 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rrr(void)
{
	t_core	*core;

	core = core_utils();
	reverse_rotate(&core->stack_a);
	reverse_rotate(&core->stack_b);
	return (1);
}

int	swap(t_meta_ilist **stack)
{
	t_ilist	*first;
	t_ilist	*second;
	t_ilist	*third;

	if ((*stack)->size < 2)
		return (1);
	first = (*stack)->head;
	second = first->next;
	third = second->next;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	first->next = third;
	if (third)
		third->prev = first;
	else
		(*stack)->tail = first;
	(*stack)->head = second;
	return (0);
}
int	push(t_meta_ilist **stack_1, t_meta_ilist **stack_2)
{
	t_ilist	*aux[2];

	if (stack_2[0]->size == 0)
		return (1);
	if (stack_2[0]->size > 1)
		aux[0] = stack_2[0]->head->next;
	if (stack_2[0]->size > 1)
		aux[0]->prev = NULL;
	else
		aux[0] = NULL;
	aux[1] = stack_2[0]->head;
	aux[1]->next = stack_1[0]->head;
	if (stack_1[0]->head)
		stack_1[0]->head->prev = aux[1];
	if (!stack_1[0]->head)
		stack_1[0]->tail = aux[1];
	stack_1[0]->head = aux[1];
	stack_2[0]->head = aux[0];
	stack_1[0]->size++;
	stack_2[0]->size--;
	if	(!stack_2[0]->head)
		stack_2[0]->tail = NULL;
	if	(!stack_2[0]->tail)
		stack_2[0]->head = NULL;
	return (0);
}

void	rotate(t_meta_ilist **stack)
{
	t_ilist	*old_head;
	t_ilist	*new_head;

	if (stack[0]->size < 2)
		return ;
	old_head = stack[0]->head;
	new_head = old_head->next;
	new_head->prev = NULL;
	old_head->next = NULL;
	old_head->prev = stack[0]->tail;
	stack[0]->tail->next = old_head;
	stack[0]->head = new_head;
	stack[0]->tail = old_head;
}

void	reverse_rotate(t_meta_ilist **stack)
{
	t_ilist	*old_tail;
	t_ilist	*new_tail;

	if (stack[0]->size < 2)
		return ;
	old_tail = stack[0]->tail;
	new_tail = old_tail->prev;
	new_tail->next = NULL;
	old_tail->prev = NULL;
	old_tail->next = stack[0]->head;
	stack[0]->head->prev = old_tail;
	stack[0]->head = old_tail;
	stack[0]->tail = new_tail;
}
