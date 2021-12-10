#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "constants.h"

void process(char *);
void quick(char *, int, int);
int partition(char *, int, int);
void swap(char *, int, int);

int main()
{
    mkfifo(PROCESS, 0644);
    mkfifo(OUTPUT, 0644);

    int readProcess = open(PROCESS, O_RDONLY); 
    int writeOutput = open(OUTPUT, O_WRONLY);

    char input[1000];
    int r = read(readProcess, input, sizeof(input));
    while (r != 0 && r != -1)
    {
        process(input);
        write(writeOutput, input, sizeof(input));
        
        r = read(readProcess, input, sizeof(input));
    }
}

void process(char *input)
{
    quick(input, 0, strlen(input));
}

void quick(char *input, int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int ind = partition(input, l, r);
    quick(input, l, ind);
    quick(input, ind + 1, r);
}

int partition(char *input, int l, int r)
{
    int index = l;
    for (int i = l; i < r - 1; i++)
    {
        if (input[i] < input[r - 1])
        {
            swap(input, i, index);
            index++;
        }
    }

    swap(input, index, r - 1);
    return index;
}

void swap(char *input, int a, int b)
{
    char temp = input[a];
    input[a] = input[b];
    input[b] = temp;
}
