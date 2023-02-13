#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/AbstractVAO.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/SimpleIndexVAO.h>
#include <iostream>
#include <memory>

#include <glm/common.hpp>
#include <glm/glm.hpp>

NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget(_parent)
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  // camera initial values will be used in my cmaera class
  setMouseTracking(true);
  setFocusPolicy(Qt::FocusPolicy::StrongFocus);
  m_cameraIndex=0;
  m_moveMode=CamMode::MOVEEYE;
  m_drawHelp=true;
  m_fov=45.0f;
  m_aspect=1024.0f/768.0f;
  m_camRotation=0;
}

NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::createCameras()
{
  // to be filled later
  Camera myCam;
  ngl::Vec3 eye(0.0f,0.0f,-10.0f);
  ngl::Vec3 look=ngl::Vec3::zero();
  ngl::Vec3 up(0,1,0);

  myCam.set(eye,look,up);
  myCam.setShape(m_fov,m_aspect, 0.2f,150.0f);
  m_cameras.push_back(myCam);
}

void NGLScene::initialiseTimeline()
{
  int frames = 250;
  m_timeline.initialiseTimeline(frames);
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_aspect=static_cast<float>(_w/_h);
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );

}

const static char* PlaneShader = "PlaneShader";
const static char* SphereShader = "SphereShader";


void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  createCameras();
  initialiseTimeline();

  std::vector<Layer>& layers = m_timeline.getLayers();
  // needs to have & because we are getting a refference to the layers

  // Layer layer2;
  // layer2.initialiseLayer("layer2");
  // layers.push_back(layer2);

//  Shape myShape;
//  myShape.setDefaultQuad();
//  m_timeline.addShape(myShape);
//  //myShape.setShapeVisibility(false);
//  m_timeline.setCurrentFrame(30);
//  m_timeline.setKeyframe(myShape,m_timeline.getCurrentFrame(),myShape.getShapeColour(),myShape.getShapeTransform());
//  //myShape.setScale(ngl::Vec3(1.5f,1.5f,1.5f));
//  //myShape.setRotation(ngl::Vec3(0.0f,0.0f,360.0f));
//  //myShape.setPosition(ngl::Vec3(-3.0f,0.0f,0.0f));
//  //m_timeline.setKeyframe(myShape,m_timeline.getCurrentFrame(),myShape.getShapeColour(),myShape.getShapeTransform());
//  m_timeline.setCurrentFrame(100);
//  myShape.setScale(ngl::Vec3(1.0f,1.0f,1.0f));
//  //myShape.setRotation(ngl::Vec3(0.0f,0.0f,0.0f));
//  myShape.setPosition(ngl::Vec3(-4.0f,2.0f,0.0f));
//  std::cout<<"x: "<<myShape.getShapeTransform().getPosition().m_x<<"\n";
//  m_timeline.setKeyframe(myShape,m_timeline.getCurrentFrame(),myShape.getShapeColour(),myShape.getShapeTransform());
//  // m_timeline.setCurrentFrame(150);
//  // myShape.setPosition(ngl::Vec3(-2.0f,4.0f,0.0f));
//  // myShape.setRotation(ngl::Vec3(0.0f,0.0f,0.0f));
//  // myShape.setScale(ngl::Vec3(1.0f,1.0f,1.0f));
//  //m_timeline.removeKeyframe(myShape,30);
//  m_timeline.setCurrentFrame(0);
//  //layers[0].addShapetoLayer(myShape);

//  Shape otherShape;
//  otherShape.setDefaultTriangle();
//  m_timeline.addShape(otherShape);
//  m_timeline.setKeyframe(otherShape,m_timeline.getCurrentFrame(),otherShape.getShapeColour(),otherShape.getShapeTransform());
//  m_timeline.setCurrentFrame(100);
//  otherShape.setPosition(ngl::Vec3(3.0f,0.0f,0.0f));
//  m_timeline.setKeyframe(otherShape,m_timeline.getCurrentFrame(),otherShape.getShapeColour(),otherShape.getShapeTransform());
//  // //otherShape.setShapeVisibility(false);
//  m_timeline.setCurrentFrame(150);
//  otherShape.setPosition(ngl::Vec3(4.0f,2.0f,0.0f));
//  otherShape.setScale(ngl::Vec3(1.0f,1.0f,1.0f));
//  m_timeline.setKeyframe(otherShape,m_timeline.getCurrentFrame(),otherShape.getShapeColour(),otherShape.getShapeTransform());
//  //otherShape.removeKeyframe(100);
//  m_timeline.setCurrentFrame(0);



  // std::cout<<"keyframes :"<<otherShape.getKeyframes()[0].frame<<"\n";
  // std::cout<<"keyframes :"<<otherShape.getKeyframes()[1].frame<<"\n";
  // //layers[1].addShapetoLayer(otherShape);
  ngl::ShaderLib::loadShader(PlaneShader,"shaders/PlaneVertex.glsl","shaders/PlaneFragment.glsl");
  //startTimer(16.6);//16.6 is 60hz converted to ms
  startTimer(41);//41.67
  timer.start();
}

