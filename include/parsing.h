/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:52:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/14 17:44:29 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cleanup.h"
# include "definitions.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <string.h>

//-----parse.c-----//

int			parse(int argc, char **argv, t_data *data);

//-----map_file_reader.c-----//

int			parse_map_file(char *file, t_data *data);

//-----map_validator.c-----//

int			parse_map_layout(t_data *data);

//-----texture_identifiers.c-----//

t_map_id	*get_map_data_type(char *line, int row, t_map_id *ids);
bool		all_ids_found(t_map_id *ids);
t_map_id	*get_map_identifiers(void);

//-----texture_parser.c-----//

int			save_image(char *line, int row, t_map_id *data_id, t_data *data);

//-----color_parser.c-----//

int			save_color(char *line, t_map_id *data_id, t_colors *colors);

//-----content_validation.c-----//

bool		validate_trailing_content(char *line, int row);
int			check_hanging_lines(char **lines, size_t row);

//-----map_validation.c-----//

bool		has_valid_neighbors(int x, int y, t_map_data *data);

//-----player_location.c-----//

bool		is_player_spawn(char c);
int			get_player_pos(t_map_data *data);

//-----map_data_saver.c-----//

int			save_line_data(char *line, int row, t_map_id *ids, t_data *data);

//-----map_layout_extractor.c-----//

int			extract_map_layout(char **lines, size_t *row, t_map *map);

//-----map_line_processor.c-----//

size_t		get_next_char_block(char **save, const char *str);
bool		is_valid_layout_line(const char *line, size_t row, t_map *map);
char		*modified_map_line(char *old_line, t_map *map);

//-----------------------------------UTILS-----------------------------------//
//-----char_checks.c-----//

bool		is_whitespace(char c);
size_t		skip_whitespace(const char *str);

//-----line_utils.c-----//

bool		is_empty_line(char *line);
bool		has_leading_whitespace(char *line, int row);
size_t		skip_empty_lines(char **lines, size_t start_row);

//-----file_ops.c-----//

int			open_file_read(const char *file);
void		log_close(int fd, const char *file, int line);
int			correct_file_extension(const char *file, const char *extension);

//-----read_file.c-----//

char		**read_file(const char *file);

//-----arrays.c-----//

int			new_array(size_t member_size, size_t capacity, t_array *array);
int			expand_array(t_array *array);
int			append_to_array(void *src, t_array *array);

//-----color_utils.c-----//

int			set_color_channel(int color, t_color_channel channel, int value);
int			get_color_channel(int color, t_color_channel channel);

#endif /* PARSING_H */
