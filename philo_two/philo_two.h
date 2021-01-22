/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:30:14 by ejawe             #+#    #+#             */
/*   Updated: 2021/01/23 00:08:47 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>

# define SEM_FORK_NAME "/fork"
# define SEM_STATUS_NAME "/status"
# define SEM_EAT_NAME "/eat"

typedef struct		s_info
{
	int				nb_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_time;
	sem_t			*sem_fork;
	sem_t			*sem_status;
	sem_t			*sem_eat;
	int				is_dead;
	int				start;
}					t_info;

typedef struct		s_philo
{
	int				index;
	int				start_meal;
	int				must_eat_count;
	t_info			*info;
	pthread_t		thread;
}					t_philo;

int					ft_isdigit(int c);
int					ft_atoi_philo(const char *nptr);
int					ft_init_info(t_info *info, char **argv);
int					ft_init_philo(t_philo *philo, t_info *info);
int					ft_ini_semaphores(t_info *info);
void				ft_destroy_semaphores(t_info *info);
void				*ft_routine(void *rphilo);
int					ft_gettime(void);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putnbr(unsigned long n);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t len);
size_t				ft_strlen(const char *s);
void				*ft_death(void *rphilo);
int					ft_error(t_info *info, char *error_msg);

#endif
