#ifndef TIMELINE_H_
#define TIMELINE_H_
#include <memory>
#include <vector>
#include "Layer.h"
#include <string>
#include <ngl/Util.h>

///  @class Timeline
///  Class for managing creation,deletion and playback of keyframes
///  and storage of laysers
///  @author David Owairu
///  @version 1.0
///  @date 21/05/22
///
class Timeline
{
public:
    Timeline() = default;
    void initialiseTimeline(int& _frames);
    void play();//through all layers and object with keyframes
    void pause();

    std::vector<Shape> getShapes() { return m_shapes; }//if doest work add in &
    void addShape(const Shape& s) {m_shapes.push_back(s); }
    void removeShape(Shape& s);
    int getCurrentFrame(){return m_currentFrame;}
    void setKeyframe(Shape& shape,int _frame,ngl::Vec4& _colour,ngl::Transformation _transforms);
    void removeKeyframe(Shape& shape,int _frame);
    void updateShapesList(Shape& shape, int iterator){m_shapes[iterator] = shape;}
    bool getAnimating(){return m_animate;}
    void setAnimate(bool _animating){m_animate = _animating;}
    ngl::Real calculateTimeIncrement(){return 1.0f/250;}
    void setCurrentFrame(int _frame);
    void updateTimeline();
    std::vector<Layer> getLayers() { return m_layers; }//if doest work add in &
    void addLayer(const Layer& s) {m_layers.push_back(s); }
    int m_frames;
    //  want to move keyframe .h in here but keep getting cyclical dependency issues
    

private:
    //std::vector<int> 
    Layer m_defaultLayer;
    std::vector<Shape> m_shapes;
    std::vector<Layer> m_layers;
    //ngl::Real m_time=0;
    //int m_inbetweenFrames;
    ngl::Real m_frameIncrement=0;
    ngl::Real m_frametime=0;
    bool m_animate=0;
    int m_startFrame=0;
    int m_EndFrame;
    int m_currentFrame=0;
    int m_fps=24;
    
};

#endif
