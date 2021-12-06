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
    geometry["bunny"] = new Obj;
    geometry["cube"] -> init();
    geometry["bunny"] -> init("models/bunny.obj");
    
    // Create a material palette
    material["wood"] = new Material;
    material["wood"] -> ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["wood"] -> diffuse = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> specular = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> shininess = 100.0f;

    material["limb"] = new Material;
    material["limb"] -> ambient = vec4(.8f,0.5961f,0.4431f,1.0f);
    material["limb"] -> diffuse = vec4(1.0f,0.7961f,0.6431f,1.0f);
    material["limb"] -> specular = vec4(1.0f,0.7961f,0.6431f,1.0f);
    material["limb"] -> shininess = 100.0f;
    
    material["ceramic"] = new Material;
    material["ceramic"] -> ambient = vec4(0.02f, 0.07f, 0.2f, 1.0f);
    material["ceramic"] -> diffuse = vec4(0.2f, 0.25f, 0.6f, 1.0f);
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
    
    material["bulb"] = new Material;
    material["bulb"] -> ambient = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    material["bulb"] -> emision = vec4(0.9f,0.2f,1.0f,1.0f);
    material["bulb"] -> shininess = 200.0f;
    
    // Create a model palette

    model["limb"] = new Model;
    model["limb"] -> geometry = geometry["cube"];
    model["limb"] -> material = material["limb"];
    model["body"] = new Model;
    model["body"] -> geometry = geometry["cube"];
    model["body"] -> material = material["bulb"];
    model["head"] = new Model;
    model["head"] -> geometry = geometry["bunny"];
    model["head"] -> material = material["silver"];

    model["building"] = new Model;
    model["building"] -> geometry = geometry["cube"];
    model["building"] -> material = material["wood"];

    model["bunny1"] = new Model;
    model["bunny1"] -> geometry = geometry["bunny"];
    model["bunny1"] -> material = material["turquoise"];

    model["bunny2"] = new Model;
    model["bunny2"] -> geometry = geometry["bunny"];
    model["bunny2"] -> material = material["ceramic"];
    // Create a light palette
    light["sun"] = new Light;
    light["sun"] -> position = vec4(3.0f,2.0f,1.0f,0.0f);
    light["sun"] -> color = 1.0f*vec4(1.0f,1.0f,1.0f,1.0f);
    
    light["bulb"] = new Light;
    light["bulb"] -> position = vec4(0.0f,2.0f,0.0f,0.0f);
    light["bulb"] -> color = 1.5f * vec4(1.0f,0.2f,0.1f,1.0f);
    
    // Build the scene graph
    // tposer
    node["tpose"] = new Node;
    node["arm"] = new Node;
    node["leg"] = new Node;
    node["body"] = new Node;
    node["head"] = new Node;
    node["bunny1"] = new Node;
    node["bunny2"] = new Node;

    node["tpose"] -> childnodes.push_back( node["arm"] );
    node["tpose"] -> childtransforms.push_back( translate(vec3(0.5f,0.25f,0.0f)) );
    node["tpose"] -> childnodes.push_back( node["arm"] );
    node["tpose"] -> childtransforms.push_back( translate(vec3(-0.5f,0.25f,0.0f)) );
    node["tpose"] -> childnodes.push_back( node["leg"] );
    node["tpose"] -> childtransforms.push_back( translate(vec3(-0.15f,-0.7f,0.0f)) );
    node["tpose"] -> childnodes.push_back( node["leg"] );
    node["tpose"] -> childtransforms.push_back( translate(vec3(0.15f,-0.7f,0.0f)) );
    node["tpose"] -> childnodes.push_back( node["body"] );
    node["tpose"] -> childtransforms.push_back( translate(vec3(0.0f)) );
    node["tpose"] -> childnodes.push_back( node["head"] );
    node["tpose"] -> childtransforms.push_back( translate(vec3(0.15f,0.55f,0.0f)) );

    node["arm"] -> models.push_back( model["limb"] );
    node["arm"] -> modeltransforms.push_back( scale(vec3(0.8f,0.2f,0.2f)));
    node["body"] -> models.push_back( model["body"] );
    node["body"] -> modeltransforms.push_back( scale(vec3(0.6f,0.9f,0.4f)));
    node["leg"] -> models.push_back( model["limb"] );
    node["leg"] -> modeltransforms.push_back( scale(vec3(0.23f,1.0f,0.23f)));
    node["head"] -> models.push_back( model["head"] );
    node["head"] -> modeltransforms.push_back( rotate( -90.0f * float(M_PI)/180.0f, vec3(0.0f,1.0f,0.0f)) * scale(vec3(0.2f,0.3f,0.8f)));
    
    //room
    node["room"] = new Node;
    node["floor"] = new Node;
    node["wall"] = new Node;

    node["room"] -> childnodes.push_back( node["floor"] );
    node["room"] -> childtransforms.push_back( translate(vec3(0.0f,-1.0f,0.0f)) );
    node["room"] -> childnodes.push_back( node["wall"] );
    node["room"] -> childtransforms.push_back( translate(vec3(1.0f,0.0f,0.0f)) );
    node["room"] -> childnodes.push_back( node["wall"] );
    node["room"] -> childtransforms.push_back( rotate( 90.0f * float(M_PI)/180.0f, vec3(0.0f,1.0f,0.0f)) * translate(vec3(1.0f,0.0f,0.0f)) );

    node["floor"] -> models.push_back( model["building"] );
    node["floor"] -> modeltransforms.push_back( scale(vec3(2.0f,0.1f,2.0f)));
    node["wall"] -> models.push_back( model["building"] );
    node["wall"] -> modeltransforms.push_back( scale(vec3(0.1f,2.0f,2.0f)));

    // bunnies
    node["bunny1"] -> models.push_back( model["bunny1"] );
    node["bunny1"] -> modeltransforms.push_back( mat4(1.0f) );
    node["bunny2"] -> models.push_back( model["bunny2"] );
    node["bunny2"] -> modeltransforms.push_back( mat4(1.0f) );

    // floor
    node["floor"] -> childnodes.push_back( node["bunny1"] );
    node["floor"] -> childtransforms.push_back( scale(vec3(0.2f,0.2f,0.2f)) *  translate(vec3(3.2f,1.0f,-4.4f)));
    node["floor"] -> childnodes.push_back( node["bunny2"] );
    node["floor"] -> childtransforms.push_back( scale(vec3(0.2f,0.2f,0.2f)) * translate(vec3(3.9f,1.0f,-3.2f)) );

    node["world"] -> childnodes.push_back( node["tpose"] );
    node["world"] -> childtransforms.push_back( translate(vec3(0.0f,1.0f,0.0f)) );
    node["world"] -> childnodes.push_back( node["room"] );
    node["world"] -> childtransforms.push_back( rotate(45.0f * float(M_PI)/180.0f, vec3(0.0f,1.0f,0.0f))*translate(vec3(0.5f,0.4f,-0.5f)) );
    // Put a camera
    camera = new Camera;
    camera -> target_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> eye_default = vec3( 0.0f, 1.0f, 5.0f );
    camera -> up_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> reset();
    
    // Initialize shader
    shader = new SurfaceShader;
    shader -> read_source( "shaders/projective.vert", "shaders/lighting.frag" );
    shader -> compile();
    glUseProgram(shader -> program);
    shader -> initUniforms();
}
