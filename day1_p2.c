#include <bo_arena.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <bo_utils.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int times_pointer_crosses_zero(int *ptr, const Line line){
    int sum = 0;
    int times = 0;
    sum = strtol(&line.start[1], NULL, 10);
    while(sum!=0){
        if(line.start[0]=='L'){
            *ptr = (*ptr -  1)%100;
            *ptr = *ptr < 0 ? *ptr + 100: *ptr;
        }else{
            *ptr = (*ptr +  1)%100;
            *ptr = *ptr < 0 ? *ptr + 100: *ptr;
        }
        sum-=1;
        if(*ptr==0){
            times++;
        }
    }
    return times;
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
        result += times_pointer_crosses_zero(&start,line);
    }
    return result;
}

int main(int argc, char **argv){
    bo_arena_assert(argc==2, "Must pass two arguments");
    char *buf = calloc(1024*1024*10, sizeof(char));
    bo_arena arena = bo_make_arena((void*)buf, 1024*1024*100, false, NULL);

    ArrayOfchars file_data = get_file_data(&arena, argv[1]);
    printf("RESULT: %d\n",logic(&arena, file_data));
    return 0;
}
