
struct mapping{
    char top, topLeft, topRight, middle,
            bottom, bottomLeft, bottomRight;
};

struct sequences{
    char zero[8], one[8], four[8], six[8], seven[8], eight[8], nine[8];
};

int calculateEntry(const char string[100]);
bool isMappingComplete(struct mapping mapping);
void emptyArray(char array[100]);
void swapArrays(char arr1[8], char arr2[8]);
void computeDigits(int digits[4], struct mapping mapping, const char string[100]);
bool isTwo(const char string[8], struct mapping mapping);
bool isThree(const char string[8], struct mapping mapping);
bool isFive(const char string[8], struct mapping mapping);
bool isZero(const char string[8], struct mapping mapping);
bool isSix(const char string[8], struct mapping mapping);
bool isNine(const char string[8], struct mapping mapping);
