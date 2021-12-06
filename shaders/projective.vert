# version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 lightview;
uniform mat4 lightprojection;

out vec4 position;
out vec3 normal;
smooth out vec4 positionLS;

void main(){
    gl_Position = projection * view * model * vec4( vertex_position, 1.0f );
    // forward the raw position and normal in the model coord to frag shader
    position = vec4(vertex_position, 1.0f );
    normal = vertex_normal;
    positionLS = lightprojection * lightview * model * vec4(vertex_position,1.0f);
}
