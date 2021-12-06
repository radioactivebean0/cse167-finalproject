/**************************************************
Scene.inl contains the definition of the scene graph
*****************************************************/
#include "Scene.h"
#include "Cube.h"
#include "Obj.h"

using namespace glm;
void Scene::init(void){
    // Create a geometry palette
    geometry["cube"] = new Cube;
    geometry["teapot"] = new Obj;
    geometry["bunny"] = new Obj;
    geometry["cube"] -> init();
    geometry["teapot"] -> init("models/teapot.obj");
    geometry["bunny"] -> init("models/bunny.obj");
    
    // Create a material palette
    material["wood"] = new Material;
    material["wood"] -> ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["wood"] -> diffuse = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> specular = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> shininess = 100.0f;
    
    material["ceramic"] = new Material;
    material["ceramic"] -> ambient = vec4(0.02f, 0.07f, 0.2f, 1.0f);
    material["ceramic"] -> diffuse = vec4(0.1f, 0.25f, 0.7f, 1.0f);
    material["ceramic"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["ceramic"] -> shininess = 150.0f;
 
    material["silver"] = new Material;
    material["silver"] -> ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["silver"] -> diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    material["silver"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["silver"] -> shininess = 50.0f;
    
    material["turquoise"] = new Material;
    material["turquoise"] -> ambient = vec4(0.1f, 0.2f, 0.17f, 1.0f);
    material["turquoise"] -> diffuse = vec4(0.2f, 0.375f, 0.35f, 1.0f);
    material["turquoise"] -> specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    material["turquoise"] -> shininess = 100.0f;

    material["floor"] = new Material;
    material["floor"] -> ambient = vec4(0.14f,0.14f,0.14f, 1.0f);
    material["floor"] -> diffuse = vec4(0.3f,0.3f,0.3f,1.0f);
    material["floor"] -> specular = vec4(0.25f,0.25f,0.25f,1.0f);
    material["floor"] -> shininess = 100.0f;
    
    // Create a model palette
    model["teapot1"] = new Model;
    model["teapot1"] -> geometry = geometry["teapot"];
    model["teapot1"] -> material = material["silver"];
    model["teapot2"] = new Model;
    model["teapot2"] -> geometry = geometry["teapot"];
    model["teapot2"] -> material = material["ceramic"];
    model["table piece"] = new Model;
    model["table piece"] -> geometry = geometry["cube"];
    model["table piece"] -> material = material["wood"];
    model["bunny"] = new Model;
    model["bunny"] -> geometry = geometry["bunny"];
    model["bunny"] -> material = material["turquoise"];
    model["floor"] = new Model;
    model["floor"] -> geometry = geometry["cube"];
    model["floor"] -> material = material["floor"];

    // Create a light palette
    light = new Light;
    light -> position = vec4(6.0f,4.0f,2.0f,0.0f);
    light -> color = 1.0f*vec4(1.0f,1.0f,1.0f,1.0f);
    light -> calculate();
    
    // Build the scene graph
    node["table"] = new Node;
    node["table top"] = new Node;
    node["table leg"] = new Node;
    node["teapot1"] = new Node;
    node["teapot2"] = new Node;
    node["bunny"] = new Node;
    node["floor"] = new Node;
    
    
    node["table"] -> childnodes.push_back( node["table top"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.0f,1.2f,0.0f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-0.9f,0.0f,-0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-0.9f,0.0f,0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.9f,0.0f,0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.9f,0.0f,-0.4f)) );
    
    node["table leg"] -> models.push_back( model["table piece"] );
    node["table leg"] -> modeltransforms.push_back( translate(vec3(0.0f,0.5f,0.0f)) * scale(vec3(0.2f,1.0f,0.2f)) );
    
    node["table top"] -> models.push_back( model["table piece"] );
    node["table top"] -> modeltransforms.push_back( translate(vec3(0.0f,-0.1f,0.0f)) * scale(vec3(2.0f,0.2f,1.0f)) );
    node["table top"] -> childnodes.push_back( node["teapot1"] );
    node["table top"] -> childtransforms.push_back( translate(vec3(-0.5f,0.0f,0.0f)) );
    node["table top"] -> childnodes.push_back( node["teapot2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 0.5f,0.0f,0.0f)) * rotate( -120.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    
    node["teapot1"] -> models.push_back( model["teapot1"] );
    node["teapot1"] -> modeltransforms.push_back( scale(vec3(0.5f)) );
    node["teapot2"] -> models.push_back( model["teapot2"] );
    node["teapot2"] -> modeltransforms.push_back( scale(vec3(1.0f,1.5f,1.0f)) * scale(vec3(0.5f)) );
    
    node["bunny"] -> models.push_back( model["bunny"] );
    node["bunny"] -> modeltransforms.push_back( scale(vec3(0.8f)) * translate(vec3(0.0f,1.0f,0.0f)) );
    
    node["floor"] -> models.push_back( model["floor"] );
    node["floor"] -> modeltransforms.push_back( scale(vec3(5.0f,0.05f,5.0f)));

    node["world"] -> childnodes.push_back( node["table"] );
    node["world"] -> childtransforms.push_back( mat4(1.0f) );
    node["world"] -> childnodes.push_back( node["bunny"] );
    node["world"] -> childtransforms.push_back( translate(vec3(-1.8f,0.0f,0.0f)) * rotate( 90.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ));
    node["world"] -> childnodes.push_back( node["floor"] );
    node["world"] -> childtransforms.push_back(translate(vec3(0.0f,-0.02f, 0.0f)));
    // Put a camera
    camera = new Camera;
    camera -> target_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> eye_default = vec3( 0.0f, 1.0f, 5.0f );
    camera -> up_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> reset();
    
    // Initialize shaders
    shader = new SurfaceShader;
    shader -> read_source( "shaders/projective.vert", "shaders/lighting.frag" );
    shader -> compile();
    shader -> initUniforms();
    depthshader = new DepthShader;
    depthshader -> read_source( "shaders/lightspace.vert", "shaders/depth.frag" );
    depthshader -> compile();
    depthshader -> initUniforms();



}