void NGLScene::loadMatricesToShader(ngl::Transformation& _t)
{
  ngl::ShaderLib::use(PlaneShader);
  struct transform
  {
    ngl::Mat4 MVP;
    ngl::Mat4 normalMatrix;
    ngl::Mat4 M;
  };

  transform t;
  t.M= _t.getMatrix();

  t.MVP=m_cameras[m_cameraIndex].getVPMatrix()*t.M;
  ngl::ShaderLib::setUniformBuffer("TransformUBO",sizeof(transform),&t.MVP.m_00);
  ngl::ShaderLib::setUniform("camPos",m_cameras[m_cameraIndex].getEye().toVec3());

}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  //need to add error checking to the layer and shape vectors to see if they are empty
  // std::cout<<"currentFrame: "<<m_timeline.getCurrentFrame()<<"\n";

  // std::cout<<"time: "<<m_timeline.getTime()<<"\n";
  // std::cout<<"Animate: "<<m_timeline.getAnimating()<<"\n";
  std::vector<Shape> shapes = m_timeline.getShapes();
  // std::cout<<shapes[0].getShapeTransform().getPosition().m_x<<"\n";
  for(int i=0;i<shapes.size();i++)
  {
    //bool shapevisible = shapes[i].getShapeVisibility();
    // if(shapevisible)
    // {
    //ngl::Transformation shapeTransform = shapes[i].getShapeTransform();
    ngl::Vec4 col=shapes[i].getShapeColour();
//    std::cout<<"X: "<<col.m_r<<" Y: "<<col.m_g<<" Z: "<<col.m_b<<"\n";
    //shapeTransform.setRotation(m_rotation);
    //shapeTransform.setPosition(m_position);
    //shapeTransform.setScale(m_scale);
    //shapeTransform.setPosition(m_position);
//    m_transform.setScale(shapeTransform.getScale());
//    m_transform.setRotation(shapeTransform.getRotation());
//    m_transform.setPosition(shapeTransform.getPosition());
        m_transform.setScale(m_scale);
        m_transform.setRotation(m_rotation);
        m_transform.setPosition(m_position);
        //std::cout<<"tXval: "<<m_position.m_x<<" tYval: "<<m_position.m_y<<" tZval: "<<m_position.m_z<<"\n";
        //std::cout<<"shXval: "<<shapeTransform.getPosition().m_x<<" shYval: "<<shapeTransform.getPosition().m_y<<" shZval: "<<shapeTransform.getPosition().m_z<<"\n";
    loadMatricesToShader(m_transform);// not passing in the transforms of the shape for getmatrix
    ngl::ShaderLib::setUniform("PlaneColour", col.m_r, col.m_g,col.m_b, col.m_a);
    shapes[i].render();

    // }
  }
  // std::cout<<"number of Shapes: "<<shapes.size()<<"\n";
  // std::vector<Layer>& layers = m_timeline.getLayers();
  // for(int i=0;i<layers.size();++i)
  // {
  //   bool isvisible = layers[i].getLayerVisibility();
  //   if(isvisible)
  //   {
  //     std::vector<Shape>& shapes = layers[i].getShapes();
  //     for(int j=0;j<shapes.size();++j)
  //     {
  //       bool shapevisible = shapes[j].getShapeVisibility();
  //       std::string shapeName = shapes[j].getShapeName();
  //       ngl::Transformation shapeTransform = shapes[j].getShapeTransform();
  //       if(shapevisible)
  //       {
  //         ngl::Vec4 col=shapes[j].getShapeColour();
  //         //m_transform.setMatrix(shapeTransform.getMatrix());//get matrix doesnt work on my transform for some wierd reason
  //         m_transform.setScale(shapeTransform.getScale());
  //         m_transform.setRotation(shapeTransform.getRotation());
  //         m_transform.setPosition(shapeTransform.getPosition());
  //         loadMatricesToShader(m_transform);// not passing in the transforms of the shape for getmatrix
  //         ngl::ShaderLib::setUniform("PlaneColour", col.m_r, col.m_g,col.m_b, col.m_a);
  //         shapes[j].render();
  //         m_transform.reset();
  //       }
  //       else
  //       {
  //         std::cout<<"Shape: "<<shapeName <<" is not visible"<<std::endl;
  //       }

  //     }
  //   }
  //   else
  //   {
  //     std::cout<<"layer not visible"<<std::endl;
  //   }
  //}  
}

