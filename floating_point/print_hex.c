
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

static int print_hex(unsigned long num)
{
        const char hex[] = "0123456789abcdef";
        char str[40];
        int i = sizeof(str)-1;

        str[i--] = '\0';
        do {
                str[i--] = hex[num & 0x0f];
                num >>= 4;
        } while (num);

        str[i--] = 'x';
        str[i] = '0';
        puts(&str[i]);

        return 0;
}

int main(int argc, char *argv[])
{
    unsigned long foo = 1234567890;

    print_hex(foo);

    return EXIT_SUCCESS;
}

