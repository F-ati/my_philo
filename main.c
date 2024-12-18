/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:40:39 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/18 15:59:39 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_error(int  ac , char **av)
{
	int i ;

	i = 1;
	if(ac != 5 && ac != 6)
	{
		printf("error en the nb of args \n");
		return(-7);
	}
	while(av[i] != NULL)
	{

		if(check_is_number(av[i]) == 0 || ft_atoi(av[i]) == -7)
		{
			printf("error in the value of args\n");
			return(-7);
		}
		i++;
	}
	
	return(0);
}


int main(int ac , char *av[])
{
	pthread_t *philo;
	t_data *data;
	pthread_mutex_t *forks;
	
	if(check_error(ac , av) != 0)
		return(1);
	if (allocate_data(&data ,&philo, &forks , ft_atoi(av[1])) != 0)
	{
		printf("error in malloc \n");
		return(1);
	}
	initialize_data(data,av);
	if (initialize_mutex(data ,forks) != 0)
	{
		printf("error in init the mutex \n");
		// distroy;
		// free;
	}
	init_threads_with_forks(data,philo,forks);
	wait_for_all_threads(data , philo);
	// while(1)
	// {
	// 	pthread_mutex_lock(&data->chared_mutex);
	// 	if(*data->is_die == 1)
	// 	{
	// 		printf("%d %s\n",*data->error,"is die");
	// 		pthread_mutex_unlock(&data->chared_mutex);
	// 		break;
	// 	}
	// 	pthread_mutex_unlock(&data->chared_mutex);
	// }
}