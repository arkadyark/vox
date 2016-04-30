#include <stdio.h>
#include <stdlib.h>
//remvocals oldfile newfile

#define FORMAT 44

void remVocals(FILE *vocals, FILE *novocals);

int main(int argc, char **argv){
    if(argc!=3){
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }
    FILE *vocals = fopen(argv[1], "rb");
    FILE *novocals = fopen(argv[2], "wb");

    if(vocals ==NULL){
        perror(argv[1]);
        exit(1);
    }

    if(novocals ==NULL){
        perror(argv[1]);
        exit(1);
    }

    remVocals(vocals, novocals);

    fclose(vocals);
    fclose(novocals);
    return 0;
}

void remVocals(FILE *vocals, FILE *novocals){
    short s;
    int i;
    for (i = 0; i < 132; i++) {
        fread(&s, sizeof(short), 1, vocals);
        fwrite(&s, sizeof(short), 1, novocals);
    }

    short left;
    short right;
    short combined;
    short *combined_ptr = &combined;
    int j = 1;
    while(j == 1){
        fread(&left, sizeof(left), 1, vocals);
        j = fread(&right, sizeof(right), 1, vocals);
        *combined_ptr = (left-right)/(short)2;
        fwrite(combined_ptr, sizeof(short), 1, novocals);
        fwrite(combined_ptr, sizeof(short), 1, novocals);
    }
}
