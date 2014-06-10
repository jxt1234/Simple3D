//SceneNewton.h  牛顿法解方程的迭代混沌
#ifndef __SceneNewton_H_
#define __SceneNewton_H_

#include "ColorMover.h"
#include <vector>
#include "interface/GLColor.h"
#include "interface/IBitmap.h"

#define Scene_Update_RAND_NUM 12


class CSceneNewton
{
protected:
    CColorMover     m_ColorMover;
    double          m_ColorK1;
    double          m_ColorK2;
    double          m_ColorK3;
    long            m_UpdateTime;
    bool            m_IsExtract3Ex;
    long            m_ExtractNumber;
    bool            m_isTanRev;
    long            m_iteratInc;

    must_inline GLColor getColor(const double dL1,const double dL2,const double dL3);
    void DoDraw(IBitmap& dst);
    void Inti();
public:
    void Scene_Inti(long ScreenWidth,long ScreenHeight) { Scene_Clear(); Inti(); }
    void Scene_Clear();
    void Scene_Update(unsigned long StepTime_ms, int* randList, int* randListColor);
    void Scene_Draw(IBitmap& dst) { DoDraw(dst); }
    ~CSceneNewton(){}
};



#endif //__SceneNewton_H_
