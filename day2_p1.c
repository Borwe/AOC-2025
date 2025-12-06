#include <stdio.h>
#include "utils.h"
#include <bo_arena.h>
#include <bo_utils.h>
#include <stdlib.h>
#include <string.h>

size_t logic(const ArrayOfchars *data){
    size_t result = 0;
    char *next = &data->items[0];
    char num_buffer[512] = {0};
    size_t ranges[2] = {0};
    while((uintptr_t)next < (uintptr_t)data->items+ data->len){
        char *end = NULL;
        ranges[0] = strtol(next, &end, 10);
        next = end+1;
        ranges[1] = strtol(next, &end, 10);
        next = end+1;

        for(size_t i=ranges[0]; i<=ranges[1]; i++){\
            int byts = snprintf(num_buffer,512, "%lu", i);
            if(byts % 2 == 0){
                const int size = byts/2;
                if(strncmp(num_buffer, num_buffer+size, size) == 0){
                    result+=i;
                }
            }
        }
    }
    return result;
}

int main(int argc, char **argv){
    bo_arena_assert(argc==2, "Need to pass atleast two arguments");
    char *mem = calloc(1024*1024*10, sizeof(char));
    bo_arena arena = bo_make_arena(mem, 1024*1024*10, false, NULL);
    ArrayOfchars data = get_file_data(&arena, argv[1]);
    bo_arena_assert(data.len>0, "DATA should be greater than zero");

    printf("RESULT %lu\n",logic(&data));
    return 0;
}
