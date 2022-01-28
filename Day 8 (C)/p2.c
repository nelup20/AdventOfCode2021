#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "checks.h"
#include "utility.h"
#include "p2.h"

// Ended up refactoring immediately after the previous commit... (sleep deprivation & Katana Zero OST = ♥)
// There are probably some improvements left, but I'm satisfied for now. Might be less readable due to the naming
// (ex: mapping --> map, sequence --> seq etc.), but by knowing the context I'd say it's more readable.

// I desperately need to resume reading the K&R book, I stopped @ around page 15, and it shows... I barely know C.

// One thing I haven't figured out is why the \n at the beginning of each string messed up the calculation of the digits.
// As in every line/string that contained a \n at the beginning would turn the 1st digit to 0, but that shouldn't be
// the case since I'm skipping \n. But anyways that's why I do a memcpy() for newStr (and the input.txt needs a new line at the end).
// Also, CLion's debugger isn't as intuitive as I hoped.

// I'll also add an explanation of how the algo generally works tomorrow.

int main() {
    char c;
    FILE *file;
    char line[100] = "";
    char newStr[100] = "";
    int finalResult = 0;

    file = fopen("../input.txt", "r");
    if(file){
        while((c = getc(file)) != EOF){
            if(c == '\r'){
                if(line[0] == '\n'){
                    memcpy(newStr, line + 1, 100);
                    finalResult += calculateEntry(newStr);
                } else {
                    finalResult += calculateEntry(line);
                }
                emptyArray(line);
                continue;
            } else {
                appendChar(line, c);
            }
        }

        fclose(file);
    }

    printf("Result: %d", finalResult);

    return 0;
}

