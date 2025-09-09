/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:59:03 by rduport           #+#    #+#             */
/*   Updated: 2025/09/02 16:59:04 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	obs_check_death(t_info *info, long current_time)
{
	int	i;

	i = 0;
	current_time = get_current_time(info);
	while (i < info->philo_nbr)
	{
		pthread_mutex_lock(&info->death_lock);
		if (current_time - info->philo[i].last_meal_time
			> info->time_to_die && info->philo[i].nb_meal > 0)
		{
			info->is_dead = 1;
			current_time = get_current_time(info);
			pthread_mutex_lock(&info->write_lock);
			printf("%ld %d died\n", current_time / 1000, i);
			pthread_mutex_unlock(&info->death_lock);
			pthread_mutex_unlock(&info->write_lock);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&info->death_lock);
		i++;
	}
}

void	ft_observer_routine(t_info *info, long current_time)
{
	int	i;
	int	all_ate;

	while (1)
	{
		obs_check_death(info, current_time);
		all_ate = 1;
		i = 0;
		while (i < info->philo_nbr)
		{
			pthread_mutex_lock(&info->death_lock);
			if (info->max_meal != -1 && info->philo[i].nb_meal < info->max_meal)
				all_ate = 0;
			pthread_mutex_unlock(&info->death_lock);
			i++;
		}
		pthread_mutex_lock(&info->death_lock);
		if (info->max_meal != -1 && all_ate == 1)
		{
			info->is_dead = 1;
			pthread_mutex_unlock(&info->death_lock);
			break ;
		}
		pthread_mutex_unlock(&info->death_lock);
	}
}

void	*ft_observer(void *arg)
{
	t_info			*info;
	long			current_time;
	int				all_ate;

	info = (t_info *) arg;
	all_ate = 0;
	current_time = 0;
	ft_observer_routine(info, current_time);
	pthread_exit(NULL);
}
