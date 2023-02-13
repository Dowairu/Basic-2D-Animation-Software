#ifndef RGBA_H_
#define RGBA_H_
#include <cstdint>
#include <algorithm>
#include <ngl/Vec4.h>

///  @class RGBA
///  Simple Colour class develeped during labs for Particle Demo
///  @author David Owairu
///  modified to convert colours from RGBA to ngl:Vec4
///  @version 1.0
///  @date 21/05/22

struct RGBA
{
    RGBA()=default;
    RGBA(unsigned char _r,
         unsigned char _g,
         unsigned char _b,
         unsigned char _a)
         {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
         }
    void set(unsigned char _r, unsigned char _g, unsigned char _b ,unsigned char _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    void clamp(unsigned char _min, unsigned char _max)
    {
        r = std::clamp(r,_min,_max);
        g = std::clamp(g,_min,_max);
        b = std::clamp(b,_min,_max);
        a = std::clamp(a,_min,_max);
    }

    union
    {
        uint32_t pixels=0;
        struct
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    };

    ngl::Vec4 convertToVec4()
    {
        ngl::Vec4 colour;
        colour.m_r = (float)r/255.0f;
        colour.m_g = (float)g/255.0f;
        colour.m_b = (float)b/255.0f;
        colour.m_a = (float)a/255.0f;
        return colour;
    }
   
};
#endif
