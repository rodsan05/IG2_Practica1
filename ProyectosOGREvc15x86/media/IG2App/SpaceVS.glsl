#version 330 core
in vec4 vertex; // atributos de los v�rtices a procesar
in vec2 uv0; // coordenadas de textura 0
uniform float st;
uniform mat4 modelViewProjMat; // constante de programa
out vec2 vUv0; // out del vertex shader
out vec2 vUv1; // out del vertex shader

void main() {
    
    vUv0 = uv0; // se pasan las coordenadas de textura

    //zoom
    float ZF = st * 0.25 + 0.75;
    vUv1 = (uv0 - 0.5) * ZF + 0.5;

    gl_Position = modelViewProjMat * vertex; //obligatorio
                                            // (Clipping coordinates)
}