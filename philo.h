/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:59:15 by rduport           #+#    #+#             */
/*   Updated: 2025/09/02 16:59:16 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

typedef struct s_info
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meal;
	long			start_simulation;
	int				end_simulation;
	int				is_dead;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
	t_fork			*forks;
}	t_info;

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	locked;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			nb_meal;
	int			last_meal_time;
	t_fork		*r_fork;
	t_fork		*l_fork;
	t_info		*info;
}	t_philo;

int			too_long(const char *string, int index);
void		ft_innit_philo(t_info *info);
int			ft_innit_info(t_info *info, char **argv, int argc);
void		ft_free_philo_forks(t_info *info);
size_t		ft_strlen(const char *string);
void		log_status(t_philo *philo, const char *msg);
int			start_of_simulation(t_philo *philo);
int			check_death(t_philo *philo, long current_time);
long		get_current_time(t_info *info);
long long	ft_atoi(const char *string, int *flag);
void		lock_forks(t_philo *philo, int first_fork, int second_fork);
void		unlock_forks(t_philo *philo, int first_fork, int second_fork);
void		ft_eat(t_philo *philo, int first_fork, int second_fork);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
int			solo_philo(t_philo *philo);
int			all_philo_enough(t_philo *philo);
int			ft_enough(t_philo *philo);
void		ft_routine(t_philo *philo, int first_fork, int second_fork);
void		*dinner(void *arg);
void		obs_check_death(t_info *info, long current_time);
void		ft_observer_routine(t_info *info, long current_time);
void		*ft_observer(void *arg);
int			main_innit(t_info *info, int argc, char **argv);
void		destroy_all(t_info *info);

#endif
