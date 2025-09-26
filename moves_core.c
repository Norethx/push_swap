/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:31:24 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/26 14:33:01 by rgomes-d         ###   ########.fr       */
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
	t_ilist	*aux;

	if (stack[0]->size < 2)
		return (1);
	aux = stack[0]->head->next;
	stack[0]->head->prev = aux;
	stack[0]->head->next = aux->next;
	aux->next = stack[0]->head;
	aux->prev = NULL;
	stack[0]->head = aux;
	return (0);
}
int	push(t_meta_ilist **stack_1, t_meta_ilist **stack_2)
{
	t_ilist	*aux[2];

	if (stack_2[0]->size == 0)
		return (1);
	if (stack_2[0]->head)
		aux[0] = stack_2[0]->head->next;
	else
		aux[0] = NULL;
	aux[1] = stack_2[0]->head;
	if (aux[0] && aux[0]->prev)
		aux[0]->prev = NULL;
	aux[1]->next = stack_1[0]->head;
	if (stack_1[0]->head)
		stack_1[0]->head->prev = aux[1];
	if (!stack_1[0]->head)
		stack_1[0]->tail = aux[1];
	stack_1[0]->head = aux[1];
	stack_2[0]->head = aux[0];
	stack_1[0]->size++;
	stack_2[0]->size--;
	return (0);
}

void	rotate(t_meta_ilist **stack)
{
	t_ilist	*aux[2];

	if (stack[0]->size < 2)
		return ;
	aux[0] = stack[0]->head->next;
	aux[1] = stack[0]->head;
	aux[0]->prev = NULL;
	aux[1]->prev = stack[0]->tail;
	aux[1]->next = NULL;
	stack[0]->head = aux[0];
	stack[0]->tail->next = aux[1];
	stack[0]->tail = aux[1];
}

void	reverse_rotate(t_meta_ilist **stack)
{
	t_ilist	*aux[2];

	if (stack[0]->size < 2)
		return ;
	aux[0] = stack[0]->tail->prev;
	aux[1] = stack[0]->tail;
	aux[0]->next = NULL;
	aux[1]->next = stack[0]->head;
	aux[1]->prev = NULL;
	stack[0]->tail = aux[0];
	aux[0] = stack[0]->head;
	stack[0]->head->prev = aux[1];
	stack[0]->head = aux[1];
}
