/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:46:07 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/27 18:35:06 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/raycaster/render.h"

t_texture	*get_texture(t_game *game, t_ray *ray)
{
	t_texture	*tex;

	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			tex = &game->west_texture;
		else
			tex = &game->east_texture;
	}
	else
	{
		if (ray->dir.y > 0)
			tex = &game->north_texture;
		else
			tex = &game->south_texture;
	}
	return (tex);
}

static void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel(&game->mlx, x, y, game->ceiling_color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int draw_end)
{
	int	y;

	y = draw_end + 1;
	while (y < game->mlx.height)
	{
		put_pixel(&game->mlx, x, y, game->floor_color);
		y++;
	}
}

static void	draw_wall(t_game *game, t_ray *ray, t_draw_ctx *ctx)
{
	t_draw_info	data;

	if (ray->side == 0)
		data.wall_x = game->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		data.wall_x = game->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	data.wall_x -= (int)data.wall_x;
	data.tex = get_texture(game, ray);
	data.tex_int.x = (int)(data.wall_x * (data.tex->width));
	data.step = (double)data.tex->height / ctx->line_height;
	data.draw_start = -ctx->line_height / 2 + game->mlx.height / 2;
	data.tex_pos = (ctx->draw_start - data.draw_start) * data.step;
	data.y = ctx->draw_start;
	while (data.y <= ctx->draw_end)
	{
		data.tex_int.y = (int)data.tex_pos;
		if (data.tex_int.y < 0)
			data.tex_int.y = 0;
		if (data.tex_int.y >= data.tex->height)
			data.tex_int.y = data.tex->height - 1;
		put_pixel(&game->mlx, ctx->x, data.y, get_pixel_color(data.tex,
				data.tex_int.x, data.tex_int.y));
		data.tex_pos += data.step;
		data.y++;
	}
}

void	draw_column(t_ray *ray, t_game *game, int x)
{
	t_draw_ctx	ctx;

	ctx.x = x;
	ctx.line_height = (int)(game->mlx.height / ray->perp_wall_dist);
	ctx.draw_start = -ctx.line_height / 2 + game->mlx.height / 2;
	if (ctx.draw_start < 0)
		ctx.draw_start = 0;
	ctx.draw_end = ctx.line_height / 2 + game->mlx.height / 2;
	if (ctx.draw_end >= game->mlx.height)
		ctx.draw_end = game->mlx.height - 1;
	draw_ceiling(game, x, ctx.draw_start);
	draw_wall(game, ray, &ctx);
	draw_floor(game, x, ctx.draw_end);
}
