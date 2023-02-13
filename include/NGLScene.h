#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <ngl/Text.h>
#include <ngl/Transformation.h>
#include "WindowParams.h"
#include "Camera.h"
#include "Timeline.h"
#include <QOpenGLWidget>
#include <QColorDialog>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QListView>
#include <QElapsedTimer>
#include <array>
#include <memory>

//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
//----------------------------------------------------------------------------------------------------------------------

class NGLScene : public QOpenGLWidget
{
   Q_OBJECT
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for our NGL drawing class
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    NGLScene(QWidget *_parent=nullptr);
       //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor must close down ngl and release OpenGL resources
    //----------------------------------------------------------------------------------------------------------------------
    ~NGLScene() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the initialize class is called once when the window is created and we have a valid GL context
    /// use this to setup any default GL stuff
    //----------------------------------------------------------------------------------------------------------------------
    void initializeGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we resize the scene
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(int _w, int _h) override;
    Timeline m_timeline;


public slots:
    void addSquare();
    void addTriangle();
    void removeShape();
    void setCurrentFrame(int _i);
    void setXRotation( double _x	);
    void addKeyframe();
    void removeKeyframe();
    /// @brief set the Y rotation value
    /// @parm[in] _y the value to set
    void setYRotation( double _y	);
    /// @brief set the Z rotation value
    /// @parm[in] _z the value to set
    void setZRotation( double _z	);
    /// @brief set the X scale value
    /// @parm[in] _x the value to set
    void setXScale( double _x	);
    /// @brief set the Y scale value
    /// @parm[in] _y the value to set
    void setYScale( double _y	);
    /// @brief set the Z scale value
    /// @parm[in] _z the value to set
    void setZScale( double _z	);

    /// @brief set the X position value
    /// @parm[in] _x the value to set
    void setXPosition( double _x	);
    /// @brief set the Y position value
    /// @parm[in] _y the value to set
    void setYPosition(double _y);
    /// @brief set the Z position value
    /// @parm[in] _z the value to set
    //void setZPosition(double _z	);
    /// @brief set the draw object
    /// @param[in] _i the index of the object
    void setColour();




private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the windows params such as mouse and rotations etc
    //----------------------------------------------------------------------------------------------------------------------
    WinParams m_win;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the camera move mode
    //----------------------------------------------------------------------------------------------------------------------
    enum class CamMode {MOVEEYE,MOVELOOK,MOVEBOTH,MOVESLIDE};
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a container for our Cameras
    //----------------------------------------------------------------------------------------------------------------------
    std::vector <Camera> m_cameras;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief an index into the active camera list
    //----------------------------------------------------------------------------------------------------------------------
    size_t m_cameraIndex;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the move mode for the camera
    //----------------------------------------------------------------------------------------------------------------------
    CamMode m_moveMode;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief toggle help flag
    //----------------------------------------------------------------------------------------------------------------------
    bool m_drawHelp;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief fov value for the camera
    //----------------------------------------------------------------------------------------------------------------------
    float m_fov;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief aspect ratio of the camera
    //----------------------------------------------------------------------------------------------------------------------
    float m_aspect;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief rotation of the teapot
    //----------------------------------------------------------------------------------------------------------------------
    float m_camRotation;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief array of light states
    //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------
    // text for rendering
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<ngl::Text> m_text;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the global mouse transforms
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_mouseGlobalTX;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief transformation stack for the gl transformations etc
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Transformation m_transform;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method to load transform matrices to the shader
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatricesToShader(ngl::Transformation& _t);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseMoveEvent (QMouseEvent * _event ) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is pressed
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mousePressEvent ( QMouseEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseReleaseEvent ( QMouseEvent *_event ) override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void wheelEvent( QWheelEvent *_event) override;
    void createCameras();
    void setCameraShape();
    void initialiseTimeline();
    void timerEvent(QTimerEvent *_e) override;
    QElapsedTimer timer;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    int m_frame=0;
    ngl::Vec3 m_position;
    ngl::Vec3 m_rotation;
    ngl::Vec3 m_scale;
    ngl::Vec4 m_colour;
    void updateTransforms();
    ///@brief this method updates the shapes transforms and colours ///@note I may move this within shape later.
    void updateShape();






};



#endif
