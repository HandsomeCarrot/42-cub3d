/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:52:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/28 17:23:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../common/logging.h"
# include "parsing_types.h"
# include "parsing_constants.h"
# include "../../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>

//-----CLEANUP-----//

void		free_string_array(char ***string_array);

//-----parse.c-----//

int			parse(int argc, char **argv, t_map_data *data);

//-----------------------------------CONFIG-----------------------------------//

//-----parse_colors.c-----//

int			save_color(char *line, int row, t_map_id *data_id,
				t_colors *colors);

//-----identify_textures.c-----//

t_map_id	*get_map_data_type(char *line, int row, t_map_id *ids);
bool		all_ids_found(t_map_id *ids);
t_map_id	*get_map_identifiers(void);

//-----parse_textures.c-----//

int			save_image(char *line, int row, t_map_id *data_id,
				t_map_data *data);

//-----------------------------------MAP-----------------------------------//
//-----read_map_file.c-----//

int			parse_map_file(char *file, t_map_data *data);

//-----validate_map.c-----//

int			parse_map_layout(t_map_data *data);

//-----save_map_data.c-----//

int			save_line_data(char *line, int row, t_map_id *ids,
				t_map_data *data);

//-----extract_map_layout.c-----//

int			extract_map_layout(char **lines, size_t *row, t_map *map);

//-----process_map_lines.c-----//

size_t		get_next_char_block(char **save, const char *str);
bool		is_valid_layout_line(const char *line, size_t row, t_map *map);
char		*modified_map_line(char *old_line, t_map *map);

//-----check_neighbors.c-----//

bool		has_valid_neighbors(int x, int y, t_map_data *data);

//-----------------------------------PLAYER-----------------------------------//
//-----locate_player.c-----//

bool		is_player_spawn(char c);
int			get_player_pos(t_map_data *data);

//-----------------------------------UTILS-----------------------------------//
//-----manage_arrays.c-----//

int			new_array(size_t member_size, size_t capacity, t_array *array);
int			expand_array(t_array *array);
int			append_to_array(void *src, t_array *array);

//-----manage_colors.c-----//

int			set_color_channel(int color, t_color_channel channel, int value);
int			get_color_channel(int color, t_color_channel channel);

//-----manage_files.c-----//

int			open_file_read(const char *file);
void		log_close(int fd, const char *file, int line);
int			correct_file_extension(const char *file, const char *extension);

//-----check_lines.c-----//

bool		is_empty_line(char *line);
bool		has_leading_whitespace(char *line, int row);
size_t		skip_empty_lines(char **lines, size_t start_row);

//-----read_file_content.c-----//

char		**read_file(const char *file);

//-----check_chars.c-----//

bool		is_whitespace(char c);
size_t		skip_whitespace(const char *str);

//---------------------------------VALIDATION---------------------------------//
//-----validate_content.c-----//

bool		has_trailing_content(char *line, int row);
int			check_hanging_lines(char **lines, size_t row);

//----------------------------------LOGGING-----------------------------------//
//-----log_parsing_info.c-----//

void		log_extension_error(const char *file, const char *message,
				const char *src_file, int line);
void		log_line_error(int line_num, const char *message,
				const char *src_file, int line);
void		log_id_processing(t_map_id *data_id, char *src_file, int src_line);
void		log_found_img(const char *id, char *img_path, char *src_file,
				int src_line);
void		log_found_color(const char *id, int color, char *src_file,
				int src_line);

//-----log_parsing_error.c-----//

void		log_missing_ids(t_map_id *ids);
void		log_invalid_file(const char *file, const char *extension);
void		log_invalid_map_line(int row, const char *line, int pos);
void		log_multiple_player_spawns(int y, int x);

#endif /* PARSING_H */
