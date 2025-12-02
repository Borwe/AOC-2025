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
    return *ptr == 100 || *ptr == 0;
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
    FILE *data = fopen(argv[1], "r");
    bo_arena_assert(data!=NULL, "Data wasn't readable");

    char *buf = calloc(1024*1024*10, sizeof(char));
    bo_arena arena = bo_make_arena((void*)buf, 1024*1024*100, false, NULL);

    ArrayOfchars file_data = {0};
    bo_allocate_items(file_data.items, true, &arena, char, 1024*1024*5);
    file_data.len = fread(file_data.items, sizeof(char), 1024*1024*5, data);
    bo_arena_assert(file_data.len>0, "Seems no data was read");
    printf("RESULT: %d\n",logic(&arena, file_data));
    return 0;
}
