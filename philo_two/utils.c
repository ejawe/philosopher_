/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:30:32 by ejawe             #+#    #+#             */
/*   Updated: 2021/01/22 23:30:33 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_atoi_philo(const char *nptr)
{
	long	resultat;

	resultat = 0;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			return (-1);
		nptr++;
	}
	while (*nptr)
	{
		if (ft_isdigit(*nptr) == 0)
			return (-1);
		resultat *= 10;
		resultat += (long)*nptr - 48;
		nptr++;
	}
	return (int)(resultat);
}

int		ft_gettime(void)
{
	struct timeval	tp;
	int				ms;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000;
	ms += tp.tv_usec / 1000;
	return (ms);
}

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

void	*ft_calloc(size_t len)
{
	void	*ret;

	if (!(ret = malloc(len)))
		return (NULL);
	ft_bzero(ret, len);
	return (ret);
}
