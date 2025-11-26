/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:09:48 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/17 16:09:50 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(t_table));
	if (!parse_argv(argc, argv, &table.info))
		return (1);
	table.info.simulation = 1;
	if (!init_mutexes(&table))
		return (2);
	if (!init_philos(&table, table.forks, table.info.philosophers))
		return (3);
	if (!launch(&table))
	{
		mutex_set_bool(&table.info.is_ready, 1, &table.ready);
		mutex_set_bool(&table.info.simulation, 0, &table.simulation);
		usleep(100);
	}
	cleanup(&table, NULL);
	return (0);
}
