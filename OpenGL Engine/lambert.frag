#version 400

in vec4 worldPos;
in vec4 worldNorm;

out vec4 outColour;

void main () {
    vec4 lightPosition = vec4 (10.0, 10.0, 10.0, 10.0);
    vec4 lightVector = normalize(lightPosition - worldPos);

    float d = dot(lightVector, normalize(worldNorm));
    float dotLN = max(d, 0.0);
    vec4 diffuse = dotLN * vec4 (0.385 ,0.647 ,0.812 ,1.0);
    vec4 ambient = vec4 (0.1 ,0.1 ,0.1 ,1.0);
    outColour = ambient + diffuse;
}