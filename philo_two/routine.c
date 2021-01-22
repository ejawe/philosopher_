/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:25:58 by ejawe             #+#    #+#             */
/*   Updated: 2021/01/22 23:54:55 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_print_status(t_philo *philo, char *status)
{
	sem_wait(philo->info->sem_status);
	if (!philo->info->is_dead && !(philo->info->must_eat_time > 0 &&
				philo->must_eat_count >= philo->info->must_eat_time))
	{
		ft_putnbr((ft_gettime() - philo->info->start));
		write(1, " ", 1);
		ft_putnbr(philo->index + 1);
		write(1, " ", 1);
		write(1, status, ft_strlen(status));
		write(1, "\n", 1);
	}
	sem_post(philo->info->sem_status);
}

void	*ft_death(void *rphilo)
{
	t_philo *philo;

	philo = rphilo;
	while (!philo->info->is_dead)
	{
		sem_wait(philo->info->sem_eat);
		if (!philo->info->is_dead &&
				(ft_gettime() - philo->start_meal) > philo->info->die_time)
		{
			if (philo->info->must_eat_time > 0 &&
					philo->must_eat_count >= philo->info->must_eat_time)
			{
				sem_post(philo->info->sem_eat);
				return (NULL);
			}
			ft_print_status(philo, "died");
			philo->info->is_dead = 1;
			sem_post(philo->info->sem_eat);
			return (NULL);
		}
		usleep(100);
		sem_post(philo->info->sem_eat);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->info->sem_fork);
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	philo->start_meal = ft_gettime();
	usleep(philo->info->eat_time * 1000);
	philo->must_eat_count = philo->must_eat_count + 1;
	sem_post(philo->info->sem_fork);
}

void	*ft_routine(void *rphilo)
{
	t_philo *philo;

	philo = rphilo;
	philo->start_meal = ft_gettime();
	while (!philo->info->is_dead)
	{
		ft_eat(philo);
		if (philo->info->is_dead || (philo->info->must_eat_time > 0 &&
					philo->must_eat_count >= philo->info->must_eat_time))
			return (NULL);
		if (!philo->info->is_dead)
			ft_print_status(philo, "is sleeping");
		usleep(philo->info->sleep_time * 1000);
		if (!philo->info->is_dead)
			ft_print_status(philo, "is thinking");
	}
	return (NULL);
}
