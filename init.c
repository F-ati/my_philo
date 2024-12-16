/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:02 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/16 17:20:10 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void init_iput(t_data *data ,char **av ,int nb)
{
	int	i;
	
	i = 0;
	while(i < nb)
	{
		data[i].input.nb_of_philo = ft_atoi(av[1]);
		data[i].input.time_to_die = ft_atoi(av[2]);
		data[i].input.time_to_eat = ft_atoi(av[3]);
		data[i].input.time_to_sleep = ft_atoi(av[4]);
		data[i].input.nb_of_meals = -7;
		if(av[5] != NULL)
		{
			data[i].input.nb_of_meals = ft_atoi(av[5]);
		}
		i++;
	}
}

void init_chare_data(t_data *data ,int nb)
{	
	int i ;
	i = 0;
	while(i < nb)
	{
		data[i].error = data->p1;
		*data[i].error = -7;
		data[i].full = data->p2;
		*data[i].full = -7;
		data[i].is_die = data->p3;
		*data[i].is_die = -7;
		
		i++;
	}


}
void initialize_data( t_data *data,char *av[])
{
	
	int i = 0;
	int nb_of_philo = ft_atoi(av[1]);
	init_iput(data ,av , nb_of_philo);
	init_chare_data(data,nb_of_philo);
	while(i < nb_of_philo)
	{
		printf("%d\n",data[i].input.nb_of_meals);
		i++;
	}
	
}
