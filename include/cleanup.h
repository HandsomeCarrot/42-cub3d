/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:31:32 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 13:12:02 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "definitions.h"
# include "libft.h"
# include "logging.h"
# include <mlx.h>

//-----cleanup_main.c-----//

void	main_cleanup(t_data *data);

//-----cleanup_strings.c-----//

void	free_string_array(char ***string_array);

#endif /* CLEANUP_H */
