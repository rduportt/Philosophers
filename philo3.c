/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:58:57 by rduport           #+#    #+#             */
/*   Updated: 2025/09/02 16:58:58 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	solo_philo(t_philo *philo)
{
	if (philo->info->philo_nbr == 1)
	{
		pthread_mutex_lock(&philo->info->death_lock);
		philo->last_meal_time = get_current_time(philo->info);
		philo->nb_meal++;
		pthread_mutex_unlock(&philo->info->death_lock);
		return (1);
	}
	return (0);
}

int	all_philo_enough(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->philo_nbr)
	{
		if (philo[i].nb_meal < philo->info->max_meal)
			return (0);
		i++;
	}
	return (1);
}

int	ft_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_lock);
	if (philo->info->is_dead || (philo->info->max_meal != -1
			&& all_philo_enough(philo) == 1))
	{
		philo->info->is_dead = 1;
		pthread_mutex_unlock(&philo->info->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->death_lock);
	return (0);
}

void	ft_routine(t_philo *philo, int first_fork, int second_fork)
{
	while (1)
	{
		pthread_mutex_lock(&philo->info->death_lock);
		if (philo->info->is_dead || (philo->info->max_meal != -1
				&& all_philo_enough(philo)))
		{
			pthread_mutex_unlock(&philo->info->death_lock);
			break ;
		}	
		pthread_mutex_unlock(&philo->info->death_lock);
		if (philo->id % 2 == 0)
			usleep(500);
		ft_eat(philo, first_fork, second_fork);
		ft_sleep(philo);
		ft_think(philo);
	}
}

void	*dinner(void *arg)
{
	t_philo			*philo;
	int				first_fork;
	int				second_fork;

	philo = (struct s_philo *) arg;
	if (solo_philo(philo) == 1)
		pthread_exit(NULL);
	first_fork = philo->id;
	second_fork = (philo->id + 1) % philo->info->philo_nbr;
	pthread_mutex_lock(&philo->info->death_lock);
	philo->last_meal_time = get_current_time(philo->info);
	pthread_mutex_unlock(&philo->info->death_lock);
	ft_routine(philo, first_fork, second_fork);
	pthread_exit(NULL);
}
