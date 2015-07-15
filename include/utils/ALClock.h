#ifndef INCLUDE_UTILS_ALCLOCK_H
#define INCLUDE_UTILS_ALCLOCK_H
#include <time.h>
#include <string>
class ALClock
{
    public:
        ALClock(const char* name, int line)
        {
            mName = name;
            mLine = line;
            mSta = clock();
        }
        ~ALClock()
        {
            clock_t fin = clock();
            printf("For %s, %d Time is %lu\n", mName.c_str(), mLine, fin-mSta);
        }
    private:
        std::string mName;
        int mLine;
        clock_t mSta;
};
#define ALAUTOTIME ALClock __alclock(__func__, __LINE__)
#endif