int calculateEntry(const char line[100]){
    struct mapping map = {0, 0, 0, 0, 0, 0, 0};
    struct sequences seq = {"", "", "", "", "", "", ""};

    while(!isMappingComplete(map)){
        char str[8] = "";

        bool isInSeq = false;

        for(int i = 0; i < 100; i++){
            if(line[i] == '|' || line[i] == '\r') break;
            if(line[i] == '\n') continue;

            isInSeq = line[i] != ' ';

            if(isInSeq){
                appendChar(str, line[i]);
            } else {
                int seqLength = strlen(str);
                if(seqLength == 2 && !mapExists(2, map.topR, map.botR)){
                    map.topR = str[0];
                    map.botR = str[1];
                    memcpy(seq.one, str, 8);
                }

                if(seqLength == 3 && mapExists(2, map.topR, map.botR) &&
                   !mapExists(1, map.top)){

                    for(int j = 0; j < 3; j++){
                        if(charNotInMap(str[j], 2, map.topR, map.botR)){
                            map.top = str[j];
                            memcpy(seq.seven, str, 8);
                            break;
                        }
                    }
                }

                if(seqLength == 4){
                    if(strlen(seq.four) == 0){
                        memcpy(seq.four, str, 8);
                    } else {
                        if(map.mid != 0){
                            for(int j = 0; j < 4; j++){
                                if(charNotInMap(seq.four[j], 3, map.mid, map.topR, map.botR)){
                                    map.topL = seq.four[j];
                                }
                            }
                        }
                    }
                }

                if(seqLength == 6){
                    if(strlen(seq.zero) == 0){
                        memcpy(seq.zero, str, 8);
                    } else if(strlen(seq.six) == 0){
                        memcpy(seq.six, str, 8);
                    } else if(strlen(seq.nine) == 0){
                        memcpy(seq.nine, str, 8);
                    }

                    if(strlen(seq.four) != 0 && mapExists(2, map.topR, map.botR)){
                        for(int j = 0; j < 4; j++){
                            if(charNotInMap(seq.four[j], 2, map.topR, map.botR)){
                                bool isInSeqZero = false;
                                bool isInSeqSix = false;
                                bool isInSeqNine = false;

                                for(int k = 0; k < 6; k++){
                                    if(seq.four[j] == seq.zero[k]){
                                        isInSeqZero = true;
                                    }

                                    if(seq.four[j] == seq.six[k]){
                                        isInSeqSix = true;
                                    }

                                    if(seq.four[j] == seq.nine[k]){
                                        isInSeqNine = true;
                                    }
                                }

                                if(!isInSeqSix){
                                    swapArrays(seq.zero, seq.six);
                                }

                                if(!isInSeqNine){
                                    swapArrays(seq.zero, seq.nine);
                                }

                                if(!isInSeqZero || !isInSeqSix || !isInSeqNine){
                                    map.mid = seq.four[j];
                                    break;
                                }
                            }
                        }
                    }

                    if(strlen(seq.six) != 0 && strlen(seq.nine) != 0 &&
                       mapExists(3, map.topR, map.botR, map.mid)){
                        bool isTopRInSeqNine = false;
                        bool isBotRInSeqSix = false;
                        bool isBotRInSeqNine = false;

                        for(int j = 0; j < 6; j++){
                            if(seq.six[j] == map.botR) isBotRInSeqSix = true;
                            if(seq.nine[j] == map.topR) isTopRInSeqNine = true;
                            if(seq.nine[j] == map.botR) isBotRInSeqNine = true;
                        }

                        if(!isBotRInSeqSix || !isBotRInSeqNine){
                            char temp = map.botR;
                            map.botR = map.topR;
                            map.topR = temp;
                        }

                        if(!isBotRInSeqNine || !isTopRInSeqNine){
                            swapArrays(seq.six, seq.nine);
                        }
                    }

                    if(strlen(seq.nine) != 0 && mapExists(5, map.topL, map.top, map.topR, map.mid, map.botR)){
                        for(int j = 0; j < 6; j++){
                            if(charNotInMap(seq.nine[j], 5, map.topL, map.top, map.topR, map.mid, map.botR)){
                                map.bot = seq.nine[j];
                                break;
                            }
                        }
                    }
                }

                if(seqLength == 7){
                    if(strlen(seq.eight) == 0){
                        memcpy(seq.eight, str, 8);
                    } else {
                        if(mapExists(6, map.topL, map.top, map.topR, map.mid, map.botR, map.bot)){
                            for(int j = 0; j < 7; j++){
                                if(charNotInMap(seq.eight[j], 6, map.topL, map.top, map.topR, map.mid, map.botR, map.bot)){
                                    map.botL = seq.eight[j];
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

    computeDigits(digits, map, line);

    int result = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];

    return result;
}

void computeDigits(int digits[4], const struct mapping map, const char line[100]) {
    bool isInSeq = false;
    char str[8] = "";
    int currDigit = 0;

    for(int i = 61; i <= strlen(line); i++) {
        if (line[i] == '\r') {
            break;
        }

        isInSeq = line[i] != ' ' && line[i] != '\0' && line[i] != '\n';
        if(isInSeq){
            appendChar(str, line[i]);
        } else {
            if(strlen(str) == 2) digits[currDigit] = 1;
            if(strlen(str) == 3) digits[currDigit] = 7;
            if(strlen(str) == 4) digits[currDigit] = 4;
            if(strlen(str) == 7) digits[currDigit] = 8;

            if(strlen(str) == 5 && is2(str, map)) digits[currDigit] = 2;
            if(strlen(str) == 5 && is3(str, map)) digits[currDigit] = 3;
            if(strlen(str) == 5 && is5(str, map)) digits[currDigit] = 5;

            if(strlen(str) == 6 && is0(str, map)) digits[currDigit] = 0;
            if(strlen(str) == 6 && is6(str, map)) digits[currDigit] = 6;
            if(strlen(str) == 6 && is9(str, map)) digits[currDigit] = 9;

            memset(str, 0, 8);
            currDigit++;
        }
    }
}