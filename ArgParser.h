#ifndef ARK_PARSER_H
#define ARK_PARSER_H

#include <string.h>

struct FlagStorage
{
    bool releaseEnabled;
    bool testsEnabled;
    bool colourEnabled;
    const char* inputFileName;
    const char* outputFileName;
};

typedef void (*FlagFunc)(FlagStorage* storage, const char* argv);

struct ConsoleFlag
{
    const char name[30];
    const char short_name[5];
    FlagFunc flag_func; //   без typedef-a: void (*flag_func)(FlagStorage*);
    bool isArg;
};

void getFlags(int argc, const char* argv[], const ConsoleFlag* list_flags,
              size_t count_flags, FlagStorage* storage);
void setRelease(FlagStorage* storage, const char* argv);
void setUnitTests(FlagStorage* storage, const char* argv);
void inputFileEnable(FlagStorage* storage, const char* argv);
void outputFileEnable(FlagStorage* storage, const char* argv);
bool testValid(const FlagStorage* storage);


#endif // ARK_PARSER_H
