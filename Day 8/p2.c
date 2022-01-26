#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "p2.h"

// This is an awful mess. But it works, and I'm too lazy to refactor right now, maybe tomorrow.
// I desperately need to resume reading the K&R book, I stopped @ around page 15, and it shows... I barely know C.

// One thing I haven't figured out is why the \n at the beginning of each string messed up the calculation of the digits.
// As in every line/string that contained a \n at the beginning would turn the 1st digit to 0, but that shouldn't be
// the case since I'm skipping \n. But anyways that's why I do a memcpy() for newStr. Also, CLion's debugger isn't as
// intuitive as I hoped.

// I'll also add an explanation of how the algo generally works tomorrow.

int main() {
    char c;
    FILE *file;
    char str[100] = "";
    char newStr[100] = "";
    int finalResult = 0;

    file = fopen("../input.txt", "r");
    if(file){
        while((c = getc(file)) != EOF){
            if(c == '\r'){
                if(str[0] == '\n'){
                    memcpy(newStr, str + 1, 100);
                    finalResult += calculateEntry(newStr);
                } else {
                    finalResult += calculateEntry(str);
                }
                emptyArray(str);
                continue;
            } else {
                char temp[1] = {c};
                strncat(str, temp, 1);
            }
        }

        fclose(file);
    }

    printf("Result: %d", finalResult);

    return 0;
}

int calculateEntry(const char string[100]){
    struct mapping mapping = {0, 0, 0, 0, 0, 0, 0};
    struct sequences sequences = {"", "", "", "", "", "", ""};

    while(!isMappingComplete(mapping)){
        char str[8] = "";

        bool isInSequence = false;

        for(int i = 0; i < 100; i++){
            if(string[i] == '|' || string[i] == '\r') break;
            if(string[i] == '\n') continue;

            isInSequence = string[i] != ' ';

            if(isInSequence){
                char temp[1] = {string[i]};
                strncat(str, temp, 1);
            } else {
                int sequenceLength = strlen(str);
                if(sequenceLength == 2 && mapping.topRight == 0 && mapping.bottomRight == 0){
                    mapping.topRight = str[0];
                    mapping.bottomRight = str[1];
                    memcpy(sequences.one, str, 8);
                }

                if(sequenceLength == 3 && mapping.topRight != 0 && mapping.bottomRight != 0 && mapping.top == 0){
                    for(int j = 0; j < 3; j++){
                        if(str[j] != mapping.topRight && str[j] != mapping.bottomRight){
                            mapping.top = str[j];
                            memcpy(sequences.seven, str, 8);
                            break;
                        }
                    }
                }

                if(sequenceLength == 4){
                    if(strlen(sequences.four) == 0){
                        memcpy(sequences.four, str, 8);
                    } else {
                        if(mapping.middle != 0){
                            for(int j = 0; j < 4; j++){
                                if(sequences.four[j] != mapping.middle && sequences.four[j] != mapping.topRight &&
                                   sequences.four[j] != mapping.bottomRight){
                                    mapping.topLeft = sequences.four[j];
                                }
                            }
                        }
                    }
                }

                if(sequenceLength == 6){
                    if(strlen(sequences.zero) == 0){
                        memcpy(sequences.zero, str, 8);
                    } else if(strlen(sequences.six) == 0){
                        memcpy(sequences.six, str, 8);
                    } else if(strlen(sequences.nine) == 0){
                        memcpy(sequences.nine, str, 8);
                    }

                    if(strlen(sequences.four) != 0 && mapping.topRight != 0 && mapping.bottomRight != 0){
                        for(int j = 0; j < 4; j++){
                            if(sequences.four[j] != mapping.topRight && sequences.four[j] != mapping.bottomRight){
                                bool isInSequenceZero = false;
                                bool isInSequenceSix = false;
                                bool isInSequenceNine = false;

                                for(int k = 0; k < 6; k++){
                                    if(sequences.four[j] == sequences.zero[k]){
                                        isInSequenceZero = true;
                                    }

                                    if(sequences.four[j] == sequences.six[k]){
                                        isInSequenceSix = true;
                                    }

                                    if(sequences.four[j] == sequences.nine[k]){
                                        isInSequenceNine = true;
                                    }
                                }

                                if(!isInSequenceSix){
                                    swapArrays(sequences.zero, sequences.six);
                                }

                                if(!isInSequenceNine){
                                    swapArrays(sequences.zero, sequences.nine);
                                }

                                if(!isInSequenceZero || !isInSequenceSix || !isInSequenceNine){
                                    mapping.middle = sequences.four[j];
                                    break;
                                }
                            }
                        }
                    }

                    if(strlen(sequences.six) != 0 && strlen(sequences.nine) != 0 &&
                       mapping.topRight != 0 && mapping.bottomRight != 0 && mapping.middle != 0){
                        bool isTopRightInSequenceNine = false;
                        bool isBottomRightInSequenceSix = false;
                        bool isBottomRightInSequenceNine = false;

                        for(int j = 0; j < 6; j++){
                            if(sequences.six[j] == mapping.bottomRight) isBottomRightInSequenceSix = true;
                            if(sequences.nine[j] == mapping.topRight) isTopRightInSequenceNine = true;
                            if(sequences.nine[j] == mapping.bottomRight) isBottomRightInSequenceNine = true;
                        }

                        if(!isBottomRightInSequenceSix || !isBottomRightInSequenceNine){
                            char temp = mapping.bottomRight;
                            mapping.bottomRight = mapping.topRight;
                            mapping.topRight = temp;
                        }

                        if(!isBottomRightInSequenceNine || !isTopRightInSequenceNine){
                            swapArrays(sequences.six, sequences.nine);
                        }
                    }

                    if(strlen(sequences.nine) != 0 && mapping.topLeft != 0 && mapping.top != 0 &&
                       mapping.topRight != 0 && mapping.middle != 0 && mapping.bottomRight != 0){
                        for(int j = 0; j < 6; j++){
                            if(sequences.nine[j] != mapping.topLeft && sequences.nine[j] != mapping.top &&
                               sequences.nine[j] != mapping.topRight && sequences.nine[j] != mapping.middle &&
                               sequences.nine[j] != mapping.bottomRight){
                                mapping.bottom = sequences.nine[j];
                                break;
                            }
                        }
                    }
                }

                if(sequenceLength == 7){
                    if(strlen(sequences.eight) == 0){
                        memcpy(sequences.eight, str, 8);
                    } else {
                        if(mapping.topLeft != 0 && mapping.top != 0 && mapping.topRight &&
                           mapping.middle != 0 && mapping.bottomRight != 0 && mapping.bottom != 0){
                            for(int j = 0; j < 7; j++){
                                if(sequences.eight[j] != mapping.topLeft && sequences.eight[j] != mapping.top &&
                                   sequences.eight[j] != mapping.topRight && sequences.eight[j] != mapping.middle &&
                                   sequences.eight[j] != mapping.bottomRight && sequences.eight[j] != mapping.bottom){
                                    mapping.bottomLeft = sequences.eight[j];
                                    break;
                                }
                            }
                        }
                    }
                }

                emptyArray(str);
            }
        }
    }

    int digits[4] = {0, 0, 0, 0};

    computeDigits(digits, mapping, string);

    int result = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];

    return result;
}

