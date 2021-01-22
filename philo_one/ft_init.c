/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:43:35 by ejawe             #+#    #+#             */
/*   Updated: 2021/01/22 22:10:35 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_init_info(t_info *info, char **argv)
{
	info->nb_philo = ft_atoi_philo(argv[1]);
	info->die_time = ft_atoi_philo(argv[2]);
	info->eat_time = ft_atoi_philo(argv[3]);
	info->sleep_time = ft_atoi_philo(argv[4]);
	if (argv[5] != NULL)
		info->must_eat_time = ft_atoi_philo(argv[5]);
	else
		info->must_eat_time = 0;
	if (info->nb_philo == -1 || info->die_time == -1 ||
			info->eat_time == -1 || info->sleep_time == -1 ||
			info->must_eat_time == -1 || info->nb_philo == -1 ||
			info->nb_philo == 0 || info->nb_philo == 1)
		return (-1);
	return (0);
}

int		ft_malloc_mutex(t_info *info)
{
	if (!(info->eating = malloc(sizeof(pthread_mutex_t) * info->nb_philo)))
		return (1);
	ft_bzero(info->eating, sizeof(pthread_mutex_t) * info->nb_philo);
	if (!(info->lock_forks = malloc(sizeof(pthread_mutex_t) * info->nb_philo)))
		return (1);
	ft_bzero(info->lock_forks, sizeof(pthread_mutex_t) * info->nb_philo);
	return (0);
}

int		ft_ini_mutex(t_info *info)
{
	int i;

	if (pthread_mutex_init(&info->status, NULL) != 0)
		return (1);
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_mutex_init(&info->eating[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_mutex_init(&info->lock_forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int		ft_init_philo(t_philo *philo, t_info *info)
{
	int			i;
	pthread_t	thread;

	info->start = ft_gettime();
	info->is_dead = 0;
	i = 0;
	while (i < info->nb_philo)
	{
		philo[i] = (t_philo) { .index = i, .info = info, .must_eat_count = 0,
			.start_meal = ft_gettime()};
		if (pthread_create(&thread, NULL, &ft_routine, &philo[i]) != 0)
			return (1);
		pthread_detach(thread);
		if (pthread_create(&philo[i].thread, NULL, &ft_death, &philo[i]) != 0)
			return (1);
		usleep(1000);
		i++;
	}
	i = -1;
	while (++i < philo->info->nb_philo)
		pthread_join(philo[i].thread, NULL);
	free(philo);
	return (0);
}
