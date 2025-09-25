/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:31:24 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/25 11:11:32 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_meta_ilist **stack)
{
	t_ilist	*aux;

	if (stack[0]->size < 2)
		return ;
	aux = stack[0]->head->next;
	stack[0]->head->prev = aux;
	stack[0]->head->next = aux->next;
	stack[0]->head->pos = 2;
	aux->next = stack[0]->head;
	aux->prev = NULL;
	aux->pos = 1;
	stack[0]->head = aux;
}
void	push(t_meta_ilist **stack_1, t_meta_ilist **stack_2)
{
	t_ilist	*aux[2];

	if (stack_2[0]->size == 0)
		return ;
	aux[0] = stack_2[0]->head->next;
	aux[1] = stack_2[0]->head;
	aux[0]->prev = NULL;
	aux[1]->next = stack_1[0]->head;
	stack_1[0]->head->prev = aux[1];
	stack_1[0]->head = aux[1];
	stack_2[0]->head = aux[0];
	stack_1[0]->size++;
	stack_2[0]->size--;
	while (aux[0])
	{
		aux[0]->pos--;
		aux[0] = aux[0]->next;
	}
	aux[1] = aux[1]->next;
	while (aux[1])
	{
		aux[1]->pos++;
		aux[1] = aux[1]->next;
	}
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
	while (aux[0])
	{
		aux[0]->pos--;
		aux[0] = aux[0]->next;
	}
	stack[0]->tail->next = aux[1];
	aux[1]->pos = stack[0]->tail->pos + 1;
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
	while (aux[0])
	{
		aux[0]->pos++;
		aux[0] = aux[0]->next;
	}
	stack[0]->head->prev = aux[1];
	aux[1]->pos = 1;
	stack[0]->head = aux[1];
}

// sa (swap a): Troca os 2 primeiros elementos no topo da pilha a.
// Não faz nada se houver apenas um elemento ou nenhum.
// sb (swap b): Troca os 2 primeiros elementos no topo da pilha b.
// Não faz nada se houver apenas um elemento ou nenhum.
// ss : sa e sb ao mesmo tempo.
// pa (push a): Pega o primeiro elemento no topo de b e o coloca no topo de a.
// Não faz nada se b estiver vazia.
// pb (push b): Pega o primeiro elemento no topo de a e o coloca no topo de b.
// Não faz nada se a estiver vazia.
// ra (rotate a): Move todos os elementos da pilha a para cima em 1.
// O primeiro elemento se torna o último.
// rb (rotate b): Move todos os elementos da pilha b para cima em 1.
// O primeiro elemento se torna o último.
// rr : ra e rb ao mesmo tempo.
// rra (reverse rotate a): Move todos os elementos da pilha a para baixo em 1.
// O último elemento se torna o primeiro.
// rrb (reverse rotate b): Move todos os elementos da pilha b para baixo em 1.
// O último elemento se torna o primeiro.
// rrr : rra e rrb ao mesmo tempo
