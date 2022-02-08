/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:22:54 by abonard           #+#    #+#             */
/*   Updated: 2022/02/08 20:26:19 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <signal.h>

int		g_ciao = 0;

void	ft_sendmessage(char c, int pid)
{
	int		i;
	char	b;

	i = 0;
	b = '\0';
	while(i < 8)
	{
		if (((c >> b) & 1) == 1)
		{
			if(kill(pid, SIGUSR1) == -1)
			{
				ft_printf("OOPS\n");
				exit(1);
			}
		}
		else
		{
			if(kill(pid, SIGUSR2) == -1)
			{
				ft_printf("OOPS\n");
				exit(1);
			}
		}
		i++;
		b++;
		usleep(400);
	}
}

int	ft_gimmepid(char *str)
{
	long long int	pid;

	pid = ft_atoi(str);
	ft_printf("PID %d\n", pid);
	if(pid <= 0 || pid >= 2147483647)
	{
		ft_printf("OMG, IT IS TOO SMALL OR TO BIG ENOUGH FOR ME\n");
		exit(1);
	}
	return (pid);
}

void	ft_check(int signal)
{
	if (signal == SIGUSR1)
		;
	ft_printf("%sThe message has been recieved by the server\n%s", GREEN, NC);
	g_ciao = 1;
}

void	ft_sigavailable(void)
{
	if (signal(SIGUSR1, ft_check) == SIG_ERR
			|| signal(SIGUSR2, ft_check) == SIG_ERR)
		exit(1);
}

int main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		ft_printf("ERROR: WRONG NUMBER ARGUMENTS\n");
		return (1);
	}
	ft_sigavailable();//verifier les signaux sont dispo
	pid = ft_gimmepid(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		ft_sendmessage(argv[2][i], pid);
		i++;
	}
	ft_sendmessage(argv[2][i], pid);
	ft_printf("%s%s%s", GREEN, MSG, NC);
	signal(SIGUSR1, ft_check);
	return (0);
}
