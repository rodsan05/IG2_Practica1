#version 330 core
in vec4 vertex; // layout (location = 0) in vec4 vertex;
in vec3 normal; // layout (location = 1) in vec3 normal;

in vec2 uv0; // layout (location = 2) in vec2 uv0;
out vec2 vUv0; // coordenadas de textura

out vec3 vFrontColor; // color rgb de la iluminación de la cara front
out vec3 vBackColor; // color rgb de la iluminación de la cara back

uniform mat4 modelViewMat; // View*Model matrix
uniform mat4 modelViewProjMat; // Projection*View*Model matrix
uniform mat4 normalMat; // = transpose(inverse(modelView))

uniform vec3 lightDiffuse;
uniform vec4 lightPosition; // datos de la fuente de luz en view space
// lightPosition.w == 0 -> directional light
// lightPosition.w == 1 -> positional light

uniform vec3 frontDiffuse;
uniform vec3 backDiffuse;

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPosition.xyz; // directional light ?
    
    if (lightPosition.w == 1) // positional light ?
        lightDir = lightPosition.xyz - cVertex;
    
    return max(dot(cNormal, normalize(lightDir)), 0.0); // dot: coseno ángulo
}

void main() {

    // diffuse en view space
    vec3 viewVertex = vec3(modelViewMat * vertex);
    vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
    
    vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * frontDiffuse;
    vFrontColor = diffuse; // + specular
    
    diffuse = diff(viewVertex, -viewNormal) * lightDiffuse * backDiffuse;
    vBackColor = diffuse; // + specular

    vUv0 = uv0; // se pasan las coordenadas de textura

    gl_Position = modelViewProjMat * vertex; //obligatorio
                                            // (Clipping coordinates)
}