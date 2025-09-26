/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:53:45 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/25 15:54:34 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
// rrr : rra e rrb ao mesmo tempo.

int	ra(void)
{
	t_core	*core;

	core = core_utils();
	rotate(&core->stack_a);
	core->last_move = NONE;
	ft_printf("ra\n");
	return (1);
}
int	rb(void)
{
	t_core	*core;

	core = core_utils();
	rotate(&core->stack_b);
	core->last_move = NONE;
	ft_printf("rb\n");
	return (1);
}

int	rr(void)
{
	t_core	*core;

	core = core_utils();
	rotate(&core->stack_a);
	rotate(&core->stack_b);
	core->last_move = NONE;
	ft_printf("rr\n");
	return (1);
}

int	rra(void)
{
	t_core	*core;

	core = core_utils();
	reverse_rotate(&core->stack_a);
	core->last_move = NONE;
	ft_printf("rra\n");
	return (1);
}
int	rrb(void)
{
	t_core	*core;

	core = core_utils();
	reverse_rotate(&core->stack_b);
	core->last_move = NONE;
	ft_printf("rrb\n");
	return (1);
}
