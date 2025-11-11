/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:21:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/30 18:32:38 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_color_channel(int color, t_color_channel channel, int value)
{
	int	result;

	result = color;
	if (value < 0 || value > 255)
	{
		log_msg(WARNING, __FILE__, __LINE__,
			"color channel value out of range (0-255)");
		return (color);
	}
	if (channel == RED_CHANNEL)
		result = (color & 0xFF00FFFF) | (value << 16);
	else if (channel == GREEN_CHANNEL)
		result = (color & 0xFFFF00FF) | (value << 8);
	else if (channel == BLUE_CHANNEL)
		result = (color & 0xFFFFFF00) | value;
	else if (channel == ALPHA_CHANNEL)
		result = (color & 0x00FFFFFF) | (value << 24);
	return (result);
}

int	get_color_channel(int color, t_color_channel channel)
{
	int	result;

	result = 0;
	if (channel == RED_CHANNEL)
		result = (color >> 16) & 0xFF;
	else if (channel == GREEN_CHANNEL)
		result = (color >> 8) & 0xFF;
	else if (channel == BLUE_CHANNEL)
		result = color & 0xFF;
	else if (channel == ALPHA_CHANNEL)
		result = (color >> 24) & 0xFF;
	return (result);
}