#version 330 core
uniform sampler2D checker;
uniform sampler2D bumpyMetal;
uniform sampler2D spaceSky;
in vec2 vUv0;
in vec2 vUv1;
out vec4 fFragColor;

void main(void) {
    vec3 checkerMap = vec3(texture(checker, vUv0));
    vec3 texture1 = vec3(texture(bumpyMetal, vUv0));
    vec3 texture2 = vec3(texture(spaceSky, vUv1));

    if (checkerMap.r == 0)
    {
       fFragColor = vec4(texture2, 1.0);
    }
    else
    {
       fFragColor = vec4(texture1, 1.0);
    }
    
    // vec3 modulatedText1 = texture1 * checkerMap;
    // vec3 modulatedText2 = texture2 * checkerMap * -1;

    // vec3 modulatedText = modulatedText1 + modulatedText2;

    // fFragColor = vec4(modulatedText, 1.0);
}