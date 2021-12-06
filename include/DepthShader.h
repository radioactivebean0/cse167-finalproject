#include "Shader.h"
#include <glm/glm.hpp>
#ifndef __DEPTHSHADER_H__
#define __DEPTHSHADER_H__

struct DepthShader : Shader {
    glm::mat4 model = glm::mat4(1.0f); GLuint model_loc;
    glm::mat4 projection = glm::mat4(1.0f); GLuint projection_loc;
    glm::mat4 view = glm::mat4(1.0f); GLuint view_loc;

    void initUniforms(){
        model_loc = glGetUniformLocation( program, "model" );
        projection_loc = glGetUniformLocation( program, "projection" );
        view_loc = glGetUniformLocation( program, "view" );
    }

    void setUniforms(){
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
    }
};


#endif