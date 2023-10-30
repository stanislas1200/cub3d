/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:20:26 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 10:28:15 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	stop_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		sleep(1);
		execlp("pkill", "pkill", "afplay", NULL);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	*embient_sound(void *nop)
{
	(void)nop;
	while (1)
		system("afplay -v 0.5 data/sound/test.wav ");
	return (NULL);
}

void	play_sound(char *sound, t_game *game)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", sound, NULL);
		exit(0);
	}
}
