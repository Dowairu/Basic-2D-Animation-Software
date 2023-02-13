#include "../include/MainWindow.h"
#include "ui/ui_MainWindow.h"
#include <QSlider>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_gl = new NGLScene(this);
    m_ui->MainWIndowGridLayout->addWidget(m_gl,0,0,3,1);
    // add signals and slots here
//    connect(m_ui->addSquare,&QPushButton::clicked,[=](){
//        m_gl->addSquare();
//    });
//    connect(m_ui->m_wireframe,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));
//      // set the rotation signals
    connect(m_ui->addSquare,SIGNAL(clicked()),m_gl,SLOT(addSquare()));

    connect(m_ui->timelineSlider,QOverload<int>::of(&QSlider::valueChanged),m_gl,[=](int val){ upDateFrame(val); });

    connect(m_ui->addTriangle,SIGNAL(clicked()),m_gl,SLOT(addTriangle()));
    connect(m_ui->removeShape,SIGNAL(clicked()),m_gl,SLOT(removeShape()));
    connect(m_ui->m_currentFrame,SIGNAL(valueChanged(int)),m_gl,SLOT(setCurrentFrame(int)));
    connect(m_ui->addKeyframe,SIGNAL(clicked()),m_gl,SLOT(addKeyframe()));
    connect(m_ui->removeKeyframe,SIGNAL(clicked()),m_gl,SLOT(removeKeyframe()));
    connect(m_ui->timelineSlider,SIGNAL(valueChanged(int)),m_gl,SLOT(setCurrentFrame(int)));
    connect(m_ui->m_objectRotX,SIGNAL(valueChanged(double)),m_gl,SLOT(setXRotation(double)));
    connect(m_ui->m_objectRotY,SIGNAL(valueChanged(double)),m_gl,SLOT(setYRotation(double)));
    connect(m_ui->m_objectRotZ,SIGNAL(valueChanged(double)),m_gl,SLOT(setZRotation(double)));
    /// set the scale signals
    connect(m_ui->m_objectScaleX,SIGNAL(valueChanged(double)),m_gl,SLOT(setXScale(double)));
    connect(m_ui->m_objectScaleY,SIGNAL(valueChanged(double)),m_gl,SLOT(setYScale(double)));
    //connect(m_ui->m_objectScaleZ,SIGNAL(valueChanged(double)),m_gl,SLOT(setZScale(double)));
    /// set the position signals
    connect(m_ui->m_objectPosX,SIGNAL(valueChanged(double)),m_gl,SLOT(setXPosition(double)));
    connect(m_ui->m_objectPosY,SIGNAL(valueChanged(double)),m_gl,SLOT(setYPosition(double)));
    //connect(m_ui->m_objectPosZ,SIGNAL(valueChanged(double)),m_gl,SLOT(setZPosition(double)));
    /// set the combo box index change signal
//    connect(m_ui->m_objectSelection,SIGNAL(currentIndexChanged(int)),m_gl,SLOT(setObjectMode(int)));
    connect(m_ui->m_colour,SIGNAL(clicked()),m_gl,SLOT(setColour()));

}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::upDateFrame(int i)
{
   //int frame = m_gl->m_timeline.getCurrentFrame();
   m_ui->m_currentFrame->setValue(i);
   m_ui->timelineSlider->setMaximum(m_gl->m_timeline.m_frames);
}

