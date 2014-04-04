#version 330 core

in vec4 diffuseColor;
in vec3 vertexNormal;
in vec3 cameraSpacePosition;

out vec4 outputColor;

const vec4 specularColor = vec4(0.2, 0.2, 0.2, 1.0);
const float specularShininess = 0.1;
const float maxIntensity = 0.5;
const float gamma = 0.5;

struct Light
{
    vec4 cameraSpaceLightPos;
    vec4 lightIntensity;
};

const int MaxNnumberOfLights = 8;

layout (std140) uniform LightsBlock
{
    vec4 ambientIntensity;
    float lightAttenuation;
    int numberOfLights;
    Light lights[MaxNnumberOfLights];
};

float CalcAttenuation(in vec3 cameraSpacePosition,
                      in vec3 cameraSpaceLightPos,
                      out vec3 lightDirection)
{
    vec3 lightDifference =  cameraSpaceLightPos - cameraSpacePosition;
    float lightDistanceSqr = dot(lightDifference, lightDifference);
    lightDirection = lightDifference * inversesqrt(lightDistanceSqr);
    
    return (1 / ( 1.0 + lightAttenuation * lightDistanceSqr));
}

vec4 ComputeLighting(in Light lightData)
{
    vec3 lightDir;
    vec4 lightIntensity;
    if(lightData.cameraSpaceLightPos.w == 0.0)
    {
        lightDir = vec3(lightData.cameraSpaceLightPos);
        lightIntensity = lightData.lightIntensity;
    }
    else
    {
        float atten = CalcAttenuation(cameraSpacePosition,
            lightData.cameraSpaceLightPos.xyz, lightDir);
        lightIntensity = atten * lightData.lightIntensity;
    }
    
    vec3 surfaceNormal = normalize(vertexNormal);
    float cosAngIncidence = dot(surfaceNormal, lightDir);
    cosAngIncidence = cosAngIncidence < 0.0001 ? 0.0 : cosAngIncidence;
    
    vec3 viewDirection = normalize(-cameraSpacePosition);
    
    vec3 halfAngle = normalize(lightDir + viewDirection);
    float angleNormalHalf = acos(dot(halfAngle, surfaceNormal));
    float exponent = angleNormalHalf / specularShininess;
    exponent = -(exponent * exponent);
    float gaussianTerm = exp(exponent);

    gaussianTerm = cosAngIncidence != 0.0 ? gaussianTerm : 0.0;
    
    vec4 lighting = diffuseColor * lightIntensity * cosAngIncidence;
    lighting += specularColor * lightIntensity * gaussianTerm;
    
    return lighting;
}

void main()
{
    vec4 accumLighting = diffuseColor * ambientIntensity;
    for(int light = 0; light < numberOfLights; light++)
    {
        accumLighting += ComputeLighting(lights[light]);
    }

    vec4 gamma = vec4(1.0 / gamma);
    gamma.w = 1.0;
    outputColor = pow(accumLighting, gamma);

    outputColor = accumLighting / maxIntensity;
}