/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:35:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/11 19:31:13 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef enum e_error
{
	INVALID_ARGS,
	INVALID_NUMBER,
	NOT_INT_ERROR
}						t_error;

typedef struct s_ilist
{
	int					num;
	struct s_list_int	*next;
	struct s_list_int	*prev;
}						t_ilist;

typedef struct s_meta_ilist
{
	t_ilist				*head;
	t_ilist				*tail;
	int					size;
}						t_meta_ilist;

int	handle_error(t_error error);

#endif
