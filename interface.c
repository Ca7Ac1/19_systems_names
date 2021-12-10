#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "constants.h"

int main()
{
    mkfifo(PROCESS, 0644);
    mkfifo(OUTPUT, 0644);
    
    int writeProcess = open(PROCESS, O_WRONLY); 
    int readOutput = open(OUTPUT, O_RDONLY);

    char input[1000];
    input[0] = '\0';

    while (1)
    {
        printf("Input message to give to other process (or exit to quit): ");

        fgets(input, sizeof(input) - 1, stdin);

        if (input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0'; 
        }

        if (strcmp(input, "exit") == 0)
        {
            break;
        }

        write(writeProcess, input, sizeof(input));
        read(readOutput, input, sizeof(input));

        printf("\nMessage recieved from other process: %s\n", input);
    }

    return 0;
}
