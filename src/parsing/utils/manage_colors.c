/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:21:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:52:13 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing/parsing.h"

/**
 * @brief Sets a specific color channel value in an integer color.
 *
 * @param color The original color value.
 * @param channel The channel to modify (RED, GREEN, BLUE, ALPHA).
 * @param value The new value for the channel (0-255).
 * @return The modified color value.
 */
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
	if (channel == RED_CH)
		result = (color & 0xFF00FFFF) | (value << 16);
	else if (channel == GREEN_CH)
		result = (color & 0xFFFF00FF) | (value << 8);
	else if (channel == BLUE_CH)
		result = (color & 0xFFFFFF00) | value;
	else if (channel == ALPHA_CH)
		result = (color & 0x00FFFFFF) | (value << 24);
	return (result);
}

/**
 * @brief Extracts a specific color channel value from an integer color.
 *
 * @param color The color value.
 * @param channel The channel to extract (RED, GREEN, BLUE, ALPHA).
 * @return The value of the channel (0-255).
 */
int	get_color_channel(int color, t_color_channel channel)
{
	int	result;

	result = 0;
	if (channel == RED_CH)
		result = (color >> 16) & 0xFF;
	else if (channel == GREEN_CH)
		result = (color >> 8) & 0xFF;
	else if (channel == BLUE_CH)
		result = color & 0xFF;
	else if (channel == ALPHA_CH)
		result = (color >> 24) & 0xFF;
	return (result);
}
