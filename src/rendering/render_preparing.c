/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_preparing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfritz <jfritz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:08:48 by jfritz            #+#    #+#             */
/*   Updated: 2022/04/10 19:09:00 by jfritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h" 

/**
 * This is the render loop. It gets called every frame.
 * There is a cache which will prevent the image from updating
 * when nothing changed.
 */
int	render_loop(void	*cub_)
{
	int		x;
	t_cub	*cub;

	x = 0;
	cub = (t_cub *) cub_;
	move(cub);
	mouse_handler(cub);
	if (is_player_in_cache(cub))
		return (0);
	create_mlx_data(cub);
	while (x < WIDTH)
	{
		fill_floor_ceiling(cub, x);
		render_walls(cub, x);
		x++;
	}
	mlx_draw_imagegiven(cub);
	render_minimap(cub);
	destroy_mlx_image(cub);
	return (0);
}

/**
 * Move and rot speed are being set here
 */
void	set_moverot_speeds(t_cub *cub)
{
	cub->math->frame_time = (24) / 1000.0;
	cub->math->moveSpeed = cub->math->frame_time * 5.0;
	cub->math->rotSpeed = cub->math->frame_time * 3.0;
}

/**
 * Creates a window, creates mlx variables, loads the textures, 
 * setup hooks and loops
 * Sets initial key controls too
 */
static void	create_window(t_cub *cub)
{
	cub->vars.mlx = mlx_init();
	cub->vars.win = mlx_new_window(cub->vars.mlx, WIDTH, HEIGHT, "CUB3D");
	cub->movetrigger = initalize_key_trigger();
	cub->math = xmalloc(sizeof(t_math));
	set_moverot_speeds(cub);
	calculate_player_pos(cub);
	if (!load_textures(cub))
		exit(EXIT_FAILURE);
	mlx_mouse_hide();
	mlx_hook(cub->vars.win, 2, 1L << 0, key_handler, cub);
	mlx_hook(cub->vars.win, 3, 1L << 0, key_up, cub);
	mlx_loop_hook(cub->vars.mlx, render_loop, cub);
	mlx_loop(cub->vars.mlx);
}

/**
 * Starts cub3d
 */
void	start_cub3d(t_cub *cub)
{
	create_window(cub);
}
