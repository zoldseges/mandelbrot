#version 330

layout (location = 0) in vec2 pos;

out vec4 frag_pos;

void main()
{
   gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
   frag_pos = vec4(pos, 0.0, 1.0);
}
