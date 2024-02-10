/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 07:48:00 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/29 07:55:48 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <limits.h>
# include "MLX42/include/MLX42/MLX42.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# define WIDTH 1920
# define HEIGHT 1080
# define MOVE_SPEED 5
# define ROT_SPEED 5
# define BPP 4
# define TILE_SIZE 32
# define FOV_ANGLE 60
# define H_RAY 0
# define V_RAY 1

typedef struct s_cord
{
	double	x;
	double	y;
}				t_cord;

typedef struct s_chk
{
	char		**elem;
	int			line_count;
	int			no_elem;
	int			so_elem;
	int			we_elem;
	int			ea_elem;
	int			f_elem;
	int			c_elem;
	int			comma_count;
	int			digit_count;
	int			digit;
	int			num_elem;
}				t_chk;

typedef struct s_map
{
	t_chk		map_chk[1];
	t_cord		charac[1];
	char		*no_txt;
	char		*so_txt;
	char		*we_txt;
	char		*ea_txt;
	uint32_t	c_color;
	uint32_t	f_color;
	char		charac_dir;
	char		**map;
	int			map_width;
	int			map_height;

}				t_map;

typedef struct s_player
{
	t_cord		*player;
	double		rot_speed;
	double		rot_angle;
	double		ray_angle;
	double		fov;
}				t_player;

typedef struct s_casting
{
	t_cord		h_insec[1];
	t_cord		v_insec[1];
	t_cord		*player;
	char		**map;
	double		ray_angle;
	double		x_step;
	double		y_step;
	double		x_first;
	double		y_first;
	double		h_dist;
	double		v_dist;
	int			x_index;
	int			y_index;
	int			ray_up;
	int			ray_down;
	int			ray_right;
	int			ray_left;
	int			width;
	int			height;
	int			h_found_wall;
	int			v_found_wall;
}				t_casting;

typedef struct s_ray
{
	mlx_texture_t	*texture;
	uint32_t		*text_color;
	t_cord			wall_hit[1];
	double			ray_angle;
	double			ray_distance;
	uint32_t		color;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	int				ray_type;
	int				ray_up;
	int				ray_down;
	int				ray_right;
	int				ray_left;
}				t_ray;

typedef struct s_mlx
{
	mlx_image_t		*img;
	mlx_t			*win;
	mlx_texture_t	*no_txt;
	mlx_texture_t	*so_txt;
	mlx_texture_t	*we_txt;
	mlx_texture_t	*ea_txt;
	uint32_t		*north_clr;
	uint32_t		*south_clr;
	uint32_t		*west_clr;
	uint32_t		*east_clr;
	t_map			*map_data;
	t_player		player_data[1];
	double			map_scale;
	t_ray			*rays;
	t_casting		*cast;
	uint32_t		pos_txt_x;
	uint32_t		pos_txt_y;
}				t_mlx;

// UTILS
void			*ft_memset(void *s, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			ft_putendl(char *s);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s);
char			*ft_strchr(const char *s, int c);
int 			ft_isdigit(char c);

// CUB3D UTILS
void			ft_init_cord(t_cord *cord, double x, double y);
void			ft_paint_pix(uint8_t *pix, uint32_t clr, size_t size);
double			ft_norm_angle(double *angle);
double			ft_player_angle(t_map *map_data);
uint32_t		ft_rgb(uint32_t r, uint32_t g, uint32_t b, uint32_t o);

// GNL
char			*get_next_line(int fd);
char			*ft_check_nl(char **reserve);
size_t			ft_strlen_gnl(const char *s);
int				ft_strchr_gnl(char *s, int c);
void			ft_strlcpy_gnl(char *dst, const char *src, size_t size);
char			*ft_strjoin_gnl(char *reserve, char *buffer);
char			*ft_strdup_gnl(char **str);

// FT_SPLIT
char			**ft_split(char const *s, char c);
char			**ft_alloc(char **ptr, const char *s, char c, size_t wc);
size_t			word_count(char const *s, char c);
void			*ft_clr(char **ptr, size_t x);

// ERROR AND DESTROY
void			ft_error(char *err, t_map *map_data);
void			ft_destroy_map_data(t_map *map_data);
void			ft_clear(void **ptr);
void			ft_esc(void *param);

// PARSING
void			ft_nb_line(t_map *map_data, char *name);
void			ft_open_map(t_map *map_data, char *name);
void			ft_parse_map(t_map *map_data, char *name);

// CHECK
void			ft_arg_chk(int ac, char *av);
void			ft_chk_elem(t_map *map_data);
void			ft_chk_map(t_map *map_data);
int				ft_all_elems(t_chk *map_chk);
void			ft_chk_character(t_map *map_data, int x, int y);
void			ft_chk_walls(t_map *map_data, char **map, size_t x, size_t y);
void			ft_iso_content(t_map *map_data, int start);
void			ft_chk_content(t_map *map_data, int start);

// ELEM SETUP
void			ft_dir_elem(t_map *map_data, char **dire_txt, int *dire_elem);
void			ft_rgb_init(t_map *map_data, char *elem, uint32_t *clr, int *i);
void			ft_rgb_chk(t_map *map_data, char *elem, uint32_t *clr);
void			ft_rgb_elem(t_map *map_data, char **elem, int opt);

// RENDER
void			ft_render(t_map *map_data);
void			ft_init_mlx(t_mlx *mlx);
void			ft_init_ray_texture(t_mlx *mlx, t_ray *ray);
void			ft_load_textures(t_mlx *mlx);
uint32_t		ft_pix_clr(t_ray *ray, int y_offset, int x_offset);
double			ft_txt_x_offset(t_ray *ray);
void			ft_scale_cord_txt(t_mlx *mlx, t_ray *ray, int x);
void			ft_render_walls(t_mlx *mlx, t_ray *rays);
double			ft_cord_dist(t_cord *p1, t_cord *p2);
void			ft_wall_hit(t_ray *ray, t_casting *cast);
void			ft_ray_dir(t_casting *cast);
void			ft_init_ray_dir(t_ray *ray, t_casting *cast);
void			ft_calc_h_inter(t_casting *cast);
void			ft_h_inter(t_casting *cast);
void			ft_calc_v_inter(t_casting *cast);
void			ft_v_inter(t_casting *cast);
void			ft_cast_rays(t_mlx *mlx, t_ray *rays);
void			ft_paint_c_f(t_mlx *mlx);
void			ft_render_map(t_mlx *mlx);

// PLAYER MOVES
void			ft_mv_straight(t_mlx *mlx, int pix);
void			ft_mv_sides(t_mlx *mlx, int pix);
void			ft_rotate(t_mlx *mlx, int pix);
void			ft_player_moves(void *param);

#endif
