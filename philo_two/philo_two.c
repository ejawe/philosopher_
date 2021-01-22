/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:58:43 by ejawe             #+#    #+#             */
/*   Updated: 2021/01/22 23:58:45 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	memset(&info, 0, sizeof(t_info));
	if (argc < 5 || argc > 6)
		return (ft_error(&info, "Error: 4 or 5 paramaters are required.\n"));
	if (ft_init_info(&info, argv) == -1)
		return (ft_error(&info, "Error: Paramaters are incorrect.\n"));
	if (ft_ini_semaphores(&info) == 1)
		return (ft_error(&info, "Error: sem_open failed\n"));
	if (!(philo = ft_calloc(sizeof(t_philo) * info.nb_philo)))
		return (ft_error(&info, "Allocation problem\n"));
	if (ft_init_philo(philo, &info) == 1)
		return (-1);
	ft_destroy_semaphores(&info);
	return (0);
}
