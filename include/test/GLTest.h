#ifndef TEST_GLTEST_H
#define TEST_GLTEST_H

#include <vector>
#include <string>

class GLTest
{
    friend class GLTestSuit;
    public:
        virtual void run()=0;
        GLTest(){}
        virtual ~GLTest(){}
    private:
        std::string name;
};

class GLTestSuit
{
    public:
        static void run();
        static GLTestSuit* get();
        void insert(GLTest* t, const char* name);
        //
        GLTestSuit(){}
        ~GLTestSuit();
    private:
        static GLTestSuit* global;
        std::vector<GLTest*> mTests;
};

template <class T>
class GLTestRegister
{
    public:
        GLTestRegister(const char* claim)
        {
            T* test = new T;
            GLTestSuit* ts = GLTestSuit::get();
            ts->insert(test, claim);
        }
        ~GLTestRegister(){}
};
#endif
