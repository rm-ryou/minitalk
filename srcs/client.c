/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:50 by rmoriya           #+#    #+#             */
/*   Updated: 2022/05/17 16:22:37 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	put_message(char *s)
{
	ft_putendl_fd(s, 1);
	return (1);
}

void	error_exit(char *s)
{
	ft_putendl_fd(s, 1);
	exit(1);
}

void	send_byte(pid_t pid, char byte)
{
	int			kill_ret;
	u_int8_t	counter;

	counter = 0;
	while (counter < 8)
	{
		if ((byte >> counter) & 1)
			kill_ret = kill(pid, SIGUSR1);
		else
			kill_ret = kill(pid, SIGUSR2);
		if (kill_ret == -1)
			error_exit("pid_number is wrong");
		counter += 1;
		usleep(300);
	}
}

void	handle_signal(pid_t pid, char *message)
{
	size_t	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_byte(pid, message[i]);
		i++;
	}
}

pid_t	get_pid(char *pid_str)
{
	size_t	i;

	i = 0;
	while (pid_str[i] != '\0')
	{
		if ((pid_str[i] < '0' || pid_str[i] > '9') || i >= 5)
			error_exit("invalid pid_number");
		i++;
	}
	return (ft_atoi(pid_str));
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	//	return (put_message("usage : ./client [pid_number] [message]"));
		error_exit("usage : ./client [pid_number] [message]");
	pid = get_pid(argv[1]);
	if (pid == 0)
	//	return (put_message("pid_number is wrong"));
		error_exit("pid_number is wrong");
	handle_signal(pid, argv[2]);
	return (0);
}
