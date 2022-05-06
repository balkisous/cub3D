/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 00:04:42 by ddecourt          #+#    #+#             */
/*   Updated: 2022/05/05 15:57:49 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	show_image(t_env *env)
{
	mlx_put_image_to_window(env->params.mlx, \
	env->params.mlx_win, env->img.img, 0, 0);
	return (1);
}

void 	randomise_map(t_env *env)
{
	int x;
	int y;
	x = 0;
	while (x < 20)
	{
		y = 0;
		while (y < 20)
		{
			env->map[x][y] = 0;
			if (rand() % 5 == 4)
				env->map[x][y] = 1;
			y++;
		}
		x++;
	}
}

t_img make_image(void *mlx, int width, int height)
{
	t_img img;
	
	img.width = width;
	img.height = height;
	img.img = mlx_new_image(mlx, width, height);
	if (!img.img)
		return (img);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	return(img);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_env env;

	if (!parsing(ac, av, &env))
		return (1);
	env.params.mlx = mlx_init();
	mlx_get_screen_size(env.params.mlx, &env.params.res_x, &env.params.res_y);
	env.params.res_x /= 1.5;
	env.params.res_y /= 1.5;
	env.params.mlx_win = mlx_new_window(env.params.mlx, env.params.res_x/1.5, env.params.res_y/1.5, "Cub3d");
	//env.params.mlx_win = mlx_new_window(env.params.mlx, 600, 600, "Cub3d");
	env.img = make_image(env.params.mlx, env.params.res_x, env.params.res_y);
	mlx_hook(env.params.mlx_win, 33, 1L << 17, quit_program, &env);
	mlx_hook(env.params.mlx_win, 2, 1L << 0, keypress, &env);
	randomise_map(&env);
	mlx_loop_hook(env.params.mlx, render_next_frame, &env);
	mlx_loop(env.params.mlx);

}
