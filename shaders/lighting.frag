#version 330 core

in vec4 position; // raw position in the model coord
in vec3 normal;   // raw normal in the model coord
smooth in vec4 positionLS; // position in light coord

uniform mat4 model; // from model coord to eye coord
uniform mat4 view;      // from world coord to eye coord
uniform mat4 lightview;
uniform mat4 lightprojection;

// Material parameters
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emision;
uniform float shininess;

// Light source parameters
uniform bool enablelighting;
uniform vec4 lightposition;
uniform vec4 lightcolor;
uniform bool depthshade;

// shadowmap
uniform sampler2D shadowMap;

// Output the frag color
out vec4 fragColor;

vec4 compute_diffuse_part (vec4 diffuse, vec4 n, vec4 lj ){
    return diffuse*max(dot(n,lj),0);
}
vec4 compute_specular_part (vec4 specular, vec4 n, vec4 hj, float shiny){
    return specular*pow(max(dot(n,hj),0),shiny);
}
float compute_shadow (vec3 lightVec){
    // get sampled depth from texture
    vec3 l_pos = positionLS.xyz / positionLS.w;
    l_pos = l_pos * 0.5 + 0.5;
    float sampledDepth = texture(shadowMap, l_pos.xy).r;
    float currDepth = l_pos.z;
    vec3 normal = normalize(normal);
    float bias = max(0.05 * (1.0 - dot(normal, lightVec)), 0.005);
    if (currDepth-bias > sampledDepth){
        return 1.0f;
    }
    else {
        return 0.0f;
    }
}
void main (void){
    
    if(depthshade){
        vec3 l_pos = positionLS.xyz / positionLS.w;
        l_pos = l_pos * 0.5 + 0.5;
        float sampledDepth = texture(shadowMap, l_pos.xy).r;
        fragColor = vec4(vec3(sampledDepth),1.0f);
        return;
    }
    vec4 sum;
    vec4 N = vec4(normalize(inverse(transpose(mat3(model*view)))*normal),0); // normal in the eye coords
    vec4 eyeModelPos = model*view*position; // put the model in eye coords
    vec3 v = normalize(eyeModelPos.w*vec3(0,0,0)-
                       1*vec3(eyeModelPos.x,eyeModelPos.y,eyeModelPos.z));
    vec4 eyeLightPos = view*lightposition; // put the light in eye coords
    vec3 lightVec = normalize(
        eyeModelPos.w*vec3(eyeLightPos.x,eyeLightPos.y,eyeLightPos.z)-
        eyeLightPos.w*vec3(eyeModelPos.x,eyeModelPos.y,eyeModelPos.z));
    vec4 temp = ambient;
    if (!enablelighting){
        temp += compute_diffuse_part(diffuse, N, vec4(lightVec,0));
        temp += compute_specular_part(specular, N, 
                    vec4(normalize(v+lightVec),0),
                    shininess);
        temp *= lightcolor;
        sum += temp;
    }
    else {
        float inshadow = compute_shadow(lightVec);
        temp += (1.0f-inshadow)*compute_diffuse_part(diffuse, N, vec4(lightVec,0));
        temp += (1.0f-inshadow)*compute_specular_part(specular, N, 
                    vec4(normalize(v+lightVec),0),
                    shininess);
        temp *= lightcolor;
        sum += temp;
    }
    fragColor = sum + emision;
    // HW3: You will compute the lighting here.
        
    
}
