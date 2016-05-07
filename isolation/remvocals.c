#include <stdio.h>
#include <stdlib.h>
//remvocals oldfile newfile

#define FORMAT 44

void remVocals(FILE *vocals, FILE *novocals, FILE *vocalsOnly);

int main(int argc, char **argv){
    if(argc!=4){
        fprintf(stderr, "Usage: %s <file> <vocalsOnly>\n", argv[0]);
        exit(1);
    }
    FILE *vocals = fopen(argv[1], "rb");
    FILE *novocals = fopen(argv[2], "wb");
    FILE *vocalsOnly = fopen(argv[3], "wb");

    if(vocals ==NULL){
        perror(argv[1]);
        exit(1);
    }

    if(novocals ==NULL){
        perror(argv[1]);
        exit(1);
    }

    remVocals(vocals, novocals, vocalsOnly);

    fclose(vocals);
    fclose(novocals);
    fclose(vocalsOnly);
    return 0;
}

void remVocals(FILE *vocals, FILE *novocals, FILE *vocalsOnly){
    short s;
    int i;
    for (i = 0; i < 132; i++) {
        fread(&s, sizeof(short), 1, vocals);
        fwrite(&s, sizeof(short), 1, novocals);
        fwrite(&s, sizeof(short), 1, vocalsOnly);
    }

    short left;
    short right;
    short combined;
    short *combined_ptr = &combined;
    short vocalsOnly_left;
    short vocalsOnly_right;
    short *vocalsOnly_left_ptr = &vocalsOnly_left;
    short *vocalsOnly_right_ptr = &vocalsOnly_right;
    int j = 1;
    while(j == 1){
        fread(&left, sizeof(left), 1, vocals);
        j = fread(&right, sizeof(right), 1, vocals);
        *combined_ptr = (left-right)/(short)2;
        fwrite(combined_ptr, sizeof(short), 1, novocals);
        fwrite(combined_ptr, sizeof(short), 1, novocals);

        *vocalsOnly_left_ptr = left - *combined_ptr;
        *vocalsOnly_right_ptr = right - *combined_ptr;
        fwrite(vocalsOnly_left_ptr, sizeof(short), 1, vocalsOnly);
        fwrite(vocalsOnly_right_ptr, sizeof(short), 1, vocalsOnly);
    }
}
