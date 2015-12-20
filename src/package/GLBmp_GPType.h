class GLBmp_GPType:public IStatusType
{
    public:
        GLBmp_GPType():IStatusType("GLBmp"){}
        virtual void* vLoad(GPStream* input) const
        {
            size_t totalsize = 0;
            const size_t size = 4096;
            char* current = new char[size];
            char* total = NULL;
            while (!input->isEnd())
            {
                size_t reads = input->read(current, size);
                char* toread = NULL;
                if (NULL == total)
                {
                    total = new char[reads];
                    toread = total;
                }
                else
                {
                    char* swapbuffer = new char[totalsize+reads];
                    ::memcpy(swapbuffer, total, sizeof(char)*totalsize);
                    toread = swapbuffer + totalsize;
                    delete [] total;
                    total = swapbuffer;
                }
                ::memcpy(toread, current, reads);
                totalsize+=reads;
            }
            delete [] current;
            GLBmp* newbmp = new GLBmp((unsigned char*)total, totalsize);
            delete [] total;
            return newbmp;
        }
        virtual void vSave(void* contents, GPWStream* output) const
        {
        }
        virtual void vFree(void* contents) const
        {
            GLBmp* c = (GLBmp*)contents;
            c->decRef();
        }
        virtual int vMap(void** content, double* value) const
        {
            int mapnumber=0;
            if (NULL == value || NULL == content)
            {
                return mapnumber;
            }
            if (NULL == *content)
            {
            }
            return mapnumber;
        }
};
