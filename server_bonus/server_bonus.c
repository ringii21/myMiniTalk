/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:23:26 by abonard           #+#    #+#             */
/*   Updated: 2022/02/08 20:23:24 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <signal.h>

struct	s_lanorme
{
	int		g_pid;
	int		send;
}		g_lanorme;

void	ft_reception(void)
{
	if(kill(g_lanorme.g_pid, SIGUSR1) == -1)
	{
		ft_printf("OOPSIE\n");
		exit(1);
	}
	g_lanorme.send = 0;
}

void	ft_convertbitz(int base, char *buff)
{
	static char	c; // reconstituer le caractere
	static	int	bite; // nombre de bit
	static int	i = 0; // index de buffer

	if( i == 9)
	{
		ft_printf("%s", buff);
		ft_bzero(buff, '\0');
		i = 0;
		c = '\0';
		bite = 0;
	}
	c = c + (base << bite++);
	if (bite == 8)
	{
		buff[i] = c;
		if (c == '\0')
		{
			ft_printf("%s", buff);
			i = -1;
			ft_bzero(buff, '\0');
			g_lanorme.send = 1;
		}
		bite = 0;
		c = '\0';
		i++;
	}
}

void	ft_check(int signal)
{
	char buff[10];

	ft_bzero(buff, '\0');
	if (signal == SIGUSR1)
		ft_convertbitz(1, buff);
	else if (signal == SIGUSR2)
		ft_convertbitz(0, buff);

}

void	ft_sigavailable(void)
{
	if (signal(SIGUSR1, ft_check) == SIG_ERR || signal(SIGUSR2, ft_check) == SIG_ERR)
		exit(1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_printf("%s OH NO NO NOOO\n%s", RED, NC);
		exit(1);
	}
	g_lanorme.send = 0;
	ft_sigavailable();
	g_lanorme.g_pid = getpid();
	ft_printf("%sHello ! hold on...\n%sThis is you PID %s%d%s Bitches\n", CYAN, NC, YELLOW, g_lanorme.g_pid, NC);
	usleep(1000);
	int j;

	j = 0;
	while (1)
	{
		if (g_lanorme.send == 1)
			ft_reception();
	}
	return (0);
}
