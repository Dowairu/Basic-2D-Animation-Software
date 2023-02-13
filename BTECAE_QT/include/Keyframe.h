#ifndef KEYFRAME_H_
#define KEYFRAME_H_
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Transformation.h>
#include <vector>

///  @struct Keyframe
///  simple keyframe struct for holding, keyable attributes
///  @author David Owairu
///  @version 1.0
///  @date 21/05/22

struct Keyframe
{
    Keyframe()=default;
    int frame;
    ngl::Vec4 colourVal;
    ngl::Transformation transformVals;
     
};

#endif
