precision mediump float;

uniform float z_layer;

attribute vec3 xyz;
attribute vec2 st;

varying vec2 out_st;

void main() {
  gl_Position = vec4(xyz.xyz, 1.0);
  out_st = st;
}
