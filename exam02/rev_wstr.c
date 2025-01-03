#include <unistd.h>
#include <stdlib.h>

int is_whitespace(char c)
{
    return c == ' ' || c == '\t';
}

void reverse_words_order(char *str)
{
    int start = 0;
    int end = 0;
    char *t;
    int w = 0;
    int i = 0;

    while (str[end] != '\0')
        end++;
    while (end >= 0)
    {
        end--;
        while(is_whitespace(str[end] && str[end]))
            end--;
        while(str[end] && !is_whitespace(str[end]) && end >= 0)
        {
            end--;
            w++;
        }
        t = malloc(w + 1 * sizeof(char));
        if (!t)
            return ;
        start = end + 1;
        while(i < w && str[start])
            t[i++] = str[start++];
        t[i] = '\0';
        i = 0;
        if(w > 0)
        {
            write(1, t, w);
            if (end != 0)
                write(1, " ", 1);
        }
        w = 0;
        free(t);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(1, "\n", 1);
        return 0;
    }

    reverse_words_order(argv[1]);
    write(1, "\n", 1);
    return 0;
}
