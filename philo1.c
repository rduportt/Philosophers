/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:58:47 by rduport           #+#    #+#             */
/*   Updated: 2025/09/02 16:58:48 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *string, int *flag)
{
	int			i;
	int			signe;
	long long	result;
	int			j;

	j = 0;
	result = 0;
	signe = 1;
	i = 0;
	while ((string[i] >= 9 && string[i] <= 13) || string[i] == 32)
		i++;
	if (string[i] == '-')
	{
		signe = -1;
		i++;
	}
	if (string[i] == '+' && signe != -1)
		i++;
	if (too_long(string, i) == 1)
		return (*flag = 1, 0);
	while (string[i] >= '0' && string[i] <= '9')
		result = result * 10 + string[i++] - '0';
	if (result == 0)
		return (0);
	return (result * signe);
}

long	get_current_time(t_info *info)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = ((time.tv_sec * 1000000 + time.tv_usec)
			- info->start_simulation);
	return (current_time);
}

int	check_death(t_philo *philo, long current_time)
{
	pthread_mutex_lock(&philo->info->death_lock);
	current_time = get_current_time(philo->info);
	if (current_time - philo->last_meal_time > philo->info->time_to_die)
	{
		if (!philo->info->is_dead)
		{
			philo->info->is_dead = 1;
			pthread_mutex_unlock(&philo->info->death_lock);
			log_status(philo, "died");
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->info->death_lock);
	return (0);
}

int	start_of_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->info->write_lock);
	while (i < philo->info->philo_nbr)
	{
		if (philo[i].nb_meal != 0)
		{
			pthread_mutex_unlock(&philo->info->write_lock);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->info->write_lock);
	return (0);
}

void	log_status(t_philo *philo, const char *msg)
{
	long			ts;

	pthread_mutex_lock(&philo->info->death_lock);
	pthread_mutex_lock(&philo->info->write_lock);
	if (!philo->info->is_dead)
	{
		pthread_mutex_unlock(&philo->info->death_lock);
		ts = get_current_time(philo->info);
		printf("%ld %d %s\n", ts / 1000, philo->id, msg);
		pthread_mutex_unlock(&philo->info->write_lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->death_lock);
		pthread_mutex_unlock(&philo->info->write_lock);
	}
}
