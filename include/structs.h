#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_mlx_image
{
	void		*img_ptr;
	int			*ret_value;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_mlx_image;

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;

typedef struct s_map_data
{
	char		**map;
	t_mlx_image	north_wall_image;
	t_mlx_image	east_wall_image;
	t_mlx_image	south_wall_image;
	t_mlx_image	west_wall_image;
	t_rgb		floor_color;
	t_rgb		ceiling_color;
}				t_map_data;

typedef struct s_data
{
	void		*mlx_ptr;
	t_map_data	map_data;
}				t_data;

#endif
