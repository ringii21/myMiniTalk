/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:22:54 by abonard           #+#    #+#             */
/*   Updated: 2022/02/08 20:20:07 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <signal.h>

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
	int	fuckleswarnings;

	fuckleswarnings = signal;
	signal = fuckleswarnings;
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
	return (0);
}
