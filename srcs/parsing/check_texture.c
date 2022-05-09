/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 00:36:31 by ddecourt          #+#    #+#             */
/*   Updated: 2022/05/09 18:48:16 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cub3D.h"

//store texture path
int	ft_store_texture(char **path, char *line)
{
	int	i;

	i = 0;
	ft_memmove(&line[i], &line[i] + 3, ft_strlen(&line[i]));
	pass_space(line, &i);
	*path = ft_strdup(&line[i]);
	return (1);
}

//store color fot floor and ceiling
int	ft_store_FC(char *line, unsigned int rgb)
{
	int	i;
	int	col;
	int	ret;
	int	stop;
	t_rgb couleur;
	(void)rgb;

	i = 0;
	col = 0;
	stop = 0;
	while (col < 3)
	{
		pass_space(line, &i);
		ret = recup_col(line, &i, &stop);
		i = len_num(&line[i]);
		if (stop)
		{
			printf("passe ici when -----\n");
			return (-1);
		}
		store_rgb(ret, col, &couleur);
		col++;
		printf("ret vaut -%d-\n", ret);
		printf("le char -%c-\n", line[i]);
		if (line[i] == ',')
			i++;
		else if (line[i] != '\n' && line[i] != '\0')
			return (error_message("!!!il manque une couleur!!!!", 0));
	}
		printf("une fois fini le r = -%d- : le g = -%d- : le b = -%d-\n", couleur.r, couleur.g, couleur.b);
	//if (col )
	// checker la couleur existe
	// return 1 si c'est bon et -1 si erreur
	return (1);
}

int	ft_check_col(t_texture *texture, char *line)
{
	int	i;

	i = 0;
	if (!is_num(line))
		return (error_message("Invalid caracters in colors", -1));
	if (line[i] == 'F' && texture->f == false)
	{
		printf("la blou\n");
		texture->f = true;		// le true vient apres avoir check la coul
		//return (ft_store_FC(&line[i + 1], texture->fcl));
	}
	else if (line[i] == 'C' && texture->c == false)
	{
		printf("lou bli\n");
		texture->c = true;		// le true vient apres avoir check la coul
		//return (ft_store_FC(&line[i + 1], texture->ccl));
	}
	return (-1);
}

//	check path texture and if texture exist
int	ft_check_texture(t_texture *texture, char *line)
{
	int	i;

	i = 0;
	if (!extension(".xpm", line, 5))
		return (error_message("texture is not in xpm extention", -1));
	while (line[i])
	{
		pass_space(line, &i);	
		if (line[i] == 'N' && line[i + 1] && line[i + 1] == 'O' && texture->no_path == NULL)
			return (ft_store_texture(&(texture->no_path), &line[i]));
		else if (line[i] == 'S' && line[i + 1] && line[i + 1] == 'O' && texture->so_path == NULL)
			return (ft_store_texture(&(texture->so_path), &line[i]));
		else if (line[i] == 'W' && line[i + 1] && line[i + 1] == 'E' && texture->we_path == NULL)
			return (ft_store_texture(&(texture->we_path), &line[i]));
		else if (line[i] == 'E' && line[i + 1] && line[i + 1] == 'A' && texture->ea_path == NULL)
			return (ft_store_texture(&(texture->ea_path), &line[i]));
		else
			return(-1);
	}
	return (-1);
}

//function to load a texture
int	load_texture(t_env *env, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(env->params.mlx, path, \
	&(img->width), &(img->height));
	if (img->img)
		img->addr = mlx_get_data_addr(img->img, \
		&(img->bits_per_pixel), &(img->line_length), \
		&(img->endian));
	return (0);
}

//load all textures images
int	load_all_textures(t_env *env)
{
	load_texture(env, &(env->texture.no_texture), env->texture.no_path);
	load_texture(env, &(env->texture.so_texture), env->texture.so_path);
	load_texture(env, &(env->texture.we_texture), env->texture.we_path);
	load_texture(env, &(env->texture.ea_texture), env->texture.ea_path);
	return (0);
}