void computeDigits(int digits[4], const struct mapping mapping, const char string[100]) {
    bool isInSequence = false;
    char str[8] = "";
    int currDigit = 0;

    for(int i = 61; i <= strlen(string); i++) {
        if (string[i] == '\r') {
            break;
        }

        isInSequence = string[i] != ' ' && string[i] != '\0' && string[i] != '\n';
        if(isInSequence){
            char temp[1] = {string[i]};
            strncat(str, temp, 1);
        } else {
            if(strlen(str) == 2) digits[currDigit] = 1;
            if(strlen(str) == 3) digits[currDigit] = 7;
            if(strlen(str) == 4) digits[currDigit] = 4;
            if(strlen(str) == 7) digits[currDigit] = 8;

            if(strlen(str) == 5 && isTwo(str, mapping)) digits[currDigit] = 2;
            if(strlen(str) == 5 && isThree(str, mapping)) digits[currDigit] = 3;
            if(strlen(str) == 5 && isFive(str, mapping)) digits[currDigit] = 5;

            if(strlen(str) == 6 && isZero(str, mapping)) digits[currDigit] = 0;
            if(strlen(str) == 6 && isSix(str, mapping)) digits[currDigit] = 6;
            if(strlen(str) == 6 && isNine(str, mapping)) digits[currDigit] = 9;

            memset(str, 0, 8);
            currDigit++;
        }
    }
}

bool isMappingComplete(const struct mapping mapping){
    return mapping.top != 0 && mapping.topLeft != 0 && mapping.topRight != 0 && mapping.middle != 0 &&
           mapping.bottom != 0 && mapping.bottomLeft != 0 && mapping.bottomRight != 0;
}

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

bool isTwo(const char string[8], const struct mapping mapping){
    for(int i = 0; i < 5; i++){
        if(string[i] != mapping.top && string[i] != mapping.topRight && string[i] != mapping.middle &&
           string[i] != mapping.bottomLeft && string[i] != mapping.bottom){
            return false;
        }
    }

    return true;
}

bool isThree(const char string[8], const struct mapping mapping){
    for(int i = 0; i < 5; i++){
        if(string[i] != mapping.top && string[i] != mapping.topRight && string[i] != mapping.middle &&
           string[i] != mapping.bottomRight && string[i] != mapping.bottom){
            return false;
        }
    }

    return true;
}


bool isFive(const char string[8], const struct mapping mapping){
    for(int i = 0; i < 5; i++){
        if(string[i] != mapping.top && string[i] != mapping.topLeft && string[i] != mapping.middle &&
           string[i] != mapping.bottomRight && string[i] != mapping.bottom){
            return false;
        }
    }

    return true;
}

bool isZero(const char string[8], const struct mapping mapping){
    for(int i = 0; i < 6; i++){
        if(string[i] != mapping.top && string[i] != mapping.topLeft && string[i] != mapping.topRight &&
           string[i] != mapping.bottomLeft && string[i] != mapping.bottom && string[i] != mapping.bottomRight){
            return false;
        }
    }

    return true;
}

bool isSix(const char string[8], const struct mapping mapping){
    for(int i = 0; i < 6; i++){
        if(string[i] != mapping.top && string[i] != mapping.topLeft && string[i] != mapping.middle &&
           string[i] != mapping.bottomLeft && string[i] != mapping.bottom && string[i] != mapping.bottomRight){
            return false;
        }
    }

    return true;
}

bool isNine(const char string[8], const struct mapping mapping){
    for(int i = 0; i < 6; i++){
        if(string[i] != mapping.top && string[i] != mapping.topLeft && string[i] != mapping.topRight &&
           string[i] != mapping.middle && string[i] != mapping.bottom && string[i] != mapping.bottomRight){
            return false;
        }
    }

    return true;
}
