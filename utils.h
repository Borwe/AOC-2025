#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <stddef.h>
#include <bo_arena.h>
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

#endif
