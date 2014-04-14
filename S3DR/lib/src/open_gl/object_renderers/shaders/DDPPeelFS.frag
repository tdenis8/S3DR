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


layout(location = 0) out vec4 vFragColor0;	//output to target 0
layout(location = 1) out vec4 vFragColor1;	//output to target 1
layout(location = 2) out vec4 vFragColor2;	//output to target 2	

//uniforms
uniform sampler2DRect  depthBlenderTex;	//depth blending output
uniform sampler2DRect  frontBlenderTex;	//front blending output
uniform float alpha;					//fragment alpha

#define MAX_DEPTH 1.0	//max depth value to clear the depth with
 
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
	//get the current fragment depth
	float fragDepth = gl_FragCoord.z;
	//get the depth value from the depth blending output
	vec2 depthBlender = texture(depthBlenderTex, gl_FragCoord.xy).xy;
	//get the front blending output
	vec4 forwardTemp = texture(frontBlenderTex, gl_FragCoord.xy);

	// Depths and 1.0-alphaMult always increase
	// so we can use pass-through by default with MAX blending
	vFragColor0.xy = depthBlender;
	
	// Front colors always increase (DST += SRC*ALPHA_MULT)
	// so we can use pass-through by default with MAX blending
	vFragColor1 = forwardTemp;
	
	// Because over blending makes color increase or decrease,
	// we cannot pass-through by default.
	// Each pass, only one fragment can a color greater than 0
	vFragColor2 = vec4(0.0);

	float nearestDepth = -depthBlender.x;
	float farthestDepth = depthBlender.y;
	float alphaMultiplier = 1.0 - forwardTemp.w;

	if (fragDepth < nearestDepth || fragDepth > farthestDepth) {
		// Skip this depth in the peeling algorithm
		vFragColor0.xy = vec2(-MAX_DEPTH);
		return;
	}
	
	if (fragDepth > nearestDepth && fragDepth < farthestDepth) {
		// This fragment needs to be peeled again
		vFragColor0.xy = vec2(-fragDepth, fragDepth);
		return;
	}	 
	
    vec4 accumLighting = diffuseColor * ambientIntensity;
    for(int light = 0; light < numberOfLights; light++)
    {
        accumLighting += ComputeLighting(lights[light]);
    }

    vec4 gamma = vec4(1.0 / gamma);
    gamma.w = 1.0;
    outputColor = pow(accumLighting, gamma);

    vec4 outputColor = accumLighting / maxIntensity;

	// If we made it here, this fragment is on the peeled layer from last pass
	// therefore, we need to shade it, and make sure it is not peeled any farther
	vFragColor0.xy = vec2(-MAX_DEPTH);
	
	//if the fragment depth is the nearest depth, we blend the colour 
	//to the second attachment
	if (fragDepth == nearestDepth) {
		vFragColor1.xyz += outputColor.rgb * alpha * alphaMultiplier;
		vFragColor1.w = 1.0 - alphaMultiplier * (1.0 - alpha);
	} else {
		//otherwise we write to the thrid attachment
		vFragColor2 += vec4(outputColor.rgb, alpha);
}
}