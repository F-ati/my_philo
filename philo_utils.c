/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:19:09 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/17 11:20:35 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	check_is_number(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+') && str[i + 1] != '\0')
	{
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}
	if (i == ft_strlen(str))
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	r;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	r = result * sign;
	if (r < -2147483648 || r > 2147483647)
		return (-7);
	return ((int)(r));
}

int allocate_chared_data(t_data *data)
{
	data->p1 = malloc(sizeof(int));
	if(data->p1 == NULL)
		return(-7);
	data->p2 = malloc(sizeof(int));
	if(data->p2 == NULL)
	{
		free(data->p1);
		return(-7);
	}
	data->p3 = malloc(sizeof(int));
	if(data->p3 == NULL)
	{
		free(data->p1);
		free(data->p2);
		return(-7);
	}
	return(0);
}

int	allocate_data(t_data **data,pthread_t **philo, pthread_mutex_t **forks,
		int nb_of_philo)
{
	*data = malloc(sizeof(t_data) * nb_of_philo);
	if (*data == NULL)
		return (-7);
	*philo = malloc(sizeof(pthread_t) * nb_of_philo);
	if (philo == NULL)
	{
		free(*data);
		return (-7);
	}
	*forks = malloc(sizeof(pthread_mutex_t) * nb_of_philo);
	if (*forks == NULL)
	{
		free(*data);
		free(*philo);
		return (-7);
	}
	if(allocate_chared_data(*data) == -7)
	{
		free(*data);
		free(*philo);
		free(*forks);
		return(-7);
	}

	return (0);
}