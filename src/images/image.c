/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:31:51 by esekouni          #+#    #+#             */
/*   Updated: 2023/09/10 21:16:39 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../../includes/cub3.h"


void	draw_3D(t_image *image)
{
	int i;
	float	start;
	float pj;
	int y;
	


	/**
	 * @brief Equation is :		PJ	=	(Screen * SQUARE) / rays	==> TO FIND PROJECTION USING RAYS DISTANCE
	 * 							Start =	(Screen / 2) - (PJ / 2)		==> TO FIND START POINT
	 */
	i = 0;
	// printf("here\n");
	// int end = image->horizontalMapSize * SIZE * 2 / 3;
	while (i < 600)
	{
		pj = (HEIGHT * SIZE) / image->rays[i];
		if (pj > HEIGHT)
			pj = HEIGHT;
		start = 500 - (pj / 2);
		// printf("Value: i=%d  y=%d  pj=%.2f  start=%f   %f\n", i,y, pj, start, image->rays[i]);
		if (start < 0)
			start = 0;
		y = start;
		pj += start;
		while (y < pj)
			mlx_put_pixel(image->img, i, y++, 0xe6e6f0);
		i++;
	}
}

int	check(t_image *image, int move, float angle)
{
	int xx;
	int yy;

	yy = (image->yposition_p + move * sin(angle * (M_PI / 180)));
	xx = (image->xposition_p  + move * cos(angle * (M_PI / 180)));
	if ((image->map[(yy + 2)/SIZE][xx/SIZE] == '1'
	|| image->map[(yy - 2)/SIZE][xx/SIZE] == '1'
	|| image->map[yy/SIZE][(xx + 2)/SIZE] == '1'
	|| image->map[yy/SIZE][(xx - 2)/SIZE] == '1'))
		return (0);
	return (1);
}


int		check_draw_pixel_player(t_image *image, int n)
{

	if (n == 3 && check(image, 5, image->angle) == 0)
		return (0);
	if (n == 4 && check(image, -5, image->angle) == 0)
		return (0);
	if (n == 1 && check(image, 5, image->angle_right) == 0)
		return (0);
	if (n == 2 && check(image, 5, image->angle_left) == 0)
		return (0);
	return (1);
}

void	create_window(char **map)
{
	t_image image;

	image.map = map;
	image.xhorizontal = 0;
	image.yhorizontal = 0;
	image.xverticale = 0;
	image.yverticale = 0;
	image.xposition_p = 0;
	image.yposition_p = 0;
	image.angle = 0;
	image.angle_right = 0;
	image.angle_left = 0;
	image.hasEntered = 0;
	// // MAP RESOLUTION
	// image.horizontalMapSize = ft_strlen(*map);
	// image.verticalMapSize = map_size(map);
	
	image.rays = malloc(sizeof(float) * 600);
	image.mlx =  mlx_init(WIDTH, HEIGHT , "cub3D", 0);
	image.img = mlx_new_image(image.mlx, WIDTH, HEIGHT);
	// image.screen_img = mlx_new_image(image.mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(image.mlx, image.screen_img, 0, 0);
	mlx_image_to_window(image.mlx, image.img, 0, 0);
	mlx_loop_hook(image.mlx, drow_image, &image);
	mlx_key_hook(image.mlx, &key_hook, &image);
	mlx_loop(image.mlx);
	mlx_terminate(image.mlx);
}

int		main(int ac, char **av)
{
	char	**map_elements;
	char	**map;
	char	checker = 0;

	if (ac < 2)
		return (ft_putstr_fd("bad args\n", 2), 1);
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".cub", 4))
		return (ft_putstr_fd("File Name Error\n", 2), 0);
	
	if (!check_map(av[1], &map_elements, &map, &checker))
	{
		if (checker)
			return (ft_putstr_fd("File not found !!\n", 2), 1);
		free_double_pointer(map_elements);
		free_double_pointer(map);
		return (1);
	}
	t_elements *elements = parsing_elements(map_elements);
	free_double_pointer(map_elements);
	if (!elements)
		return (free_double_pointer(map), 1);
	create_window(map);
}