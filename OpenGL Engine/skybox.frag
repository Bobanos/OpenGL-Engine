#version 400

out vec4 out_color;

in vec3 texCoords;

uniform samplerCube skybox;

void main() {
//    out_color = vec4(texCoords, 1.0);
    out_color = texture(skybox, texCoords);
}