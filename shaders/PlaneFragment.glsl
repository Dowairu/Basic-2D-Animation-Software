#version 410 core
        
layout(location = 0) out vec4 fragColour;
uniform vec4 PlaneColour;
in vec3 worldPos;
in vec3 normal;
uniform vec3 camPos;

void main()
{
    fragColour = PlaneColour;
};