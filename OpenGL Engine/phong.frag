#version 400

in vec4 worldPos;
in vec4 worldNorm;

uniform vec3 cameraPos;

out vec4 outColour;

void main () {
    vec4 colour = vec4 (0.385 ,0.647 ,0.812 ,1.0);
    vec4 ambient = vec4 (0.1 ,0.1 ,0.1 ,1.0);

    vec3 lightVector = normalize(vec3(0.0, 0.0, 0.0)  - vec3(worldPos));
    vec3 normal = normalize(vec3(worldNorm));

    float dot_product = max(dot((normal), (lightVector)), 0.0);
    vec4 diffuse = dot_product * colour;   

    vec3 viewDirection = normalize(cameraPos - vec3(worldPos)); 
    vec3 reflectionDirection = reflect((-lightVector), (normal));                  
    float specular = pow(max(dot(viewDirection, (reflectionDirection)), 0.0f), 40);

    outColour = ambient + diffuse + specular;
}