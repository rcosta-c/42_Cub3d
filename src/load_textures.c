/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:47:30 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/09 17:01:02 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void load_textures(t_cub *cub)
{
    int i = 0;

    // Aloca espaço para 4 texturas
    cub->game.texture = malloc(sizeof(t_tex) * 4);
    if (!cub->game.texture)
        exit(EXIT_FAILURE);
    
    // Associa cada textura ao respectivo arquivo
    cub->game.texture[0].path = cub->map->no_file;
    cub->game.texture[1].path = cub->map->so_file;
    cub->game.texture[2].path = cub->map->we_file;
    cub->game.texture[3].path = cub->map->ea_file;
    
    while (i < 4)
    {
        cub->game.texture[i].img = mlx_xpm_file_to_image(cub->game.mlx, 
                                                       cub->game.texture[i].path, 
                                                       &cub->game.texture[i].width, 
                                                       &cub->game.texture[i].height);
        if (!cub->game.texture[i].img)
            exit(EXIT_FAILURE);
        
        cub->game.texture[i].addr = (int *)mlx_get_data_addr(cub->game.texture[i].img, 
                                                         &cub->game.texture[i].bpp, 
                                                         &cub->game.texture[i].line_len, 
                                                         &cub->game.texture[i].endian);
        i++;
    }
}
