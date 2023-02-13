#include "Timeline.h"
#include "NGLScene.h"
#include <QDateTime>

/// @file Timeline.cpp
/// @brief implementation files for Timeline class

  
void Timeline::initialiseTimeline(int& _frames)
{
    m_frames = _frames;
    m_defaultLayer.initialiseLayer();
    m_layers.push_back(m_defaultLayer);
}

void Timeline::removeShape(Shape& s)
{
    for(int i=0;i<m_shapes.size();i++)
    {
        std::string theShape = m_shapes[i].getShapeName();
        //std::cout<<theFrame<<std::endl;
        if(theShape == s.getShapeName())
        {
            m_shapes.erase(m_shapes.begin()+i);
        }
    }
}

void Timeline::setCurrentFrame(int _frame)
{
    m_currentFrame = _frame;

}

void Timeline::setKeyframe(Shape& shape,int _frame,ngl::Vec4& _colour,ngl::Transformation _transforms)
{
    //add checks for frames(if theyve been set the frame number and so on)
    Keyframe key;
    key.frame = _frame;
    key.colourVal = _colour;
    key.transformVals = _transforms;
    std::cout<<shape.getShapeName()<<"\n";
    shape.setKeyed(true);
    std::vector<Keyframe> keys=shape.getKeyframeList();
    //add check for if your seeting it on the same frame
    keys.push_back(key);
    shape.setKeyframeList(keys);
    for(int i=0;i<m_shapes.size();i++)
    {
        std::string theShape = m_shapes[i].getShapeName();
        if(theShape == shape.getShapeName())
        {
            updateShapesList(shape,i);
        }
    }
    std::cout<<"added a keyframes to an object!!!!!"<<"\n";
    std::cout<<"frame number: "<<key.frame<<"\n";
    std::cout<<"Xpos key: "<<key.transformVals.getPosition().m_x<<" Ypos key: "<<key.transformVals.getPosition().m_y<<" Zpos key: "<<key.transformVals.getPosition().m_z<<"\n";
    std::cout<<"number of keys"<<keys.size()<<"\n";
}

void Timeline::removeKeyframe(Shape& shape,int _frame)
{
    std::vector<Keyframe> keys=shape.getKeyframeList();
    if(!keys.empty())
    {
        for(int i=0;i<keys.size();i++)
        {
            int theFrame = keys[i].frame;
            std::cout<<theFrame<<std::endl;
            std::cout<<_frame<<std::endl;
            std::string theShape = m_shapes[0].getShapeName();
            if(theFrame == _frame && theShape == shape.getShapeName())
            {
                keys.erase(keys.begin()+i);
                shape.setKeyframeList(keys);
                updateShapesList(shape,0);
                ///@note need some check in here for seting the object transform to the frame before or after the deleted one
            }
        }
    }
    else
    {
        std::cout<<"must have a shape to add keys to !!!"<<"\n";
    }
}

void Timeline::updateTimeline()
{
    for (int i = 0; i <m_shapes.size(); i++)//for every shape
    {
        bool iskeyed = m_shapes[i].getKeyed();
        if(iskeyed)//
        {
            std::vector<Keyframe> keys = m_shapes[i].getKeyframeList();//if its keyed get its list of keyframes
            if(m_shapes[i].getCurrentKey() < keys.size()-1)
            {
                //calculating increment between frames
                int startframe = keys[m_shapes[i].getCurrentKey()].frame;
                int endframe =  keys[m_shapes[i].getCurrentKey()+1].frame;
                m_shapes[i].setInbetweenFrames(endframe - startframe);
                int incrementAmount = getCurrentFrame() - startframe;

                if((getCurrentFrame() > startframe) && (getCurrentFrame() <= endframe) )
                {
                    m_shapes[i].setTime(m_shapes[i].calculateFrameIncrement()*incrementAmount);//if inbetween two keyframes interpolate by eun distance
                }
                else if(getCurrentFrame() <= keys.begin()->frame)//if less than the frame number of the first keyframe set time to 0
                {
                    m_shapes[i].setTime(0);
                }
                else//if more than the frame number of the last keyframe set time to 1
                {
                    m_shapes[i].setTime(1);
                }

                ngl::Vec3 startPosVal = keys[m_shapes[i].getCurrentKey()].transformVals.getPosition();
                ngl::Vec3 endPosVal = keys[m_shapes[i].getCurrentKey()+1].transformVals.getPosition();
                ngl::Vec3 startRotVal = keys[m_shapes[i].getCurrentKey()].transformVals.getRotation();
                ngl::Vec3 endRotVal = keys[m_shapes[i].getCurrentKey()+1].transformVals.getRotation();
                ngl::Vec3 startScaleVal = keys[m_shapes[i].getCurrentKey()].transformVals.getScale();
                ngl::Vec3 endScaleVal = keys[m_shapes[i].getCurrentKey()+1].transformVals.getScale();
                ngl::Vec4 startColourVal = keys[m_shapes[i].getCurrentKey()].colourVal;
                ngl::Vec4 endColourVal = keys[m_shapes[i].getCurrentKey()+1].colourVal;

                //lerping values by increment*keyframe progress(between two keys)
                ngl::Vec3 lpos= ngl::lerp(startPosVal,endPosVal,m_shapes[i].getTime());
                ngl::Vec3 lrot= ngl::lerp(startRotVal,endRotVal,m_shapes[i].getTime());
                ngl::Vec3 lscale= ngl::lerp(startScaleVal,endScaleVal,m_shapes[i].getTime());
                ngl::Vec4 lcol = ngl::lerp(startColourVal,endColourVal,m_shapes[i].getTime());

                //setting the lerped position
                m_shapes[i].setPosition(lpos);
                m_shapes[i].setRotation(lrot);
                m_shapes[i].setScale(lscale);
                m_shapes[i].setShapeColour(lcol);
                updateShapesList(m_shapes[i],i);
             }
            else
            {
                m_shapes[i].setCurrentKey(0);
            }
        }
        else
        {
            std::cout<<"Shape :"<<m_shapes[i].getShapeName()<<" has no keyframes"<<"\n";
        }
     }
}

