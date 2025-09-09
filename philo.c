/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:30:16 by rduport           #+#    #+#             */
/*   Updated: 2025/04/12 13:22:59 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

void	ft_free_philo_forks(t_info *info)
{
	if (info->philo)
		free(info->philo);
	if (info->forks)
		free(info->forks);
}

int	ft_innit_info(t_info *info, char **argv, int argc)
{
	info->philo_nbr = ft_atoi(argv[1], NULL);
	info->time_to_die = ft_atoi(argv[2], NULL) * 1000;
	info->time_to_eat = ft_atoi(argv[3], NULL) * 1000;
	info->time_to_sleep = ft_atoi(argv[4], NULL) * 1000;
	if (argc == 6)
		info->max_meal = ft_atoi(argv[5], NULL);
	else
		info->max_meal = -1;
	info->start_simulation = 0;
	info->end_simulation = 0;
	info->is_dead = 0;
	info->forks = malloc(sizeof(t_fork) * info->philo_nbr);
	info->philo = malloc(sizeof(t_philo) * info->philo_nbr);
	if (!info->philo || !info->forks)
		return (ft_free_philo_forks(info), -1);
	ft_innit_philo(info);
	return (1);
}

void	ft_innit_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_nbr)
	{
		info->forks[i].used = 0;
		info->philo[i].id = i;
		info->philo[i].nb_meal = 0;
		info->philo[i].last_meal_time = 0;
		info->philo[i].info = info;
		i++;
	}
}

int	too_long(const char *string, int index)
{
	int	i;

	i = 0;
	while (string[index + i])
		i++;
	if (i > 13)
		return (1);
	return (0);
}
