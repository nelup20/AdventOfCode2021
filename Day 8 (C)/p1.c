#include <stdio.h>
#include <stdbool.h>

int main() {
    int c;
    FILE *file;

    file = fopen("../input.txt", "r");
    if(file){
        bool isOutput = false;
        int charCount = 0;
        int result = 0;

        while((c = getc(file)) != EOF){
            if(c == '|'){
                isOutput = true;
                continue;
            }

            if(c == '\r'){
                isOutput = false;
                continue;
            }

            if(isOutput){
                if(c == ' '){
                    if(charCount == 2 || charCount == 3 || charCount == 4 || charCount == 7) result++;
                    charCount = 0;
                } else {
                    charCount++;
                }
            }
        }

        printf("Result: %d\n", result);
        fclose(file);
    }

    return 0;
}
