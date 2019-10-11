#include <stdio.h>
#include <stdbool.h>

main() {
    FILE *fp;
    char buff[255];

    fp = fopen("../stegosaurus.h","r");

    int x;

    for (x=0; x<7; x++) {
        fscanf(fp, "%s", buff);
    }

    x = 0;
    bool last_line = false;

    while(!last_line) {
        fscanf(fp, "%s", buff);
        if (buff[0] == '}')
            last_line = true;
        else {
            printf("%d : %s\n", x, buff );

            printf("] , [\n");
            printf("a lv2:ControlPort, lv2:InputPort;\n");
            printf("lv2:index %d;\n", x);
            printf("lv2:symbol \"volume\";\n");
            printf("lv2:name \"Volume\";\n");
            printf("lv2:minimum 0;\n");
            printf("lv2:maximum 1;\n");
            printf("lv2:default 1;\n");
            printf("\n");
            x++;
        }
    }

    printf("].\n");
}
