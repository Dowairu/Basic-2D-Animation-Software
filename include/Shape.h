#ifndef SHAPE_H_
#define SHAPE_H_
//#include <ngl/AbstractVAO.h>
//#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Transformation.h>
#include "Keyframe.h"
#include "RGBA.h"
#include <memory>

///  @class Shape
///  Class for Drawing shapes and storing keysframes
///  @author David Owairu
///  @version 1.0
///  @date 21/05/22

class Shape
{
public:
    Shape()=default;
    //void setShape(size_t _numVerts,const std::string& _shapeName,ngl::Vec3& _shapePos,ngl::Vec3& _shapeScale,ngl::Vec3& _shapeRot,ngl::Vec3& _pivotPos,RGBA& _colour,std::vector<ngl::Vec3>& _vertPos);
    void setShape(size_t _numVerts,const std::string& _shapeName,ngl::Transformation& _shapeTransform,ngl::Vec3& _pivotPos,RGBA& _colour,std::vector<ngl::Vec3>& _vertPos);

    void setDefaultTriangle();
    void setDefaultQuad();

    ngl::Transformation getShapeTransform(){return m_shapeTransform;}
    ngl::Vec4 getShapeColour(){return m_colour;}
    void setShapeColour(ngl::Vec4 col){m_colour = col;}

    bool getShapeVisibility(){return m_visible;}
    void setShapeVisibility(bool isVisible){m_visible = isVisible; }

    bool getKeyed()const {return m_keyed;}
    int getCurrentKey(){return m_currentKey;}
    void setCurrentKey(int _ck){m_currentKey = _ck;}
    void setKeyed(bool isKeyed){m_keyed = isKeyed; }

    void setPosition(ngl::Vec3& _v);
    void setPositionX(double _x);//had to do these because of ui
    void setPositionY(double _y);
    void setPositionZ(double _z);

    void setRotation(ngl::Vec3& _v);
    void setRotationX(double _x);
    void setRotationY(double _y);
    void setRotationZ(double _z);

    void setScale(ngl::Vec3& _v);
    void setScaleX(double _x);
    void setScaleY(double _y);
    void setScaleZ(double _z);
    ngl::Vec3 getPivot(){return m_pivotPos;}
    ngl::Real calculateFrameIncrement(){return 1.0f/m_inbetweenFrames;}
    void setInbetweenFrames( int _ibf){m_inbetweenFrames = _ibf;}
    int getInbetweenFrames(){return m_inbetweenFrames;}
    ngl::Real getTime(){return m_time;}
    void setTime(ngl::Real _t){m_time = _t;}
    std::string getShapeName(){return m_shapeName;}
    std::vector<Keyframe> getKeyframeList();
    void setKeyframeList(std::vector<Keyframe> _k){m_keyframes = _k;}
    // void setKeyframe(int _frame,ngl::Vec4& _colour,ngl::Transformation _transforms);//sets a keyframe on the selected shape using its current values
    size_t getNumVerts() const {return m_vertexPositions.size();}
    void incrementTime();
    void updateShape();
    void render() const;
    void setAnimStart(int newAnimStart);
    int getAnimStart() const;
    void resetShape(Shape &s);


private:
    ngl::Transformation m_shapeTransform;
    std::vector<Keyframe> m_keyframes;
    std::string m_shapeName;
    ngl::Vec3 m_pivotPos;
    ngl::Vec4 m_colour;
    ngl::Real m_timeIncrement=0;
    int m_inbetweenFrames=0;
    ngl::Real m_time=0;
    int m_currentKey=0;
    int m_animStart;
    int m_animEnd;
    bool m_visible = true;
    bool m_keyed = false;
    std::vector<ngl::Vec3> m_vertexPositions;
    std::shared_ptr<ngl::AbstractVAO> m_vao;

    // on pivots https://stackoverflow.com/questions/56804658/how-to-use-pivot-point-in-transformations
};

#endif
