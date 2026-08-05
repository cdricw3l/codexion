/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:56:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/05 17:56:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	safe_print(t_coder coder, int action, pthread_mutex_t *lock)
{
	struct timespec	tm;
	clock_t			timestamp;

	if (coder.state == FALSE)
	{
		return ;
	}
	pthread_mutex_lock(lock);
	clock_gettime(CLOCK_MONOTONIC, &tm);
	timestamp = time_calculation(time_diff(coder.start, tm));
	if (action == TAKE)
	{
		printf(HCYN"%ld %d has taken a dongle"CRESET"\n", timestamp, coder.id);
		printf(HCYN"%ld %d has taken a dongle"CRESET"\n", timestamp, coder.id);
	}
	if (action == COMPILE)
	{
		printf(HCYN"%ld %d is compiling"CRESET"\n", timestamp, coder.id);
		coder.nb_of_compil++;
	}
	if (action == DEBBUG)
		printf(HCYN"%ld %d is debugging"CRESET"\n", timestamp, coder.id);
	if (action == REFACTO)
		printf(HCYN"%ld %d is refactoring"CRESET"\n", timestamp, coder.id);
	if (action == DEAD)
		printf(HCYN"%ld %d burned out"CRESET"\n", timestamp, coder.id);
	pthread_mutex_unlock(lock);
}

void	display_coders(t_coder *coders, int nb_coder)
{
	int	i;

	i = 0;
	printf("\n"HGRN"[ DISPLAY CODERS INFORMATIONS ]"CRESET"\n\n");
	while (i < nb_coder)
	{
		printf("Coder: %d\n", coders->id);
		printf("last compilation : %p\n", coders->last_compilation);
		printf("UsbLeft:%p last use %ld\n", coders->coder_mutex.dongle_l.dongle,
			coders->coder_mutex.dongle_l.last_use);
		printf("UsbRight:%p last use %ld\n", coders->coder_mutex.dongle_r.dongle,
			coders->coder_mutex.dongle_r.last_use);
		printf("display mutex %p\n", coders->coder_mutex.display_f);
		printf("timestamp_f mutex %p\n", coders->coder_mutex.timestamp_f);
		printf("cond %p\n", &coders->queue->cond);
		printf("number of request %d\n", coders->queue->request_counter);
		printf("\n");
		i++;
	}
}

void	display_params(int params[8])
{
	printf(BHGRN"Program settings:\n");
	printf(HBLU"[Number of philosopher]:"HYEL" %d\n", params[nbc]);
	printf(HBLU"[Time to burnout]:"HYEL" %d ms\n", params[time_to_burnout]);
	printf(HBLU"[Time to compile]:"HYEL" %d ms\n", params[time_to_compile]);
	printf(HBLU"[Time to debug]:"HYEL" %d ms\n", params[time_to_debug]);
	printf(HBLU"[Time to refactor]:"HYEL" %d ms\n", params[time_to_refactor]);
	printf(HBLU"[Number of compiles required]:"HYEL" %d\n",
		params[number_of_compiles_required]);
	printf(HBLU"[Dongle cooldown]:"HYEL" %d ms\n", params[dongle_cooldown]);
	printf(HBLU"[scheduler]: "HYEL);
	if (params[scheduler] == FIFO)
		printf("fifo"CRESET"\n");
	else if (params[scheduler] == EDF)
		printf("edf"CRESET"\n");
}

void	display_mutex_data(int nb_coder, t_global_mutex global_mu)
{
	int	i;

	printf("display fonction mutex: %p\n", &global_mu.display_f);
	printf("timestamp fonction mutex: %p\n", &global_mu.timestamp_f);
	i = 0;
	while (i < nb_coder)
	{
		printf("Dongle [%d] %p\n", i, &global_mu.dongles[i]);
		i++;
	}
}

void	display_request(t_request request)
{
	printf("\nRequest Id: %d\n", request.request_id);
	printf("Coder Id: %d\n", request.coder_id);
	printf("Cond adresse %p\n", request.cond);
	printf("Children left: %p\n", request.left);
	printf("Children right: %p\n", request.right);
}
