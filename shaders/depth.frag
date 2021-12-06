#version 330 core
layout (location = 0) out vec4 fragColor;

void main (void){
    // linearization and scaling of colors. source from piazza post
    float near = 0.15f;
    float far = 10.0f;
    float ndc_z = 2 * gl_FragCoord.z - 1;
    float lin_z = (2.0 * near * far) / (far + near - ndc_z * (far - near)); 
    fragColor = vec4(vec3(lin_z / (far - near)), 1.0f);
}