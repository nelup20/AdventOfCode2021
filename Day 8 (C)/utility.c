#include <string.h>

void emptyArray(char array[100]){
    memset(array, 0, strlen(array));
}

void swapArrays(char arr1[8], char arr2[8]){
    for(int i = 0; i < 8; i++){
        char temp = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = temp;
    }
}

void appendChar(char* string, char charToAppend){
    char temp[1] = {charToAppend};
    strncat(string, temp, 1);
}