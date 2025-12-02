#include <bo_arena.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <bo_utils.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line {
    char *start;
    size_t len;
}Line;

#define declare_array_of(typ) \
    typedef struct ArrayOf##typ{\
        typ *items;\
        size_t len;\
    }ArrayOf##typ##s;

declare_array_of(Line)
declare_array_of(char)


ArrayOfLines parse_lines(bo_arena *arena, const ArrayOfchars data){
    size_t default_total_lines = 320;
    ArrayOfLines lines = {0};

    bo_allocate_items(lines.items, true, arena, Line, default_total_lines);
    Line line = {
        .len = 0,
        .start = data.items
    };
    for(size_t i = 0; i<data.len; i++){
        if(data.items[i]!='\n'){
            line.len++;
            continue;
        }

        lines.len +=1;
        if(lines.len>default_total_lines){
            //allocate new bigger buffer and update default_total_lines
            Line *new_lines_buf =  NULL;
            bo_allocate_items(new_lines_buf, true, arena, Line, default_total_lines*2);
            memcpy(new_lines_buf, lines.items, default_total_lines * sizeof(Line));
            default_total_lines*=2;
            bo_arena_free(arena, lines.items);
            lines.items = new_lines_buf;
        }
        lines.items[lines.len-1] =  line;
        line.len = 0;
        line.start = data.items+i+1;
    }
    return lines;
}

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
