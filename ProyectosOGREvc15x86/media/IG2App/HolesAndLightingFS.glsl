#version 330 core
uniform sampler2D corrosion;
uniform sampler2D texFront;
uniform sampler2D texBack;
uniform float flipping;
in vec2 vUv0;
in vec3 vWorldNormal; // coordenadas de la normal en Xxx space
in vec4 vWorldVertex; // coordenadas del vértice en Xxx space
out vec4 fFragColor;

uniform mat4 worldMat; // Model matrix
uniform mat4 normalMat;

uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

uniform vec3 frontDiffuse;
uniform vec3 backDiffuse;

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPosition.xyz; // directional light ?
    
    if (lightPosition.w == 1) // positional light ?
        lightDir = lightPosition.xyz - cVertex;
    
    return max(dot(cNormal, normalize(lightDir)), 0.0); // dot: coseno ángulo
}

void main(void) {
    vec3 corrosionMap = vec3(texture(corrosion, vUv0));
    vec3 textureFront = vec3(texture(texFront, vUv0));
    vec3 textureBack = vec3(texture(texBack, vUv0));

    vec3 worldVertex = vec3(worldMat * vWorldVertex);
    vec3 worldNormal = normalize(vec3(normalMat * vec4(vWorldNormal,0)));

    //lighting
    vec3 diffuse = diff(worldVertex, worldNormal) * lightDiffuse * frontDiffuse;
    vec3 vFrontColor = diffuse; // + specular
    
    diffuse = diff(worldVertex, -worldNormal) * lightDiffuse * backDiffuse;
    vec3 vBackColor = diffuse; // + specular

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