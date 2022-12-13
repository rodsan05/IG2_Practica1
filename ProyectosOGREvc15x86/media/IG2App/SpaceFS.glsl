#version 330 core
uniform sampler2D lightMap;
uniform sampler2D spaceSky;
in vec2 vUv0;
in vec2 vUv1;
out vec4 fFragColor;

void main(void) 
{
    vec3 texture1 = vec3(texture(lightMap, vUv0));
    vec3 texture2 = vec3(texture(spaceSky, vUv1));

    vec3 modulatedText = texture1 * texture2;

    fFragColor = vec4(modulatedText, 1.0);
}