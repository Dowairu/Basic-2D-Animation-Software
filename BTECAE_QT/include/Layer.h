#ifndef LAYER_H_
#define LAYER_H_
#include <string>
#include <vector>
#include <iostream>
#include "Shape.h"

///@class Layer
///Simple class for holding animated and non animated objects.
///  @author David Owairu
///  @version 1.0
///  @date 21/05/22

class Layer
{
public:
    Layer() = default;
    void initialiseLayer(const std::string& _layerName = "default_Layer");
    void addShapetoLayer(const Shape& s) {m_objList.push_back(s); }//funtion doesnt work for some odd reason 
    bool getLayerVisibility(){return m_visible;}
    void setLayerVisibility(bool visibility){m_visible = visibility; }
    std::vector<Shape>& getShapes() { return m_objList; }
    std::string getLayerName(){return m_layerName;}

    //void update()
    //void removeShapeFromLayer(Shape _shape);



private:
    std::string m_layerName;
    std::vector<Shape> m_objList;
    bool m_visible = true;
};

#endif
