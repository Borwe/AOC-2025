#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <errno.h>
#include <stddef.h>
#include <bo_arena.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

ArrayOfchars get_file_data(
    bo_arena *arena,
    const char *restrict file){

    FILE *f = fopen(file, "r");
    bo_arena_assert(f!=NULL, "Data wasn't readable");
    struct stat s;
    if(stat(file,&s) !=0 ){
        const char *err = strerror(errno);
        fprintf(stderr, "Failed reading file, with error: %s\n", err);
        exit(-1);
    }
    ArrayOfchars file_data = {0};
    bo_allocate_items(file_data.items, true, arena, char, s.st_size);
    file_data.len = fread(file_data.items, sizeof(char), s.st_size, f);
    bo_arena_assert(file_data.len>0, "Seems no data was read");
    fclose(f);
    return file_data;
}


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
