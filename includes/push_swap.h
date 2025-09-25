/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:35:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/24 20:18:57 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef enum e_error
{
	INVALID_ARGS,
	INVALID_NUMBER,
	NOT_INT_ERROR,
	NOT_NUMBER

}					t_error;

typedef enum e_chunck
{
	LOWERS,
	AVERAGE,
	HIGHERS,
	ALL
}					t_chunck;

typedef enum e_side
{
	A,
	B,
}					t_side;

typedef struct s_ilist
{
	int				num;
	struct s_ilist	*next;
	struct s_ilist	*prev;
	int				pos;
	int				r_pos;
}					t_ilist;

typedef struct s_meta_ilist
{
	t_ilist			*head;
	t_ilist			*tail;
	int				init_pos;
	int				final_pos;
	t_side			w_side;
	int				size;
	t_chunck		w_chunck;
}					t_meta_ilist;

int					handle_error(void);
t_meta_ilist		*parsing_args(char **args);

#endif
