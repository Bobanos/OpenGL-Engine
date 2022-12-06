#version 400

out vec4 frag_colour;

uniform sampler2D textureUnitID;

in vec2 uv;

void main () {
     //frag_colour = vec4(normal,1.0);
     //frag_colour = vec4(uv,1.0,1.0); //test na funkcnost uv souøadnic
     frag_colour = texture(textureUnitID, uv);
}