/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:48:04 by ajehle            #+#    #+#             */
/*   Updated: 2024/05/08 12:34:46 by ajehle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_str(siginfo_t *info, char *str)
{
	kill(info->si_pid, SIGUSR2);
	usleep(50);
	ft_printf("%s", str);
}

static char	*charjoin(char *str, char c)
{
	char	*temp;
	int		len;

	len = ft_strlen(str);
	temp = malloc((len + 2) * sizeof(char));
	ft_strlcpy(temp, str, len + 1);
	temp[len] = c;
	temp[len + 1] = '\0';
	if (str)
		free(str);
	return (temp);
}

static void	ft_handler(int sig_nbr, siginfo_t *info, void *cont)
{
	static int				bit = 0;
	static unsigned char	ch = 0;
	static char				*str;

	if (!str)
		str = ft_strdup("");
	(void)cont;
	ch = ch << 1;
	if (sig_nbr == SIGUSR2)
		ch = ch | 1;
	bit++;
	if (bit == 8)
	{
		str = charjoin(str, ch);
		if (ch == '\0')
		{
			print_str(info, str);
			free(str);
			exit(0);
		}
		bit = 0;
		ch = 0;
	}
	return ;
}

void	test()
{
	system("leaks server");
}

int	main(void)
{
	atexit(test);
	struct sigaction	sa_signal;

	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_sigaction = ft_handler;
	sa_signal.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	ft_printf("SERVER PID %i\n", getpid());
	while (1)
		sleep(1);
	return (0);
}
