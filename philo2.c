/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:58:52 by rduport           #+#    #+#             */
/*   Updated: 2025/09/02 16:58:53 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo, int first_fork, int second_fork)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->info->forks[first_fork].locked);
		pthread_mutex_lock(&philo->info->forks[second_fork].locked);
	}
	else
	{
		pthread_mutex_lock(&philo->info->forks[second_fork].locked);
		pthread_mutex_lock(&philo->info->forks[first_fork].locked);
	}
	log_status(philo, "has taken a fork");
	log_status(philo, "has taken a fork");
}

void	unlock_forks(t_philo *philo, int first_fork, int second_fork)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->info->forks[second_fork].locked);
		pthread_mutex_unlock(&philo->info->forks[first_fork].locked);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->forks[first_fork].locked);
		pthread_mutex_unlock(&philo->info->forks[second_fork].locked);
	}
}

void	ft_eat(t_philo *philo, int first_fork, int second_fork)
{
	lock_forks(philo, first_fork, second_fork);
	log_status(philo, "is eating");
	pthread_mutex_lock(&philo->info->death_lock);
	philo->last_meal_time = get_current_time(philo->info);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->info->death_lock);
	usleep(philo->info->time_to_eat);
	unlock_forks(philo, first_fork, second_fork);
}

void	ft_sleep(t_philo *philo)
{
	log_status(philo, "is sleeping");
	usleep(philo->info->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	log_status(philo, "is thinking");
}
