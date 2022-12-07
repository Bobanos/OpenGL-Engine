#version 400

#define MAX_LIGHTS 100

uniform vec3 cameraPosition;
uniform vec3 cameraOrientation;

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_color;

vec3 point_light(vec3 color, vec3 worldPos, vec3 normalVector, vec3 lightPosition, vec3 lightColor) {

    const float specularStrength = 0.4;

    float dist = length(lightPosition - worldPos);
    float attenuation = clamp(5.0 / dist, 0.0, 1.0);

    vec3 viewDir = normalize(cameraPosition - worldPos);
    vec3 lightDir = normalize(lightPosition - worldPos);
    vec3 reflectionDir = reflect(-lightDir, normalVector);

    float dot_product = dot(lightDir, normalVector);
    vec3 diffuse = max(dot_product, 0.0) * color * attenuation;
    // vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);

    float specValue = pow(max(dot(viewDir, reflectionDir), 0.0), 16);
    vec3 spec = specularStrength * specValue * lightColor;
    if (dot_product < 0.0) {
        spec = vec3(0.0);
    }
    vec3 specular = attenuation * spec;

    return diffuse + specular;
}

vec3 spotlight(vec3 color, vec3 worldPos, vec3 normalVector, vec3 lightPosition, vec3 lightDirection, vec3 lightColor, float cutoff) {

    vec3 lightDir = normalize(lightPosition - worldPos);

    float theta = dot(lightDir, normalize(-lightDirection));
    if (theta <= cutoff) {
        return vec3(0.0, 0.0, 0.0);
    }

    const float specularStrength = 0.4;

    float dist = length(lightPosition - worldPos);
    float attenuation = clamp(5.0 / dist, 0.0, 1.0);

    vec3 viewDir = normalize(cameraPosition - worldPos);
    vec3 reflectionDir = reflect(-lightDir, normalVector);

    float dot_product = dot(lightDir, normalVector);
    vec3 diffuse = max(dot_product, 0.0) * color * attenuation;

    float specValue = pow(max(dot(viewDir, reflectionDir), 0.0), 16);
    vec3 spec = specularStrength * specValue * lightColor;
    if (dot_product < 0.0) {
        spec = vec3(0.0);
    }
    vec3 specular = attenuation * spec;

    return diffuse + specular;
}

vec3 directional_light(vec3 color, vec3 worldPos, vec3 normalVector, vec3 lightDirection, vec3 lightColor) {

    const float specularStrength = 0.4;

    vec3 lightDir = normalize(-lightDirection);
    float dot_product = dot(lightDir, normalVector);
    vec3 diffuse = max(dot_product, 0.0) * lightColor;

    vec3 viewDir = normalize(cameraPosition - worldPos);
    vec3 reflectionDir = reflect(-lightDir, normalVector);

    float specValue = pow(max(dot(viewDir, reflectionDir), 0.0), 16);
    vec3 spec = specularStrength * specValue * lightColor;
    if (dot_product < 0.0) {
        spec = vec3(0.0);
    }

    return (diffuse + spec) * color;
}

void main () {

    vec3 fragColor = vec3(0.0, 0.0, 0.0);

    vec3 worldPos = vec3(ex_worldPosition);
    vec3 normalVector = normalize(ex_worldNormal);

    vec3 color = vec3(0.385 ,0.647 ,0.812);

    //point_light
    vec3 lightPosition = vec3(-20.0, 5.0, -10.0);
    vec3 lightColor = vec3(1.0, 0.0, 0.0);
    fragColor += point_light(color, worldPos, normalVector, lightPosition, lightColor);


    //directional_light
    lightPosition = vec3(0.0, 5.0, -10.0);
    lightColor = vec3(0.0, 0.5, 0.0);
    vec3 lightDirection = vec3(-1.0, -1.0, 1.0);
    fragColor += directional_light(color, worldPos, normalVector, lightDirection, lightColor);

    //spotlight
    lightPosition = vec3(20.0, 5.0, -10.0);
    lightColor = vec3(0.0, 0.0, 1.0);
    lightDirection = vec3(-1.0, -1.0, -1.0);
    float cutoff = 100;
    fragColor += spotlight(color, worldPos, normalVector, lightPosition, lightDirection, lightColor, cutoff);

    //flashlight
    lightColor = vec3(1.0, 1.0, 1.0);
    cutoff = 100;
    fragColor += spotlight(color, worldPos, normalVector, cameraPosition, cameraOrientation, lightColor, cutoff);

    out_color = vec4(fragColor, 1.0);
}