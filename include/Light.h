/**************************************************
Light is a class for a camera object.
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#ifndef __LIGHT_H__
#define __LIGHT_H__

struct Light {
    glm::vec4 position = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::mat4 proj;
    glm::mat4 view;
    void calculate(){
        view = glm::lookAt(glm::vec3(position), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        proj = glm::ortho(-3.0f,3.0f,-3.0f,3.0f,0.15f,10.0f);
    }
};

#endif 
