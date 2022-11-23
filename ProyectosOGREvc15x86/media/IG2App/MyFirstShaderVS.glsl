#version 330 core
in vec4 vertex; // atributos de los v�rtices a procesar
in vec2 uv0; // coordenadas de textura 0
uniform mat4 modelViewProjMat; // constante de programa
out vec2 vUv0; // out del vertex shader

void main() {
    
    gl_Position = modelViewProjMat * vertex; //obligatorio
                                            // (Clipping coordinates)
}