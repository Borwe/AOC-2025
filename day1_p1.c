#include <bo_arena.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <bo_utils.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

bool is_pointer_set_zero(int *ptr, const Line line){
    int sum = 0;
    char *invalid = NULL;
    sum = strtol(&line.start[1], &invalid, 10);
    if(line.start[0]=='L'){
        sum = -sum;
    }
    *ptr = (*ptr +  sum)%100;
    *ptr = *ptr < 0 ? *ptr + 100: *ptr;
    return *ptr == 0;
}

int logic(bo_arena *arena, const ArrayOfchars data){
    int result = 0;
    int start = 50;
    char *mem = NULL;
    bo_allocate_items(mem, true, arena, char, 1024*1024*1);
    bo_arena lines_arena = bo_make_arena(mem, 1024*1024*1, false, NULL);
    ArrayOfLines lines = parse_lines(&lines_arena, data);
    for(size_t i = 0; i<lines.len; i++){
        const Line line = lines.items[i];
        if(is_pointer_set_zero(&start,line)){
            result+=1;
        }
    }
    return result;
}

int main(int argc, char **argv){
    bo_arena_assert(argc==2, "Must pass two arguments");
    char *buf = calloc(1024*1024*10, sizeof(char));
    bo_arena arena = bo_make_arena((void*)buf, 1024*1024*100, false, NULL);

    ArrayOfchars file_data = get_file_data(&arena, argv[1]);
    bo_arena_assert(file_data.len>0, "Seems no data was read");
    printf("RESULT: %d\n",logic(&arena, file_data));
    return 0;
}
