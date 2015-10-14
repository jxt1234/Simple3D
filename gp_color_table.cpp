#include "user/GPAPI.h"
#include "utils/debug.h"
#include <assert.h>
#include "package/DefaultFunctionTable.h"
#include "utils/GP_Clock.h"
#include "core/GLBmp.h"
int test_main(const char* input_bitmap, const char* target_bitmap)
{
    DefaultFunctionTable table;
    IFunctionTable* tablelist[] = {&table};
    auto metaStream = GP_Stream_Create("DefaultFunctionTable.xml");
    auto producer = GP_Producer_Create(&metaStream, tablelist, 1, 0);
    GP_Stream_Destroy(metaStream);
    {
        auto bestf = GP_Function_Create_ByType(producer,  "GLBmp", "GLBmp");
        auto fitf = GP_Function_Create_ByType(producer,  "double", "GLBmp GLBmp");
        auto inputs = GP_Stream_Create(input_bitmap);
        auto contents = GP_Contents_Load(producer, &inputs, "GLBmp", 1);
        GP_Stream_Destroy(inputs);
        auto target = GP_Stream_Create(target_bitmap);
        auto targetBmp = GP_Contents_Load(producer, &target, "GLBmp", 1);
        GP_Stream_Destroy(target);
        auto fitfunction = [&](IGPAutoDefFunction* f){
            auto outputbmp = GP_Function_Run(f, contents);
            GPContents forcompute;
            forcompute.push(outputbmp->getContent(0));
            forcompute.push(targetBmp->getContent(0));
            auto double_result = GP_Function_Run(fitf, &forcompute);
            double result = *(double*)(double_result->get(0));
            GP_Contents_Destroy(double_result);
            GP_Contents_Destroy(outputbmp);
            return result;
        };
        GP_Function_Optimize(bestf, fitfunction, 0, "time=100000");
        FUNC_PRINT_ALL(fitfunction(bestf), f);
        {
            auto output = GP_WStream_Create("output/GPTestBest.xml");
            GP_Function_Save(bestf, output);
            GP_WStream_Destroy(output);
        }
        {
            auto outputbmp = GP_Function_Run(bestf, contents);
            GLBmp* _outputbmp = (GLBmp*)(outputbmp->get(0));
            _outputbmp->save("output/gp_result.png");
            GP_Contents_Destroy(outputbmp);
        }
        GP_Contents_Destroy(contents);
        GP_Contents_Destroy(targetBmp);
        GP_Function_Destroy(fitf);
        GP_Function_Destroy(bestf);
    }
    GP_Producer_Destroy(producer);
    return 1;
}

int main(int argc, char* argv[])
{
    GLASSERT(argc>=3);
    //GP_Set_Stream_Path("/Users/jiangxiaotang/Documents/Simple3D/");
    return test_main(argv[1],argv[2]);
}
