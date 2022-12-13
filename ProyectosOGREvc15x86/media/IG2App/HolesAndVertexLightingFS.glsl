#version 330 core
uniform sampler2D corrosion;
uniform sampler2D texFront;
uniform sampler2D texBack;
uniform float flipping;
in vec2 vUv0;
in vec3 vFrontColor; // color rgb de la iluminación de la cara front
in vec3 vBackColor; // color rgb de la iluminación de la cara back
out vec4 fFragColor;

void main(void) {
    vec3 corrosionMap = vec3(texture(corrosion, vUv0));
    vec3 textureFront = vec3(texture(texFront, vUv0));
    vec3 textureBack = vec3(texture(texBack, vUv0));

    vec3 color;

    if (corrosionMap.r > 0.6)
    {
        discard;
    }

    bool frontFacing = (flipping > -1)? gl_FrontFacing : !gl_FrontFacing;
    
    if (frontFacing)
    {
        color = vFrontColor * textureFront;
    }

    else 
    {
        color = vBackColor * textureBack;        
    }

    fFragColor = vec4(color, 1.0);
}