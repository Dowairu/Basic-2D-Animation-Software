#include <iostream>
#include <ngl/VAOFactory.h>
#include "Shape.h"

/// @file Shape.cpp
/// @brief implementation files for Shape class

void Shape::setShape(size_t _numVerts,const std::string& _shapeName,ngl::Transformation& _shapeTransform,ngl::Vec3& _pivotPos,RGBA& _colour,std::vector<ngl::Vec3>& _vertPos)
{
    m_vertexPositions = _vertPos;
    m_shapeName = _shapeName;
    m_shapeTransform = _shapeTransform;
    m_pivotPos = _pivotPos;
    m_colour = _colour.convertToVec4();
    m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_TRIANGLES);

}
void Shape::setDefaultTriangle()
{
    std::string name = "Triangle";
    ngl::Transformation trans;
    trans.setPosition(0.0f,0.0f,0.0f);
    trans.setRotation(0.0f,0.0f,0.0f);
    trans.setScale(0.5f,0.5f,0.5f);
    RGBA triDef(128,255,40,255);
    ngl::Vec3 pivot(0.0f,0.0f,0.0f);
    std::vector<ngl::Vec3> verts;
    ngl::Vec3 vert1(0.5f,0.0f,0.0f);
    ngl::Vec3 vert2(0.0f,1.0f,0.0f);
    ngl::Vec3 vert3(-0.5f,0.0f,0.0f);
    verts =  {vert1,vert2,vert3};
    setShape(verts.size(),name,trans,pivot,triDef,verts);
}

void Shape::setDefaultQuad()
{
    std::string name = "Rectangle";
    ngl::Transformation trans;
    trans.setPosition(0.0f,0.0f,0.0f);
    trans.setRotation(0.0f,0.0f,0.0f);
    trans.setScale(1.0f,1.0f,1.0f);
    RGBA quadDef(255,128,25,255);
    ngl::Vec3 pivot(0.0f,0.0f,0.0f);
    std::vector<ngl::Vec3> verts;
    ngl::Vec3 vert1(0.5f,0.0f,0.0f);//bottom left
    ngl::Vec3 vert2(-0.5f,0.0f,0.0f);//bottom right
    ngl::Vec3 vert3(-0.5f,1.0f,0.0f);//top right
    ngl::Vec3 vert4(-0.5f,1.0f,0.0f);//top right
    ngl::Vec3 vert5(0.5f,1.0f,0.0f);//top left
    ngl::Vec3 vert6(0.5f,0.0f,0.0f);//bottom left
    verts =  {vert1,vert2,vert3,vert4,vert5,vert6};
    setShape(verts.size(),name,trans,pivot,quadDef,verts);
    
}

//void Shape::setDefaultCircle()
//{
//    std::string name = "Circle";
//    ngl::Transformation trans;
//    trans.setPosition(0.0f,0.0f,0.0f);
//    trans.setRotation(0.0f,0.0f,0.0f);
//    trans.setScale(1.0f,1.0f,1.0f);
//    RGBA circDef(255,128,25,255);
//    ngl::Vec3 pivot(0.0f,0.0f,0.0f);
//    std::vector<ngl::Vec3> verts;
//    ngl::Vec3 vert1(0.5f,0.0f,0.0f);//bottom left
//    ngl::Vec3 vert2(-0.5f,0.0f,0.0f);//bottom right
//    ngl::Vec3 vert3(-0.5f,1.0f,0.0f);//top right
//    ngl::Vec3 vert4(-0.5f,1.0f,0.0f);//top right
//    ngl::Vec3 vert5(0.5f,1.0f,0.0f);//top left
//    ngl::Vec3 vert6(0.5f,0.0f,0.0f);//bottom left
//    verts =  {vert1,vert2,vert3,vert4,vert5,vert6};
//    setShape(verts.size(),name,trans,pivot,circDef,verts);

//}

void Shape::setPosition(ngl::Vec3& _v)
{
    m_shapeTransform.setPosition(_v);
}

void Shape::setPositionX(double _x)
{
    auto Posx = m_shapeTransform.getPosition();
    Posx = (ngl::Real)_x;

}

void Shape::setPositionY(double _y)
{
    auto Posy = m_shapeTransform.getPosition();
    Posy.m_y = (ngl::Real)_y;

}
void Shape::setPositionZ(double _z)
{
    auto Posz = m_shapeTransform.getPosition();
    Posz.m_z = (ngl::Real)_z;

}
void Shape::setScale(ngl::Vec3& _v)
{
    m_shapeTransform.setScale(_v);
}

void Shape::setScaleX(double _x)
{
    auto Scalex = m_shapeTransform.getScale();
    Scalex.m_x = (ngl::Real)_x;

}

void Shape::setScaleY(double _y)
{
    auto Scaley = m_shapeTransform.getScale();
    Scaley.m_y = (ngl::Real)_y;

}

void Shape::setScaleZ(double _z)
{
    auto Scalez = m_shapeTransform.getScale();
    Scalez.m_z = (ngl::Real)_z;

}

std::vector<Keyframe> Shape::getKeyframeList()
{
      return m_keyframes;
}

void Shape::setRotation(ngl::Vec3& _v)
{
    m_shapeTransform.setRotation(_v);
}

void Shape::setRotationX(double _x)
{
    auto Rotx = m_shapeTransform.getRotation();
    Rotx.m_x = (ngl::Real)_x;

}

void Shape::setRotationY(double _y)
{
    auto Roty = m_shapeTransform.getRotation();
    Roty.m_y = (ngl::Real)_y;

}
void Shape::setRotationZ(double _z)
{
    auto Rotz = m_shapeTransform.getRotation();
    Rotz.m_z = (ngl::Real)_z;

}


void Shape::incrementTime()
{
    m_timeIncrement = calculateFrameIncrement();
    if (m_time >=1.0f)
    {
        m_timeIncrement=0.0f;
    }
    m_time += m_timeIncrement;
    

}

void Shape::render() const
{
  m_vao->bind();
  m_vao->setData(ngl::SimpleVAO::VertexData(m_vertexPositions.size()*sizeof(ngl::Vec3),m_vertexPositions[0][0]));
  m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(ngl::Vec3), 0,GL_FALSE);
  m_vao->setNumIndices(m_vertexPositions.size());  
  m_vao->draw();
  m_vao->unbind();
}

int Shape::getAnimStart() const
{
    return m_animStart;
}

void Shape::setAnimStart(int newAnimStart)
{
    m_animStart = newAnimStart;
}
