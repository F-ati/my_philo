/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:40:39 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/16 17:33:54 by fel-aziz         ###   ########.fr       */
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
	initialize_mutex(data ,forks);
}