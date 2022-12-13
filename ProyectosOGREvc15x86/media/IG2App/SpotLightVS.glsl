#version 330 core
in vec4 vertex; // layout (location = 0) in vec4 vertex;
in vec3 normal; // layout (location = 1) in vec3 normal;

in vec2 uv0; // layout (location = 2) in vec2 uv0;
out vec2 vUv0; // coordenadas de textura
out vec3 vWorldNormal; // coordenadas de la normal en Xxx space
out vec4 vWorldVertex; // coordenadas del vértice en Xxx space

uniform mat4 modelViewProjMat; // Projection*View*Model matrix

void main() {

    vUv0 = uv0; // se pasan las coordenadas de textura

    vWorldNormal = normal;
    vWorldVertex = vertex;

    gl_Position = modelViewProjMat * vertex; //obligatorio
                                            // (Clipping coordinates)
}