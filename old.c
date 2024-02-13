#include <unistd.h>
#include <libc.h>
#include <stdio.h>

#define BUFFER_SIZE 1024
#define SETTINGS_SIZE 5

void    ft_putstr(char *str);
void    handle_error(char *message, int fd);
char**  create_map(int numRows, int numColumns);
void    validate_and_fill_map(char **map, char *buf, char *settings, int numRows, int numColumns, int fd);
void    print_map(char **map, int numRows, int numColumns);

int main (int argc, char **argv)
{
    int     fd;
    ssize_t read_bytes;
    char    buf[BUFFER_SIZE];
    char    settings[SETTINGS_SIZE];
    int     cols;

    if (argc < 2)
    {
        handle_error("No file provided\n", -1);
    }
    fd = open (argv[1], 0);
    if (fd == -1) 
    {
        handle_error("Map error\n", fd);
    }
    // Read the first line
    read_bytes = read (fd, buf, SETTINGS_SIZE);
    if (read_bytes != SETTINGS_SIZE)
    {
        handle_error("no map settings\n", fd);
    }
    memcpy(settings, buf, SETTINGS_SIZE);

    // Read the second line
    read_bytes = read(fd, buf, BUFFER_SIZE);
    if (read_bytes <= 0) 
    {
        handle_error("Invalid second line\n", fd);
    }

    // Count the number of characters in the second line
    cols = strcspn(buf, "\n");

    // validate map
    if (cols == 0)
    {
        handle_error("Invalid map 0 cols\n", fd);
    }

    // Define the number of rows and columns
    int numRows = settings[0] - '0';
    int numColumns = cols;

    // Create a 2D array
    char **map = create_map(numRows, numColumns);

    // Read and validate the map
    validate_and_fill_map(map, buf, settings, numRows, numColumns, fd);

    // Print the map
    print_map(map, numRows, numColumns);

    close (fd);
    return (0);
}

void handle_error(char *message, int fd)
{
    write(2, message, strlen(message));
    if (fd != -1)
    {
        close(fd);
    }
    exit(1);
}

char** create_map(int numRows, int numColumns)
{
    char **map = malloc(numRows * sizeof(char *));
    for (int row = 0; row < numRows; row++) {
        map[row] = malloc(numColumns * sizeof(char));
    }
    return map;
}

void validate_and_fill_map(char **map, char *settings, int numRows, int numColumns, int fd)
{
    char *buf = malloc((numColumns + 1) * sizeof(char)); // +1 for the newline character
    for (int row = 0; row < numRows; row++) {
        // Read a line from the file
        ssize_t read_bytes = read(fd, buf, numColumns + 1);
        if (read_bytes <= 0) {
            handle_error("Invalid map read\n", fd);
        }
        int buf_index = 0;
        for (int col = 0; col < numColumns; col++) {
            char c = buf[buf_index++];
            if (c != settings[1] && c != settings[2]) {
                handle_error("Invalid map2\n", fd);
            }
            map[row][col] = c;
        }
        if (buf[buf_index++] != '\n') {
            handle_error("Invalid map3\n", fd);
        }
    }
    free(buf);
}

void print_map(char **map, int numRows, int numColumns)
{
    for (int i = 0; i < numRows; i++) 
    {
        for (int j = 0; j < numColumns; j++) 
        {
            write(1, &map[i][j], 1);
        }
        write(1, "\n", 1);
    }
}