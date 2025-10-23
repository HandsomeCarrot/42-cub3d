/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:31:32 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/23 13:34:48 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "libft.h"
# include "structs.h"
# include "logging.h"
# include <mlx.h>

//-----main-cleanup.c-----//

void	main_cleanup(t_data *data);

//-----string-cleanup.c-----//

void	free_string_array(char ***string_array, char *src_file, int src_line);

#endif /* CLEANUP_H */