void NGLScene::setCameraShape()
{
  for(auto &cam : m_cameras)
  {
    cam.setShape(m_fov,m_aspect, 0.2f,150.0f);
  }
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::timerEvent( QTimerEvent *_e)
{
  if(m_timeline.getAnimating() ==true)
  {
      //need a reset timer somewhere in here like when it goes false.
    //m_timeline.updateTimeline(m_timeline.getCurrentFrame());
    m_timeline.play();
    updateTransforms();//weird but it works

    update();
  }
}

void NGLScene::updateTransforms()
{
    std::vector<Shape> shape = m_timeline.getShapes();
    for (int i = 0; i <shape.size(); i++)
    {
        ngl::Transformation shapeTransform = shape[i].getShapeTransform();
        m_position.set(shapeTransform.getPosition());
        m_rotation.set(shapeTransform.getRotation());
        m_scale.set(shapeTransform.getScale());
        m_colour.set(shape[i].getShapeColour());
    }


}

void NGLScene::updateShape()
{
    std::vector<Shape> shape = m_timeline.getShapes();
    for (int i = 0; i <shape.size(); i++)
    {
        shape[i].setPosition(m_position);
        shape[i].setRotation(m_rotation);
        shape[i].setScale(m_scale);
        shape[i].setShapeColour(m_colour);

        m_timeline.updateShapesList(shape[i],i);
        //std::cout<<"newXval: "<<shapeTransform.getPosition().m_x<<" newYval: "<<shapeTransform.getPosition().m_y<<" newZval: "<<shapeTransform.getPosition().m_z<<"\n";
        std::cout<<"updtXval: "<<shape[i].getShapeTransform().getPosition().m_x<<" updtYval: "<<shape[0].getShapeTransform().getPosition().m_y<<" updtZval: "<<shape[0].getShapeTransform().getPosition().m_z<<"\n";
    }


}

void addtoListView()
{

}

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      if(m_timeline.getAnimating())
      {
        m_timeline.setAnimate(false);
      }
      else
      {
        m_timeline.setAnimate(true);
      }

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

  //update();
}

void NGLScene::addSquare()
{
    Shape mySquare;
    mySquare.setDefaultQuad();
    m_timeline.addShape(mySquare);
    updateTransforms();
    update();
}

void NGLScene::addTriangle()
{
    Shape myTri;
    myTri.setDefaultTriangle();
    m_timeline.addShape(myTri);
    updateTransforms();
    update();
}

void NGLScene::removeShape()
{
    std::vector<Shape> shapes = m_timeline.getShapes();
    if(!shapes.empty())
    {
        for (int i = 0; i <shapes.size(); i++)
        {
            m_timeline.removeShape(shapes[i]);
            update();
        }
    }
    else
    {
        QMessageBox::about(this,"Deletion Error","NO SHAPES TO DELETE !!!");
    }
}

void NGLScene::setCurrentFrame(int _i)
{

    m_timeline.setCurrentFrame(_i);
    m_timeline.updateTimeline();
    updateTransforms();
    update();
}

void NGLScene::setXRotation( double _x		)
{
    m_rotation.m_x = _x;
    updateShape();
    update();
}

void NGLScene::addKeyframe()
{
    std::vector<Shape> shapes = m_timeline.getShapes();
    if(!shapes.empty())
    {

        m_timeline.setKeyframe(shapes[0],m_timeline.getCurrentFrame(),shapes[0].getShapeColour(),shapes[0].getShapeTransform());
    }
    else
    {
        QMessageBox::about(this,"keyframe error","must have a shape to add keys to !!!");
    }
}

void NGLScene::removeKeyframe()
{
    std::vector<Shape> shapes = m_timeline.getShapes();
    if(!shapes.empty())
    {
        for (int i = 0; i <shapes.size(); i++)
        {
            m_timeline.removeKeyframe(shapes[i],m_timeline.getCurrentFrame());
        };
    }
    else
    {
        QMessageBox::about(this,"keyframe error","must have a shape to add keys to !!!");
    }
}

void NGLScene::setYRotation( double _y	)
{
    m_rotation.m_y = _y;
    updateShape();
    update();
}
void NGLScene::setZRotation( double _z )
{
    m_rotation.m_z = _z;
    updateShape();
    update();
}

void NGLScene::setXScale( double _x	)
{
    m_scale.m_x = _x;
    updateShape();
    update();
}

void NGLScene::setYScale(	 double _y)
{
    m_scale.m_y = _y;
    updateShape();
    update();
}
void NGLScene::setZScale( double _z )
{
    m_scale.m_z = _z;
    updateShape();
    update();
}

void NGLScene::setXPosition( double _x	)
{
    m_position.m_x = _x;
    updateShape();
    update();
}

void NGLScene::setYPosition( double _y	)
{
    m_position.m_y = _y;
    updateShape();
    update();
}
//void NGLScene::setZPosition( double _z	 )
//{
//    std::vector<Shape> Shape = m_timeline.getShapes();
//    Shape[0].setPosition(ngl::Vec3(0.0f,0.0f,_z));
//    update();
//}

//void NGLScene::setObjectMode(	int _i)
//{
//	m_selectedObject=_i;
//	update();
//}
void NGLScene::setColour()
{
    //this isnt pershape rn
    QColor colour = QColorDialog::getColor();
    if( colour.isValid())
    {
        ngl::Vec4 newcol(static_cast<float>(colour.redF()),static_cast<float>(colour.greenF()),static_cast<float>(colour.blueF()),1.0f);
        m_colour = newcol;
        updateShape();
        update();
    }
}
