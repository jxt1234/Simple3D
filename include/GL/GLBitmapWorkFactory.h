#include "GLBitmapWork.h"
#include <istream>
#include <map>
class GLBitmapWorkCreater
{
    public:
        //Create BitmapWork
        virtual GLBitmapWork* vCreate(std::istream* input) const = 0;
        //Give Detail for how to set input
        virtual void vDetail(std::ostream& os) const{}

        GLBitmapWorkCreater(){}
        virtual ~GLBitmapWorkCreater(){}
};


class GLBitmapWorkFactory
{
    public:
        //For User
        static GLBitmapWork* create(const char* name, std::istream* input=NULL);
        static void printMethods(std::ostream& os);

        //For GLBitmapWorkCreatorRegister
        void insert(GLBitmapWorkCreater* c, const std::string& s);
        static GLBitmapWorkFactory& get();
    private:
        GLBitmapWork* _create(const char* name, std::istream* input);
        GLBitmapWorkFactory();
        ~GLBitmapWorkFactory();
        static GLBitmapWorkFactory* gFactory;
        typedef std::map<std::string, GLBitmapWorkCreater*> CREATERS;
        CREATERS mCreator;
};
template <class T>
class GLBitmapWorkCreatorRegister
{
    public:
        GLBitmapWorkCreatorRegister(const char* claim)
        {
            T* test = new T;
            GLBitmapWorkFactory& ts = GLBitmapWorkFactory::get();
            std::string s(claim);
            ts.insert(test, s);
        }
        ~GLBitmapWorkCreatorRegister(){}
};
