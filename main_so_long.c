#include "so_long.h"

static void	handle_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

int32_t	main(void)
{
	mlx_t *mlx;
	mlx_image_t *image;

	// Initialize the mlx window
	mlx = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!mlx)
		handle_error();

	// Create a new image
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
		handle_error();

	// Set a pixel to red (0xFF0000FF = RGBA format: Red)
	mlx_put_pixel(image, 0, 0, 0xFF0000FF);

	// Put the image on the window
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
		handle_error();

	// Start the event loop
	mlx_loop(mlx);

	// Clean up and close
	mlx_terminate(mlx);
	return (0);
}
