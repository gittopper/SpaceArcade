//
//  glesspacegamerenderer.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#include "glesspacegamerenderer.h"
#include "gamemath.h"
#include "gameobjects.h"

using namespace Math;

namespace Game
{
    void GLESSpaceGameRenderer::visit(IObject& a)
    {
        drawGameObject(a);
    }
    
    void GLESSpaceGameRenderer::drawGameObject(IObject& obj) const
    {
        setPosition(obj.getTransform(), obj.getShift());
        drawArray(obj.getDrawPoints(),obj.getColors());
    }
    void GLESSpaceGameRenderer::setPosition(const Mat& m, const Vector& v) const
    {
        
        Mat44 objMat;
        convertTo44(objMat, m, v);
        
        Mat44 mvp;
        Mul(mvp, objMat, proj);
        
        
        glUniformMatrix4fv(u_mvpHandle, 1, GL_FALSE, (GLfloat*)&mvp.m[0] );
   
    }
    void GLESSpaceGameRenderer::drawArray(VArray& points, V4Array& colors) const
    {
        glVertexAttribPointer(a_positionHandle, 3, GL_FLOAT, GL_FALSE, 0, getFloatPointer(points));
        glEnableVertexAttribArray(a_positionHandle);
        glVertexAttribPointer(a_colorHandle, 4, GL_FLOAT, GL_FALSE, 0, getFloatPointer(colors));
        glEnableVertexAttribArray(a_colorHandle);
        glDrawArrays(GL_TRIANGLE_FAN, 0, (int) points.size());
    }
}
