/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:48:15 by ajehle            #+#    #+#             */
/*   Updated: 2024/02/16 09:36:59 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_acknowledge(int sig_nbr, siginfo_t *info, void *cont)
{
	(void)cont;
	if (sig_nbr == SIGUSR2)
		ft_printf("MESSAGE ACKNOWLEDGED FROM %i", info->si_pid);
}

static int	instructions(void)
{
	write (1, "./client [PID_DESTINATION] [MESSAGE]", 36);
	return (1);
}

static void	send_to_process(int pid, char c)
{
	int	i;

	i = 8;
	while (i)
	{
		i--;
		if (((c >> i) & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
	return ;
}

static void	slice_to_chars(int pid, char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		send_to_process(pid, arr[i]);
		i++;
		usleep(100);
	}
	send_to_process(pid, '\0');
	return ;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa_signal;

	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_sigaction = ft_acknowledge;
	sa_signal.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa_signal, NULL);
	if (argc != 3)
		return (instructions());
	slice_to_chars((ft_atoi(argv[1])), argv[2]);
	return (0);
}
