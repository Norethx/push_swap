/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:39:09 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/30 13:07:26 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_moves	which_operation(char *op);
static int		check_order(t_meta_ilist *nums);

int	main(int argc, char **argv)
{
	char			*str;

	if (argc <= 1)
		return (1);
	if (ft_gc_init())
		return (handle_error());
	if (!parsing_args(argv, argc))
		return (1);
	if (!core_utils())
		return (handle_error());
	while (1)
	{
		str = ft_gcfct_register_root(get_next_line(0), GC_DATA, "ops");
		if (!str)
			break ;
		if (which_operation(str) == -1)
			return (handle_error());
		handle_moves(which_operation(str));
	}
	if (!check_order(core_utils()->stack_a) && core_utils()->stack_b->size == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_gc_end();
}

static t_moves	which_operation(char *op)
{
	if (ft_strnstr("sa\n", op, 10))
		return (SA);
	else if (ft_strnstr("sb\n", op, 10))
		return (SB);
	else if (ft_strnstr("ss\n", op, 10))
		return (SS);
	else if (ft_strnstr("pa\n", op, 10))
		return (PA);
	else if (ft_strnstr("pb\n", op, 10))
		return (PB);
	else if (ft_strnstr("ra\n", op, 10))
		return (RA);
	else if (ft_strnstr("rb\n", op, 10))
		return (RB);
	else if (ft_strnstr("rr\n", op, 10))
		return (RR);
	else if (ft_strnstr("rra\n", op, 10))
		return (RRA);
	else if (ft_strnstr("rrb\n", op, 10))
		return (RRB);
	else if (ft_strnstr("rrr\n", op, 10))
		return (RRR);
	else
		return (NONE);
}

static int	check_order(t_meta_ilist *nums)
{
	t_ilist	*aux;

	if (!nums || nums->size == 0)
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
