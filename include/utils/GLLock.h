#ifndef UTILS_GLLOCK_H
#define UTILS_GLLOCK_H
class GLLock
{
    public:
        GLLock();
        ~GLLock();
        void lock();
        void unlock();
    private:
        void* mData;
};
class GLAutoLock
{
    public:
        GLAutoLock(GLLock& l):mL(l)
        {
            mL.lock();
        }
        ~GLAutoLock()
        {
            mL.unlock();
        }
    private:
        GLLock& mL;
};
#endif
