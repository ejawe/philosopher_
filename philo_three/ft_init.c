/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:34:59 by ejawe             #+#    #+#             */
/*   Updated: 2021/01/22 18:35:07 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int		ft_ini_semaphores(t_info *info)
{
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_STATUS_NAME);
	sem_unlink(SEM_EAT_NAME);
	sem_unlink(SEM_MUST_EAT_NAME);
	info->sem_fork = sem_open(SEM_FORK_NAME, O_CREAT, 0644,
			(unsigned int)info->nb_philo / 2);
	if (info->sem_fork == SEM_FAILED)
		return (1);
	info->sem_status = sem_open(SEM_STATUS_NAME, O_CREAT, 0644, 1);
	if (info->sem_status == SEM_FAILED)
		return (1);
	info->sem_eat = sem_open(SEM_EAT_NAME, O_CREAT, 0644, 1);
	if (info->sem_eat == SEM_FAILED)
		return (1);
	info->sem_must_eat = sem_open(SEM_MUST_EAT_NAME, O_CREAT, 0644, 0);
	if (info->sem_must_eat == SEM_FAILED)
		return (1);
	return (0);
}

void	*ft_must_eat(void *rphilo)
{
	t_philo *philo;
	int		i;

	philo = (t_philo*)rphilo;
	i = 0;
	while (i < philo->info->nb_philo)
	{
		sem_wait(philo->info->sem_must_eat);
		i++;
	}
	sem_wait(philo->info->sem_status);
	write(1, "Done", 4);
	kill(0, SIGINT);
	return (NULL);
}

void	check_philo(t_philo *philo)
{
	pthread_t thread_must_eat;

	if (philo->info->must_eat_time > 0)
	{
		pthread_create(&thread_must_eat, NULL, ft_must_eat, philo);
		pthread_join(thread_must_eat, NULL);
	}
}

int		ft_init_philo(t_philo *philo, t_info *info)
{
	int		i;
	pid_t	pid;

	info->start = ft_gettime();
	info->is_dead = 0;
	i = 0;
	while (i < info->nb_philo)
	{
		philo[i] = (t_philo) { .index = i, .info = info, .must_eat_count = 0,
			.start_meal = ft_gettime()};
		if (!(pid = fork()))
		{
			if (ft_routine(&philo[i]))
				return (1);
		}
		else if (pid < 0)
			return (1);
		usleep(100);
		i++;
	}
	if (pid > 0)
		check_philo(philo);
	waitpid(-1, NULL, 0);
	free(philo);
	return (0);
}
