#include <stdbool.h>
#include <stdarg.h>
#include "checks.h"

bool mapExists(int numOfArgs, ...){
    bool result = true;

    va_list vaList;
    va_start(vaList, numOfArgs);

    for(int i = 0; i < numOfArgs; i++){
        char currChar = va_arg(vaList, int);
        result = result && currChar != 0;
    }

    va_end(vaList);

    return result;
}

bool charNotInMap(char charToCompare, int numOfArgs, ...){
    bool result = true;

    va_list vaList;
    va_start(vaList, numOfArgs);

    for(int i = 0; i < numOfArgs; i++){
        char mappingChar = va_arg(vaList, int);
        result = result && mappingChar != charToCompare;
    }

    va_end(vaList);

    return result;
}

bool isMappingComplete(struct mapping map){
    return mapExists(7, map.top, map.topL, map.topR, map.mid, map.bot, map.botL, map.botR);
}

bool isInSeq(const char c){
    return c != ' ' && c != '\0' && c != '\n';
}

bool is2(const char string[8], const struct mapping map){
    for(int i = 0; i < 5; i++){
        if(charNotInMap(string[i], 5, map.top, map.topR, map.mid, map.botL, map.bot)){
            return false;
        }
    }

    return true;
}

bool is3(const char string[8], const struct mapping map){
    for(int i = 0; i < 5; i++){
        if(charNotInMap(string[i], 5, map.top, map.topR, map.mid, map.botR, map.bot)){
            return false;
        }
    }

    return true;
}


bool is5(const char string[8], const struct mapping map){
    for(int i = 0; i < 5; i++){
        if(charNotInMap(string[i], 5, map.top, map.topL, map.mid, map.botR, map.bot)){
            return false;
        }
    }

    return true;
}

bool is0(const char string[8], const struct mapping map){
    for(int i = 0; i < 6; i++){
        if(charNotInMap(string[i], 6, map.top, map.topL, map.topR, map.botL, map.bot, map.botR)){
            return false;
        }
    }

    return true;
}

bool is6(const char string[8], const struct mapping map){
    for(int i = 0; i < 6; i++){
        if(charNotInMap(string[i], 6, map.top, map.topL, map.mid, map.botL, map.bot, map.botR)){
            return false;
        }
    }

    return true;
}

bool is9(const char string[8], const struct mapping map){
    for(int i = 0; i < 6; i++){
        if(charNotInMap(string[i], 6, map.top, map.topL, map.topR, map.mid, map.bot, map.botR)){
            return false;
        }
    }

    return true;
}
