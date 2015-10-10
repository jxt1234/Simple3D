#include "user/GPAPI.h"
#include "utils/debug.h"
#include <assert.h>
#include "package/DefaultFunctionTable.h"
int test_main()
{
    DefaultFunctionTable table;
    IFunctionTable* tablelist[] = {&table};
    auto metaStream = GP_Stream_Create("DefaultFunctionTable.xml");
    auto producer = GP_Producer_Create(&metaStream, tablelist, 1, 0);
    GP_Stream_Destroy(metaStream);
    {
        auto bestf = GP_Function_Create_ByType(producer,  "GLBmp", "GLBmp");
        auto fitf = GP_Function_Create_ByType(producer,  "double", "GLBmp GLBmp");
        auto inputs = GP_Stream_Create("input.jpg");
        auto contents = GP_Contents_Load(producer, &inputs, "GLBmp", 1);
        GP_Stream_Destroy(inputs);
        auto target = GP_Stream_Create("test_saturation.jpg");
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
        GP_Function_Optimize(bestf, fitfunction, 0, "time=1000");
        FUNC_PRINT_ALL(fitfunction(bestf), f);
        {
            auto output = GP_WStream_Create("output/GPTestBest.xml");
            GP_Function_Save(bestf, output);
            GP_WStream_Destroy(output);
        }
        {
            auto outputbmp = GP_Function_Run(bestf, contents);
            auto wstream = GP_WStream_Create("output/GPOutputBmp.png");
            GP_Contents_Save(outputbmp, &wstream, 1);
            GP_WStream_Destroy(wstream);
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

int main()
{
    GP_Set_Stream_Path("/Users/jiangxiaotang/Documents/Simple3D/");
    return test_main();
}
