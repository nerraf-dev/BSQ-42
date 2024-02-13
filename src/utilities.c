//utilities.c
#include <unistd.h>

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

int calculate_line_length(char *buf)
{
    int i = 0;
    int length = 0;
    // Skip the metadata line
    while (buf[i] != '\n' && buf[i] != '\0')
        i++;
    if (buf[i] == '\n')
        i++; // Skip the newline character
    while (buf[i] != '\n' && buf[i] != '\0') {
        length++;
        i++;
    }
    return length;
}

int str_to_int(char *str) {
    int result = 0;
    int i = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}
