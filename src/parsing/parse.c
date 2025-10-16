/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:31:51 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 17:19:02 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief checks if the file in the path exists and has the wanted permissions.
 * 
 * Checks if the file pointed to by path_of_file, has read/write/execute
 * permissions. It will check the permissions that are not set to 0.
 * 
 * @return 1 on error, 0 on success.
 */
//int	check_file_existence(char *path_to_file, int read, int write, int execute)
//{
//	(void)path_to_file;
//	return (0);
//}

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
int	parse_input(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
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
	if (parse_input(argc, argv))
		return (1);
	//parse map
	//parse img files
	return (0);
}
