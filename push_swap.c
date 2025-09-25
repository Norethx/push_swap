/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:39:09 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/25 11:16:52 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_meta_ilist **stack);
void	push(t_meta_ilist **stack_1, t_meta_ilist **stack_2);
void	rotate(t_meta_ilist **stack);
void	reverse_rotate(t_meta_ilist **stack);

int	main(int argc, char **argv)
{
	t_meta_ilist	*nums;

	if (argc < 1)
		return(0);
	if (ft_gc_init())
		return (handle_error());
	nums = parsing_args(argv);
	if (!nums)
		return (1);
	ft_gc_end();
	return (0);
}
