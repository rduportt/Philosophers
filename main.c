/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:58:42 by rduport           #+#    #+#             */
/*   Updated: 2025/09/02 16:58:43 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_innit(t_info *info, int argc, char **argv)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (argv[++i] != NULL)
		if (ft_atoi(argv[i], &flag) <= 0)
			return (printf("Erreur de syntaxe\n"), 0);
	if (ft_innit_info(info, argv, argc) == -1)
		return (-1);
	i = -1;
	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
	{
		printf("pb innit mutex write\n");
		return (-1);
	}
	if (pthread_mutex_init(&info->death_lock, NULL) != 0)
	{
		printf("pb innit mutex death\n");
		return (-1);
	}
	while (++i < info->philo_nbr)
		pthread_mutex_init(&info->forks[i].locked, NULL);
	return (1);
}

void	destroy_all(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_nbr)
		pthread_mutex_destroy(&info->forks[i].locked);
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->death_lock);
	free(info->philo);
	free(info->forks);
}

int	main(int argc, char **argv)
{
	int				i;
	struct timeval	begin;
	t_info			info;
	pthread_t		observer;

	if (argc == 5 || argc == 6)
	{
		if (main_innit(&info, argc, argv) != 1)
			return (-1);
		gettimeofday(&begin, NULL);
		info.start_simulation = begin.tv_sec * 1000000 + begin.tv_usec;
		i = -1;
		while (++i < info.philo_nbr)
			pthread_create(&info.philo[i].thread, NULL, dinner, &info.philo[i]);
		pthread_create(&observer, NULL, ft_observer, &info);
		i = -1;
		while (++i < info.philo_nbr)
			pthread_join(info.philo[i].thread, NULL);
		pthread_join(observer, NULL);
		destroy_all(&info);
	}
	else
		printf("./Philo NbPhilo TimeToDie TimeToEat TimeToSleep NbofMeal\n");
	return (0);
}
