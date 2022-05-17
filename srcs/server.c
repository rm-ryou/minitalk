/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:58 by rmoriya           #+#    #+#             */
/*   Updated: 2022/05/17 16:31:01 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_signal	g_signal;

static void	print_pid(void)
{
	ft_putstr_fd("pid : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

static void	signal_receive(int signal)
{
	g_signal.signum = signal;
}

void	get_char()
{
	if (g_signal.signum == SIGUSR1)
		g_signal.res |= (1 << g_signal.shift_index);
	if (g_signal.shift_index == 7)
	{
		ft_putchar_fd(g_signal.res, 1);
		g_signal.res = 0;
		g_signal.shift_index = 0;
		return ;
	}
	g_signal.shift_index += 1;
	g_signal.signum = 0;
}

void	init()
{
	g_signal.signum = 0;
	g_signal.shift_index = 0;
}

int	main(void)
{
	init();
	print_pid();
	signal(SIGUSR1, signal_receive);
	signal(SIGUSR2, signal_receive);
	while (1)
	{
		pause();
		get_char();
	}
}
