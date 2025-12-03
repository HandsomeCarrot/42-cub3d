/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:31:32 by vpoka             #+#    #+#             */
/*   Updated: 2025/12/02 15:23:46 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "logging.h"
# include "../../libft/libft.h"
# include "../parsing/parsing_types.h"

//-----cleanup_main.c-----//

void	main_cleanup(t_map_data *data);
void	free_image_paths(t_map_data *data);

//-----cleanup_strings.c-----//

void	free_string_array(char ***string_array);

#endif /* CLEANUP_H */
