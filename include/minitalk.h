/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:17:36 by rmoriya           #+#    #+#             */
/*   Updated: 2022/05/18 15:25:16 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
#include <limits.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_signal
{
	volatile sig_atomic_t	signum;
	u_int8_t				shift_index;
	u_int8_t				res;
}	t_signal;

#endif
