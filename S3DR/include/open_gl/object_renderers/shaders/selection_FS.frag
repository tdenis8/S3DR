#version 330 core

out uvec3 FragColor;

uniform uint SceneObjectKey; 
uniform uint EntryIndex; 

void main()
{
    FragColor = uvec3(SceneObjectKey, EntryIndex, gl_PrimitiveID + 1);
}
