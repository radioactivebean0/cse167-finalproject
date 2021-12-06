/**************************************************
SurfaceShader is a shader that has the uniform
 variables for modelview, projection, the
 parameters for the materials, and a list of lights.
*****************************************************/
#include "Shader.h"
#include "Material.h"
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#ifndef __SURFACESHADER_H__
#define __SURFACESHADER_H__

struct SurfaceShader : Shader {
    // modelview and projection
    glm::mat4 view = glm::mat4(1.0f); GLuint view_loc;
    glm::mat4 model = glm::mat4(1.0f); GLuint model_loc;
    glm::mat4 projection = glm::mat4(1.0f); GLuint projection_loc;
    glm::mat4 lightview = glm::mat4(1.0f); GLuint lightview_loc;
    glm::mat4 lightprojection = glm::mat4(1.0f); GLuint lightprojection_loc;

    // material parameters
    Material* material;
    GLuint ambient_loc;
    GLuint diffuse_loc;
    GLuint specular_loc;
    GLuint emision_loc;
    GLuint shininess_loc;
    
    // lights
    GLboolean enablelighting = GL_FALSE; // are we lighting at all (global).
    GLboolean depthshade = GL_FALSE;
    glm::vec4 lightposition = glm::vec4(1.0f); // position of light
    glm::vec4 lightcolor = glm::vec4(1.0f); // color of light
    GLuint enablelighting_loc;
    GLuint lightposition_loc;
    GLuint lightcolor_loc;
    GLuint depthshade_loc;

    GLuint sampler_loc;

    
    
    void initUniforms(){
        view_loc  = glGetUniformLocation( program, "view" );
        model_loc  = glGetUniformLocation( program, "model" );
        projection_loc = glGetUniformLocation( program, "projection" );
        lightview_loc = glGetUniformLocation( program, "lightview" );
        lightprojection_loc = glGetUniformLocation( program, "lightprojection" );
        ambient_loc    = glGetUniformLocation( program, "ambient" );
        diffuse_loc    = glGetUniformLocation( program, "diffuse" );
        specular_loc   = glGetUniformLocation( program, "specular" );
        emision_loc    = glGetUniformLocation( program, "emision" );
        shininess_loc  = glGetUniformLocation( program, "shininess" );
        enablelighting_loc = glGetUniformLocation( program, "enablelighting" );
        lightposition_loc = glGetUniformLocation( program, "lightposition" );
        lightcolor_loc = glGetUniformLocation( program, "lightcolor" );
        sampler_loc = glGetUniformLocation( program, "shadowMap" );
        depthshade_loc = glGetUniformLocation( program, "depthshade" );
    }
    void setUniforms(){
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(lightview_loc, 1, GL_FALSE, &lightview[0][0]);
        glUniformMatrix4fv(lightprojection_loc, 1, GL_FALSE, &lightprojection[0][0]);
        glUniform4fv( ambient_loc  , 1, &(material -> ambient[0])  );
        glUniform4fv( diffuse_loc  , 1, &(material -> diffuse[0])  );
        glUniform4fv( specular_loc , 1, &(material -> specular[0]) );
        glUniform4fv( emision_loc  , 1, &(material -> emision[0])  );
        glUniform1fv( shininess_loc, 1, &(material -> shininess)   );
        glUniform1i( enablelighting_loc, enablelighting );
        glUniform1i( depthshade_loc, depthshade );
        glUniform4fv( lightposition_loc, 1, &lightposition[0] );
        glUniform4fv( lightcolor_loc, 1, &lightcolor[0] );
        glUniform1i( sampler_loc, 0);
    }
};

#endif 
