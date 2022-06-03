/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 00:05:05 by ddecourt          #+#    #+#             */
/*   Updated: 2022/06/03 16:02:52 by bben-yaa         ###   ########.fr       */
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
	int				fcl;
	bool			c;
	int				ccl;
}				t_texture;

//vecteurs
typedef struct s_vec
{
	double		dirx; //vecteur de direction (commence à -1 pour N, 1 pour S, 0 sinon)
	double		diry; //vecteur de direction (commence à -1 pour W, 1 pour E, 0 sinon)
	double		planx; //vecteur du plan (commence à 0.66 pour E, -0.66 pour W, 0 sinon)
	double		plany; //vecteur du plan (commence à 0.66 pour N, -0.66 pour S, 0 sinon)
}				t_vec;

typedef struct s_pos
{
	double x; //position x du joueur
	double y; //position y du joueur
}				t_pos;

typedef struct s_distance
{
	double		sidex; //distance que le rayon parcours jusqu'au premier point d'intersection vertical (=un coté x)
	double		sidey; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)
	double		deltax; //distance que rayon parcours entre chaque point d'intersection vertical
	double		deltay; //distance que le rayon parcours entre chaque point d'intersection horizontal
	double		playerwall; // distance du joueur au mur
}				t_distance;

//structure d'intervalle du raycasting
typedef struct s_camera
{
	double		raydirx; //calcul de direction x du rayon
	double		raydiry; //calcul de direction y du rayon
	double		camera; //point x sur la plan camera : Gauche ecran = -1, milieu = 0, droite = 1
}				t_camera;

typedef struct	s_ray
{
	t_vec		vec;
	t_camera	camera;
	t_distance	distance;
	t_pos		pos;

	int 		mapx;
	int 		mapy;
	int			stepx; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int			stepy; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int			hit; // 1 si un mur a ete touche, 0 sinon
	int			side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	
	int			lineheight; //hauteur de la ligne a dessiner
	int			drawstart; //position de debut ou il faut dessiner
	int			drawend; //position de fin ou il faut dessiner
	int			x; //permet de parcourir tous les rayons
}					t_ray;

typedef struct s_env
{
	char		**map;
	int			nb_lfile;
	int			height;
	int			width;
	int			ppi;
	int			count;
	double		spawn_pos[2];
	double		speed;
	double		rotspeed;
	double		oldplanex;
	double		olddirx;
	int			ppos;
	int			texy;
	int			texx;
	t_params	params;
	t_img		img;
	t_img 		minimap;
	t_texture	texture;
	t_ray		ray;
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
int		error_message(char *str, int ret);

//--check_color--
int		is_num(char *line);
int		is_num2(char *line, int *i, int *j, int *num);
int		check_file(t_texture *texture);
int		check_path_files(t_env *env);
void	player_pos(char c, t_env *env);

//--check_map--
int		ft_check_file(int fd);
int		check_around(char **map, int x, int y);
int		check_valid_char(t_env *env, char c, int x, int y);
int		check_wall_line(char *f_line, int width);
int		ft_check_walls(t_env *env, char **map);


//--check_texture_utils--
int		recup_col(char *line, int i);
void	store_rgb(int ret, int col, t_rgb *couleur);
void	ft_check(const char *str, int *i, int *k, int *sign);
void	ft_maxmin(long int *n, int *stop);
int		ft_check_int(char *str, int *stop);

//--check_texture--
int		ft_store_texture(char **path, char *line);
int		ft_store_fc(char *line, int *rgb, int i);
int		ft_check_col(t_texture *texture, char *line);
int		ft_check_texture(t_texture *texture, char *line);
int		load_texture(t_env *env, t_img *img, char *path);

//--init_env--
void	init_env(t_env *env);
void	init_ray(t_env *env);
void	init_texture(t_texture *texture);
void	ft_free_map(char **map);
void	ft_free(t_env *env);

//--len_map--
int		len_map(char *line);
int		empty_line(char *line);
int		read_map(int fd, t_env *env, int *exit);
int		store_map(t_env *env, int fd, int *exit);
int		store_width(char *line, int width);


//--parsing--
int		extension(char *ext, char *str, int len);
int		open_fd(int fd, char *argv);
int		parsing(int ac, char **av, t_env *env);
int		parsing_2(t_env *env, char *path);

//--store_map--
int		is_empty(char *s);
int		in_map(char *line, int i);
int		is_map(char *line);
int		is_param(char *line);

//--store_params_utils--
int		len_num(char *line);
void	secure_line(char *line);
void	pass_space(char *line, int *i);
void	finish_line(char *line, int *i);
int		load_all_textures(t_env *env);

//--store_params--
int		pass_text(char *line, t_env *env, int *len, int *stop);
int		pass_col(char *line, t_env *env, int *len, int *stop);
int		rread_file(char *line, int *nb_line, t_env *env, int *stop);
void	read_file(int fd, int *nb_line, t_env *env, int *stop);
int		read_line(char *line, t_env *env, int *stop);


				//////////
				// SRCS //
				//////////

//--win_utils--
int		quit_program(t_env *env);
int		keypress(int key, t_env *env);

//--raycasting--
void	calculate_step(t_env *env);
void    wall(t_env *env);
void	stripe(t_env *env);
void	draw(t_env *env);
void	raycasting(t_env *env);

//--raycasting_utils--
void	ft_init_ray(t_env *env);
void    init_ray2(t_env *env, int x);
int		get_texture_color(t_env *env, t_img img);


//--mlx_utils--
unsigned int	create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//Minimap
void	ft_init_minimap(t_env *env);
int	draw_minimap(t_env *env);
int	draw_wall(t_env *env);
int draw_background(t_env *env);
void	draw_stripe(t_env *env);


//cub3d
t_img make_image(void *mlx, int width, int height);

int print_all_datas(t_env *env);

#endif
