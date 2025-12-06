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

        //get numbder from range
        for(size_t i=ranges[0]; i<=ranges[1]; i++){
            const size_t byts = snprintf(num_buffer,510, "%lu", i);

            //get size of bits to compare
            for(size_t j=1; j<byts; j++){

                if(byts%j != 0){
                    continue;
                }

                bool matched = true;
                bool entered_comparison = false;

                //loop through numbers to see if any match occurs
                for(char *l = num_buffer+j; ((uintptr_t)l)+j <= (uintptr_t)&num_buffer[byts]; l+=j){
                    entered_comparison = true;

                    if(strncmp(num_buffer, l, j)!=0){
                        matched = false;
                        break;
                    }
                }
                if(matched && entered_comparison){
                    result+=i;
                    break;
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
