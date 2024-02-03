#include "types.h"
#include "user.h"
#include "fcntl.h"

enum {
    MAX_WORD_LENGTH = 15
};

struct word
{
    int length;
    char data[MAX_WORD_LENGTH + 1];
};

int max(const int l1, const int l2)
{
    return (l1 >= l2) ? l1 : l2;
}

void convert_to_lowercase(struct word *w)
{
    for (int i = 0; i < w->length; i++)
    {
        if (w->data[i] >= 'A' && w->data[i] <= 'Z')
        {
            w->data[i] = w->data[i] + 32;
        }
    }
}

void strdiff(const int fd, const struct word *w1, const struct word *w2)
{
    int size = max(w1->length, w2->length);
    int bit;
    char bit_char;
    for (int i = 0; i < size; i++)
    {
        bit = !(w1->data[i] >= w2->data[i]);
        bit_char = bit + '0';
        write(fd, &bit_char, 1);
    }
}

int invalid_length(const int w_length)
{
    return (w_length < 1 || w_length > MAX_WORD_LENGTH + 1);
}

void initialize_word(struct word *w, const char *_data, int id)
{
    w->length = strlen(_data);
    if (invalid_length(w->length))
    {
        printf(1, "Length of each word%d should be between 1 and 15 and %d is too much.\n", id, w->length);
        exit();        
    }
    for (int i = 0; i < w->length; i++)
        w->data[i] = _data[i];
    for (int i = w->length; i < MAX_WORD_LENGTH; i++)
        w->data[i] = '@';
    w->data[MAX_WORD_LENGTH] = '\0';
    convert_to_lowercase(w);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf(1, "strdiff takes two words to run!\n");
        exit();
    }

    struct word w1, w2;
    initialize_word(&w1, argv[1], 1);
    initialize_word(&w2, argv[2], 2);

    int fd;
    const char *filename = "strdiff_result.txt";
    if ((fd = open(filename, O_CREATE | O_WRONLY)) < 0)
    {
        printf(1, "strdiff: cannot create strdiff_result.txt\n");
        exit();
    }
    strdiff(fd, &w1, &w2);
    write(fd, "\n", 1);
    close(fd);

    exit();
}