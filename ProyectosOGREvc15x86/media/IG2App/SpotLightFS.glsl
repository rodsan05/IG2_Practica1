#version 330 core
in vec2 vUv0;
in vec3 vWorldNormal; // coordenadas de la normal en Xxx space
in vec4 vWorldVertex; // coordenadas del vértice en Xxx space
out vec4 fFragColor;

uniform sampler2D stones;
uniform mat4 worldMat; // Model matrix
uniform mat4 normalMat;
uniform vec4 lightPosition;
uniform float cutoff;

void main(void) {
    vec3 texture = vec3(texture(stones, vUv0));

    vec3 worldVertex = vec3(worldMat * vWorldVertex);
    vec3 worldNormal = normalize(vec3(normalMat * vec4(vWorldNormal,0)));

    vec3 color = texture;
    if (dot(worldNormal, normalize(worldVertex - vec3(vec3(lightPosition)))) < cutoff * 0.15 + 0.85)
    {
        color = 0.2 * texture;    
    }  

    fFragColor = vec4(color, 1.0);
}