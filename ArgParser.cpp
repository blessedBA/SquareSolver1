#include "ArgParser.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void getFlags(const int argc, const char* argv[],
              const ConsoleFlag* list_flags,
              const size_t count_flags,
              FlagStorage* storage)
{
    // TODO asserts
    assert(storage != nullptr);
    assert(&list_flags != NULL);
    for (int i = 1; i < argc; i++)
    {
        for (size_t j = 0; j < count_flags; j++)
        {
            if (strcmp(argv[i], list_flags[j].name) == 0 ||
                strcmp(argv[i], list_flags[j].short_name) == 0)
            {
                if (list_flags[j].isArg)
                {
                    if (i + 1 >= argc)
                    {
                        printf("invalid argument!!!\n");
                        return;
                    }
                     list_flags[j].flag_func(storage, argv[i+1]);
                }
                else
                {
                    list_flags[j].flag_func(storage, NULL);
                }
            }
        }
    }
}

void setRelease(FlagStorage* storage, const char* /* arg */)
{
    storage->releaseEnabled = true;
}
void setUnitTests(FlagStorage* storage, const char* /* arg */)
{
    storage->testsEnabled = true;
}

void inputFileEnable(FlagStorage* storage, const char* arg)
{
    storage->inputFileName = arg;
}

void outputFileEnable(FlagStorage* storage, const char* arg)
{
    storage->outputFileName = arg;
}

bool testValid(const FlagStorage* storage)
{
    bool indicator = true;
    if (storage->releaseEnabled == true &&
        storage->testsEnabled == true)
    {
        indicator = false;
        printf("please, enter just one mode!!!\n");
    }
    if (storage->releaseEnabled == false &&
        storage->testsEnabled == false)
    {
        indicator = false;
    }
    return indicator;
}

