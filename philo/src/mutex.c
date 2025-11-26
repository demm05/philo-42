/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:09:58 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/17 16:10:01 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	mutex_get_bool(bool *var, t_mutex *mutex)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *var;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	mutex_set_bool(bool *var, bool value, t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

int	mutex_get_int(int *var, t_mutex *mutex)
{
	int	res;

	pthread_mutex_lock(mutex);
	res = *var;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	mutex_set_int(int *var, int value, t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}
