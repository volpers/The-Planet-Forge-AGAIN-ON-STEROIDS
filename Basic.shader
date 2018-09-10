#shader vertex
#version 330 core

layout(location=0) in vec3  position;
layout(location = 1) in vec2 texCoord;	 

out vec2 v_TexCoord;	//output to fragment-shader
uniform mat4 u_MVP; //Model-View-Projection-Matrix

void main()
{
	gl_Position = u_MVP * vec4(position,1.0);
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location=0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 v_TexCoord;	//input from vertex shader

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color=texColor * u_Color;
};