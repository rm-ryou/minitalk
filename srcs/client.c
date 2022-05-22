/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:50 by rmoriya           #+#    #+#             */
/*   Updated: 2022/05/23 05:52:32 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	put_message(char *s)
{
	ft_putendl_fd(s, 1);
	return (1);
}

static int	send_bit(pid_t pid, char byte)
{
	int			kill_ret;
	u_int8_t	counter;

	counter = 0;
	while (counter < CHAR_BIT)
	{
		if ((byte >> counter) & 1)
			kill_ret = kill(pid, SIGUSR1);
		else
			kill_ret = kill(pid, SIGUSR2);
		if (kill_ret == -1)
			return (1);
		counter += 1;
		usleep(SLEEP);
	}
	return (0);
}

static int	send_char(pid_t pid, char *message)
{
	size_t	i;

	i = 0;
	while (message[i] != '\0')
	{
		if (send_bit(pid, message[i]))
			return (1);
		i++;
	}
	return (0);
}

static pid_t	check_pid(char *pid_str)
{
	size_t	i;

	i = 0;
	while (pid_str[i] != '\0')
	{
		if ((pid_str[i] < '0' || pid_str[i] > '9') || i >= 5)
			return (0);
		i++;
	}
	return (ft_atoi(pid_str));
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		return (put_message("usage : ./client [pid_number] [message]"));
	pid = check_pid(argv[1]);
	if (pid == 0)
		return (put_message("pid_number is wrong"));
	if (send_char(pid, argv[2]))
		return (put_message("pid_number is wrong"));
	return (0);
}
