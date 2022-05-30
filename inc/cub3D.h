/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 00:05:05 by ddecourt          #+#    #+#             */
/*   Updated: 2022/05/30 18:01:47 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ESC 0xff1b
# define UP 0x0077
# define RIGHT 0x0064
# define LEFT 0x0061
# define DOWN 0x0073
# define ARROW_RIGHT 0xFF53
# define ARROW_LEFT 0xFF51

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"


//maps de test avant parsing
//char mapi[20][20];

typedef struct s_params
{
	void	*mlx;
	void	*mlx_win;
	int		res_x;
	int		res_y;
}				t_params;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		ratio;
}			t_img;

typedef struct s_rgb
{	
	int		r;
	int		g;
	int		b;
}			t_rgb;

typedef struct s_texture
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	t_img			no_texture;
	t_img			so_texture;
	t_img			we_texture;
	t_img			ea_texture;
	int				fd_no;
	int				fd_so;
	int				fd_we;
	int				fd_ea;
	bool			f;
	unsigned int	fcl;
	bool			c;
	unsigned int	ccl;
}				t_texture;

//pour gérer les rotations
typedef struct s_rot
{
	double angle;
	double cos;
	double sin;
}				t_rot;

//vecteurs
typedef struct s_vec
{
	int x;
	int y;
}				t_vec;

typedef struct s_vec_double
{
	double x;
	double y;
}				t_vec_double;

typedef struct s_shape
{
	int x;
	int y;
	int width;
	int height;
}				t_shape;

//structure d'intervalle du raycasting
typedef struct s_ray
{
	t_vec_double		cos_step;
	t_vec_double 		sin_step;
	double			len_cos;
	double			len_sin;
}				t_ray;

typedef struct s_rparams
{
	double px;
	double py;
	double yaw;
}				t_rparams;

typedef struct s_env
{
	char		maap[20][20];
	char		**map;
	int			nb_lfile;
	int			height;
	int			width;
	int			ppi;
	int			count;
	int			spawn_pos[2];
	int			ppos;
	t_params	params;
	t_img		img;
	t_img 		minimap;
	t_texture	texture;
	t_ray		ray;
	t_rot		rot;
	t_vec		vec;
	t_vec_double	vec_double;
	t_rparams	ray_params;
}				t_env;

				///////////////////
				// GET NEXT LINE //
				///////////////////

//--get_next_line_utils--
char	*copy(char *s1, int *i, char *ret);

//--get next line--
int		ft_strclen(char *str, char c);
char	*ft_strndu(char *str, int n);
char	*ft_strjoi(char *s1, char *s2);
char	*ft_ret_str(char **ret_str);
char	*gnl(int fd);


				/////////////
				// PARSING //
				/////////////

//--alloc_map--
int		alloc_map(t_env *env, int fd, char *line);
int		open_map(t_env *env, int fd);
int		ft_len(char *line);
void	copy_line(char *line, t_env *env, char *map);

//--alloc_map2--
int		malloc_fail(char *line);
void	ft_copy(int *i, t_env *env, char *map);

//--check_color--
int		is_num(char *line);
int		is_num2(char *line, int *i, int *j, int *num);
int		check_file(t_texture *texture);

//--check_map--
int		ft_check_file(int fd);
int		check_around(char **map, int x, int y);
int		check_valid_char(t_env *env, char c, int x, int y);
int		check_wall_line(char *f_line, int width);
//int		check_wall_all_around(t_env *env, char **map);
int		ft_check_walls(t_env *env, char **map);


//--check_texture_utils--
int		recup_col(char *line, int i);
void	store_rgb(int ret, int col, t_rgb *couleur);
void	ft_check(const char *str, int *i, int *k, int *sign);
void	ft_maxmin(long int *n, int *stop);
int		ft_check_int(char *str, int *stop);

//--check_texture--
int		ft_store_texture(char **path, char *line);
int		ft_store_fc(char *line, unsigned int *rgb, int i);
int		ft_check_col(t_texture *texture, char *line);
int		ft_check_texture(t_texture *texture, char *line);
int		load_texture(t_env *env, t_img *img, char *path);

//--init_env--
void	init_env(t_env *env);
void	init_texture(t_texture *texture);
void	ft_free(t_env *env);

//--len_map--
int		len_map(char *line);
int		empty_line(char *line);
int		read_map(int fd, t_env *env, int *exit);
int		store_map(t_env *env, int fd, int *exit);
int		store_width(char *line, int width);


//--parsing--
int		error_message(char *str, int ret);
int		extension(char *ext, char *str, int len);
int		open_fd(int fd, char *argv);
int		parsing(int ac, char **av, t_env *env);
int		parsing_2(t_env *env, char *path);

//--store_map--
int		is_empty(char *s);
int		ft_store_map(char *path, t_env *env, int fd);
int		is_map(char *line);

//--store_params_utils--
int		len_num(char *line);
void	secure_line(char *line);
void	pass_space(char *line, int *i);
void	finish_line(char *line, int *i);
int		load_all_textures(t_env *env);

//--store_params--
int		pass_text(char *line, t_env *env, int *len, int *stop);
int		pass_col(char *line, t_env *env, int *len, int *stop);
void	read_file(int fd, int *nb_line, t_env *env, int *stop);
int		read_line(char *line, t_env *env, int *stop);
int		is_param(char *line);


				//////////
				// SRCS //
				//////////

//--win_utils--
int		quit_program(t_env *env);
int		keypress(int key, t_env *env);

//--raycasting--
void raycasting_1(t_env *env, t_img *img);
int		render_next_frame(t_env *env);
void	cast_forward(t_ray *ray, t_ray step);

//--raycasting_utils--
void rect(t_img *img, t_shape shape, int color);
double square(t_vec_double vector);
t_ray	init_ray(t_rot * rot, double x, double y);
int		check_colide(t_ray ray, t_env *env, t_rot rot, bool up);

//--mlx_utils--
unsigned int	create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//Minimap
void	ft_init_minimap(t_env *env);
int	draw_minimap(t_env *env);
int	draw_wall(t_env *env);
int draw_background(t_env *env);


//cub3d
t_img make_image(void *mlx, int width, int height);

int print_all_datas(t_env *env);

#endif
