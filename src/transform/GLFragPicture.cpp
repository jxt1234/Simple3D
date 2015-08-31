#include "transform/GLFragPicture.h"
#include "SceneNewton.h"

void GLGenFragPicNewTon(IBitmap& bitmap)
{
    int scenelist[Scene_Update_RAND_NUM];
    int colorlist[ColorMover_RAND_NUM];
    for (int i=0; i<Scene_Update_RAND_NUM; ++i)
    {
        scenelist[i] = rand();
    }
    for (int i=0; i<ColorMover_RAND_NUM; ++i)
    {
        colorlist[i] = rand();
    }
    int width = bitmap.width();
    int height = bitmap.height();
    CSceneNewton scene;
    scene.Scene_Inti(width, height);
    scene.Scene_Update(0, scenelist, colorlist);
    scene.Scene_Draw(bitmap);
    scene.Scene_Clear();
}

