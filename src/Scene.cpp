/**************************************************
Scene.cpp contains the implementation of the draw command
*****************************************************/
#include "Scene.h"
#include "Cube.h"
#include "Obj.h"

// The scene init definition 
#include "Scene.inl"


using namespace glm;
// drawing the scene. passes both the light view and projection to the shader
// then for each model, passes the model transform and material to the shader
// uses the model transformation matrix instead of the modelview like in HW3
void Scene::draw(void){
    glUseProgram(shader -> program);
    camera -> computeMatrices();
    shader -> view = camera -> view;
    shader -> projection = camera -> proj;
    shader -> lightposition = light -> position;
    shader -> lightcolor =  light -> color;
    shader -> lightprojection = light -> proj;
    shader -> lightview = light -> view;
    
    // Define stacks for depth-first search (DFS)
    std::stack < Node* > dfs_stack;
    std::stack < mat4 >  matrix_stack;
    
    // Initialize the current state variable for DFS
    Node* cur = node["world"]; // root of the tree
    mat4 cur_M = mat4(); // Initially, we are at the "world" node, whose modelview matrix is just camera's view matrix.
    
    dfs_stack.push( cur );
    matrix_stack.push( cur_M );
    while( ! dfs_stack.empty() ){
        
        // top-pop the stacks
        cur = dfs_stack.top();        dfs_stack.pop();
        // pop the matrix
        cur_M = matrix_stack.top();
        matrix_stack.pop();
        
        // draw all the models at the current node
        for ( unsigned int i = 0; i < cur -> models.size(); i++ ){
            // Prepare to draw the geometry. Assign the modelview and the material.
            shader -> model = cur_M * cur -> modeltransforms[i];
            shader -> material  = ( cur -> models[i] ) -> material;
            
            // The draw command
            shader -> setUniforms();
            ( cur -> models[i] ) -> geometry -> draw();
        }
        
        // Continue the DFS: put all the child nodes of the current node in the stack
        for ( unsigned int i = 0; i < cur -> childnodes.size(); i++ ){
            dfs_stack.push( cur -> childnodes[i] );
            matrix_stack.push( cur_M * cur -> childtransforms[i] );
        }
        
    } // End of DFS while loop.
    
}

void Scene::drawDepth(void){
    glUseProgram( depthshader -> program );
    depthshader -> projection = light -> proj;
    depthshader -> view = light -> view;
    
    // Define stacks for depth-first search (DFS)
    std::stack < Node* > dfs_stack;
    std::stack < mat4 >  matrix_stack; 

    // Initialize the current state variable for DFS
    Node* cur = node["world"]; // root of the tree
    mat4 cur_M = mat4(); 

    dfs_stack.push( cur );
    matrix_stack.push( cur_M );
    while( ! dfs_stack.empty() ){
        
        // top-pop the stacks
        cur = dfs_stack.top();        dfs_stack.pop();
        // pop the matrix
        cur_M = matrix_stack.top();
        matrix_stack.pop();
        
        // draw all the models at the current node
        for ( unsigned int i = 0; i < cur -> models.size(); i++ ){
            // model transform
            depthshader -> model = cur_M * cur -> modeltransforms[i]; 
            // The draw command
            depthshader -> setUniforms();
            ( cur -> models[i] ) -> geometry -> draw();
        }
        
        // Continue the DFS: put all the child nodes of the current node in the stack
        for ( unsigned int i = 0; i < cur -> childnodes.size(); i++ ){
            dfs_stack.push( cur -> childnodes[i] );
            matrix_stack.push( cur_M * cur -> childtransforms[i] );
        }
        
    } // End of DFS while loop.
    
}