void Timeline::play()
{
    for (int i = 0; i <m_shapes.size(); i++)
    {
        bool iskeyed = m_shapes[i].getKeyed();
        if(iskeyed)
        {
            std::vector<Keyframe> keys = m_shapes[i].getKeyframeList();//if its keyed get its list of keyframes
            setCurrentFrame(getCurrentFrame()+1);
            if(getCurrentFrame()>m_frames)
            {
                setCurrentFrame(0);
            }
            if(m_shapes[i].getCurrentKey() < keys.size()-1)
            {
                //calculating increment between frames
                int startframe = keys[m_shapes[i].getCurrentKey()].frame;
                int endframe =  keys[m_shapes[i].getCurrentKey()+1].frame;
                m_shapes[i].setInbetweenFrames(endframe - startframe);

//                if((getCurrentFrame() > startframe) && (getCurrentFrame() <= endframe) )
//                {

//                }
                m_shapes[i].incrementTime();
                //setting start and end positions for interpolation
                ngl::Vec3 startPosVal = keys[m_shapes[i].getCurrentKey()].transformVals.getPosition();
                ngl::Vec3 endPosVal = keys[m_shapes[i].getCurrentKey()+1].transformVals.getPosition();
                ngl::Vec3 startRotVal = keys[m_shapes[i].getCurrentKey()].transformVals.getRotation();
                ngl::Vec3 endRotVal = keys[m_shapes[i].getCurrentKey()+1].transformVals.getRotation();
                ngl::Vec3 startScaleVal = keys[m_shapes[i].getCurrentKey()].transformVals.getScale();
                ngl::Vec3 endScaleVal = keys[m_shapes[i].getCurrentKey()+1].transformVals.getScale();
                ngl::Vec4 startColourVal = keys[m_shapes[i].getCurrentKey()].colourVal;
                ngl::Vec4 endColourVal = keys[m_shapes[i].getCurrentKey()+1].colourVal;

                //std::cout<<m_shapes[i].getTime()<<"\n";
                ngl::Vec3 lpos= ngl::lerp(startPosVal,endPosVal,m_shapes[i].getTime());
                ngl::Vec3 lrot= ngl::lerp(startRotVal,endRotVal,m_shapes[i].getTime());
                ngl::Vec3 lscale= ngl::lerp(startScaleVal,endScaleVal,m_shapes[i].getTime());
                ngl::Vec4 lcol = ngl::lerp(startColourVal,endColourVal,m_shapes[i].getTime());

                //setting shapes transforms to the interpolated position
                int interpolating_frame = m_shapes[i].getTime()*m_shapes[i].getInbetweenFrames() + startframe;//keys[m_shapes[i].getCurrentKey()].frame;
                std::cout<<"CurrentFrame: "<<getCurrentFrame()<<"\n";
                std::cout<<"Interpolating Frame: "<<interpolating_frame<<"\n";
//                if((getCurrentFrame() >= interpolating_frame) && (getCurrentFrame() <= endframe))
//                {

//                }
//                std::cout<<"ANIMATING!!";
                m_shapes[i].setPosition(lpos);
                m_shapes[i].setRotation(lrot);
                m_shapes[i].setScale(lscale);
                m_shapes[i].setShapeColour(lcol);

                if(m_shapes[i].getTime() >= 1)
                {
                    std::cout<<"DOOOOOOOOOOONEEEEEEEEE!"<<"\n";
                    m_shapes[i].setCurrentKey(m_shapes[i].getCurrentKey()+1);
                    m_shapes[i].setTime(0);
                    //need to check if I've gotten to the lasy key
                }

            }
            else
            {
                m_shapes[i].setCurrentKey(0);
            }

        }
        else
        {
            if(getCurrentFrame()>m_frames)
            {
                setCurrentFrame(0);
            }
            else
            {
                setCurrentFrame(getCurrentFrame()+1);

            }

        }

    }

    //prevTime = currentTime;

    // for(int i =0;i<m_layers.size();++i)
    // {
    //     std::vector<Shape>& shapes = m_layers[i].getShapes();
    //     for(int j =0;j<shapes.size();++j)
    //     {
    //         bool isKeyed = shapes[j].getKeyedShape();
    //         if(isKeyed)
    //         {
    //             std::cout<<"hell yh"<<"\n";
    //             std::vector<Keyframe> shapeKeyframes = shapes[j].getKeyframes();

    //             int time = shapeKeyframes[j+1].frame - shapeKeyframes[j].frame;
    //             ngl::Vec3 startVal = shapeKeyframes[j].transformVals.getPosition();
    //             ngl::Vec3 endVal = shapeKeyframes[j+1].transformVals.getPosition();
    //             ngl::Vec3 lpos= ngl::lerp(startVal,endVal,time);
    //             shapes[j].getShapeTransform().setPosition(lpos);
    //         }
    //         else
    //         {
    //             std::cout<<"Shape has no keys"<<"\n";
    //         }
    //     }

    // }
}
