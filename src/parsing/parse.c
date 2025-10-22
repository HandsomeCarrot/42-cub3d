/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:31:51 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 12:49:47 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Parses the input of the user
 * 
 * It will scan the input if it only has the map file as input.
 * 
 * @param argc the amount of strings in argv
 * @param argv all the input given by user (strings)
 * 
 * @return 1 on error, 0 on success
 */
static int	parse_input(int argc, char **argv)
{
	log_msg(INFO, __FILE__, __LINE__, "validating user input");
	if (argc != 2 || !argv || !argv[0] || !argv[1])
	{
		log_msg(ERROR, __FILE__, __LINE__, "invalid input");
		return (1);
	}
	return (0);
}

/**
 * @brief Main entrypoint into the parsing of input and map data.
 * 
 * First it will look if the user input provided a valid map file
 * and no other input. Then it will parse the data in the map file.
 *
 * Image files, colors, map, ...
 * 
 * @param argc the amount of strings in argv
 * @param argv all the input given by user (strings)
 * 
 * @return 1 on error, 0 on success.
 */
int	parse(int argc, char **argv, t_data *data)
{
	log_msg(INFO, __FILE__, __LINE__, "starting parsing of data");
	if (parse_input(argc, argv))
		return (1);
	(void)data;
	//parse map
	//parse img files
	return (0);
}
