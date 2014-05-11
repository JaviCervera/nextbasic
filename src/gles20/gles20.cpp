#include "glew.h"
#include <stdlib.h>
#include <string>

using namespace std;

extern "C" {

static GLenum _initStatus;

int _glInit() {
	_initStatus = glewInit();
	return _initStatus == GLEW_OK;
}

const char* _glInitError() {
	return (const char*)glewGetErrorString(_initStatus);
}

void _glActiveTexture(int texture) {
	glActiveTexture(texture);
}

void _glAttachShader(int program, int shader) {
	glAttachShader(program, shader);
}

void _glBindAttribLocation(int program, int index, const char* name) {
	glBindAttribLocation(program, index, name);
}

void _glBindBuffer(int target, int buffer) {
	glBindBuffer(target, buffer);
}

void _glBindFramebuffer(int target, int framebuffer) {
	glBindFramebuffer(target, framebuffer);
}

void _glBindRenderbuffer(int target, int renderbuffer) {
	glBindRenderbuffer(target, renderbuffer);
}

void _glBindTexture(int target, int tex) {
	glBindTexture(target, tex);
}

void _glBlendColor(float red, float green, float blue, float alpha) {
	glBlendColor(red, green, blue, alpha);
}

void _glBlendEquation(int mode) {
	glBlendEquation(mode);
}

void _glBlendEquationSeparate(int modeRGB, int modeAlpha) {
	glBlendEquationSeparate(modeRGB, modeAlpha);
}

void _glBlendFunc(int sfactor, int dfactor) {
	glBlendFunc(sfactor, dfactor);
}

void _glBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) {
	glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void _glBufferData(int target, int size, int data, int usage) {
	glBufferData(target, size, (void*)data, usage);
}

void _glBufferSubData(int target, int offset, int size, int data) {
	glBufferSubData(target, offset, size, (void*)data);
}

int _glCheckFramebufferStatus(int target) {
	return glCheckFramebufferStatus(target);
}

void _glClear(int mask) {
	glClear(mask);
}

void _glClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void _glClearDepthf( float depth ){
	glClearDepth( depth );
}

void _glClearStencil(int s) {
	glClearStencil(s);
}

void _glColorMask(int r, int g, int b, int a) {
	glColorMask(r, g, b, a);
}

void _glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border) {
	glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void _glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) {
	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void _glCompileShader(int shader) {
	glCompileShader(shader);
}

int _glCreateBuffer(){
	GLuint buf;
	glGenBuffers( 1,&buf );
	return buf;
}

int _glCreateFramebuffer(){
	GLuint buf;
	glGenFramebuffers( 1,&buf );
	return buf;
}

int _glCreateProgram() {
	return glCreateProgram();
}

int _glCreateRenderbuffer(){
	GLuint buf;
	glGenRenderbuffers( 1,&buf );
	return buf;
}

int _glCreateShader(int type) {
	return glCreateShader(type);
}

int _glCreateTexture(){
	GLuint buf;
	glGenTextures( 1,&buf );
	return buf;
}

void _glCullFace(int mode) {
	glCullFace(mode);
}

void _glDeleteBuffer( int buffer ){
	glDeleteBuffers( 1,(GLuint*)&buffer );
}

void _glDeleteFramebuffer( int buffer ){
	glDeleteFramebuffers( 1,(GLuint*)&buffer );
}

void _glDeleteProgram(int program) {
	glDeleteProgram(program);
}

void _glDeleteRenderbuffer( int buffer ){
	glDeleteRenderbuffers( 1,(GLuint*)&buffer );
}

void _glDeleteShader(int shader) {
	glDeleteShader(shader);
}

void _glDeleteTexture( int texture ){
	glDeleteTextures( 1,(GLuint*)&texture );
}

void _glDepthFunc(int func) {
	glDepthFunc(func);
}

void _glDepthMask(int flag) {
	glDepthMask(flag);
}

void _glDepthRangef( float zNear,float zFar ){
	glDepthRange( zNear,zFar );
}

void _glDetachShader(int program, int shader) {
	glDetachShader(program, shader);
}

void _glDisable(int cap) {
	glDisable(cap);
}

void _glDisableVertexAttribArray(int index) {
	glDisableVertexAttribArray(index);
}

void _glDrawArrays(int mode, int first, int count) {
	glDrawArrays(mode, first, count);
}

void _glDrawElements(int mode, int count, int type, const void* ptr) {
	glDrawElements(mode, count, type, ptr);
}

void _glEnable(int cap) {
	glEnable(cap);
}

void _glEnableVertexAttribArray(int index) {
	glEnableVertexAttribArray(index);
}

void _glFinish() {
	glFinish();
}

void _glFlush() {
	glFlush();
}

void _glFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer) {
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void _glFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level) {
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void _glFrontFace(int mode) {
	glFrontFace(mode);
}

void _glGenerateMipmap(int target) {
	glGenerateMipmap(target);
}

void _glGetActiveAttrib(int program, int index, int bufsize, int length, int size, int type, int name) {
	glGetActiveAttrib(program, index, bufsize, (int*)length, (int*)size, (unsigned int*)type, (char*)name);
}

void _glGetActiveUniform(int program, int index, int bufsize, int length, int size, int type, int name) {
	glGetActiveUniform(program, index, bufsize, (int*)length, (int*)size, (unsigned int*)type, (char*)name);
}

void _glGetAttachedShaders(int program, int maxcount, int count, int shaders) {
	glGetAttachedShaders(program, maxcount, (int*)count, (unsigned int*)shaders);
}

int _glGetAttribLocation(int program, const char* name) {
	return glGetAttribLocation(program, name);
}

void _glGetBooleanv(int pname, GLboolean* params) {
	glGetBooleanv(pname, params);
}

void _glGetBufferParameteriv(int target, int pname, int params) {
	glGetBufferParameteriv(target, pname, (int*)params);
}

int _glGetError() {
	return glGetError();
}

void _glGetFloatv(int pname, float* params) {
	glGetFloatv(pname, params);
}

void _glGetIntegerv(int pname, int* params) {
	glGetIntegerv(pname, params);
}

void _glGetFramebufferAttachmentParameteriv(int target, int attachment, int pname, int params) {
	glGetFramebufferAttachmentParameteriv(target, attachment, pname, (int*)params);
}

void _glGetProgramiv(int program, int pname, int params) {
	glGetProgramiv(program, pname, (int*)params);
}

string _glGetProgramInfoLog( int program ){
	int length=0,length2=0;
	glGetProgramiv( program,GL_INFO_LOG_LENGTH,&length );
	char *buf=(char*)malloc( length+1 );
	glGetProgramInfoLog( program,length,&length2,buf );
	string t( buf );
	free( buf );
	return t;
}

void _glGetRenderbufferParameteriv(int target, int pname, int params) {
	glGetRenderbufferParameteriv(target, pname, (int*)params);
}

void _glGetShaderiv(int shader, int pname, int params) {
	glGetShaderiv(shader, pname, (int*)params);
}

string _glGetShaderInfoLog( int shader ){
	int length=0,length2=0;
	glGetShaderiv( shader,GL_INFO_LOG_LENGTH,&length );
	char *buf=(char*)malloc( length+1 );
	glGetShaderInfoLog( shader,length,&length2,buf );
	string t( buf );
	free( buf );
	return t;
}

string _glGetShaderSource( int shader ){
	int length=0,length2=0;
	glGetShaderiv( shader,GL_SHADER_SOURCE_LENGTH,&length );
	char *buf=(char*)malloc( length+1 );
	glGetShaderSource( shader,length,&length2,buf );
	string t( buf );
	free( buf );
	return t;
}

const char* _glGetString(int name) {
	return (const char*)glGetString(name);
}

void _glGetTexParameterfv(int target, int pname, float* params) {
	glGetTexParameterfv(target, pname, params);
}

void _glGetTexParameteriv(int target, int pname, int* params) {
	glGetTexParameteriv(target, pname, params);
}

void _glGetUniformfv(int program, int location, float* params) {
	glGetUniformfv(program, location, params);
}

void _glGetUniformiv(int program, int location, int* params) {
	glGetUniformiv(program, location, params);
}

int _glGetUniformLocation(int program, const char* name) {
	return glGetUniformLocation(program, name);
}

void _glGetVertexAttribfv(int index, int pname, float* params) {
	glGetVertexAttribfv(index, pname, params);
}

void _glGetVertexAttribiv(int index, int pname, int* params) {
	glGetVertexAttribiv(index, pname, params);
}

void _glHint(int target, int mode) {
	glHint(target, mode);
}

int _glIsBuffer(int buffer) {
	return glIsBuffer(buffer);
}

int _glIsEnabled(int cap) {
	return glIsEnabled(cap);
}

int _glIsFramebuffer(int framebuffer) {
	return glIsFramebuffer(framebuffer);
}

int _glIsProgram(int program) {
	return glIsProgram(program);
}

int _glIsRenderbuffer(int renderbuffer) {
	return glIsRenderbuffer(renderbuffer);
}

int _glIsShader(int shader) {
	return glIsShader(shader);
}

int _glIsTexture(int texture) {
	return glIsTexture(texture);
}

void _glLineWidth(float width) {
	glLineWidth(width);
}

void _glLinkProgram(int program) {
	glLinkProgram(program);
}

void _glPixelStorei(int pname, int param) {
	glPixelStorei(pname, param);
}

void _glPolygonOffset(float factor, float units) {
	glPolygonOffset(factor, units);
}

void _glReadPixels(int x, int y, int width, int height, int format, int type, void* pixels) {
	glReadPixels(x, y, width, height, format, type, pixels);
}

void _glReleaseShaderCompiler() {
	glReleaseShaderCompiler();
}

void _glRenderbufferStorage(int target, int internalformat, int width, int height) {
	glRenderbufferStorage(target, internalformat, width, height);
}

void _glSampleCoverage(float value, int invert) {
	glSampleCoverage(value, invert);
}

void _glScissor(int x, int y, int width, int height) {
	glScissor(x, y, width, height);
}

void _glShaderSource( int shader, const char* source ){
	glShaderSource( shader,1,&source,NULL );
}

void _glStencilFunc(int func, int ref, int mask) {
	glStencilFunc(func, ref, mask);
}

void _glStencilFuncSeparate(int face, int func, int ref, int mask) {
	glStencilFuncSeparate(face, func, ref, mask);
}

void _glStencilMask(int mask) {
	glStencilMask(mask);
}

void _glStencilMaskSeparate(int face, int mask) {
	glStencilMaskSeparate(face, mask);
}

void _glStencilOp(int fail, int zfail, int zpass) {
	glStencilOp(fail, zfail, zpass);
}

void _glStencilOpSeparate(int face, int fail, int zfail, int zpass) {
	glStencilOpSeparate(face, fail, zfail, zpass);
}

void _glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, const void* pixels) {
	glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void _glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, const void* pixels) {
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void _glTexParameterf(int target, int pname, float param) {
	glTexParameterf(target, pname, param);
}

void _glTexParameteri(int target, int pname, int param) {
	glTexParameteri(target, pname, param);
}

void _glUniform1f(int location, float x) {
	glUniform1f(location, x);
}

void _glUniform1i(int location, float x) {
	glUniform1i(location, x);
}

void _glUniform2f(int location, float x, float y) {
	glUniform2f(location, x, y);
}

void _glUniform2i(int location, float x, float y) {
	glUniform2i(location, x, y);
}

void _glUniform3f(int location, float x, float y, float z) {
	glUniform3f(location, x, y, z);
}

void _glUniform3i(int location, float x, float y, float z) {
	glUniform3i(location, x, y, z);
}

void _glUniform4f(int location, float x, float y, float z, float w) {
	glUniform4f(location, x, y, z, w);
}

void _glUniform4i(int location, float x, float y, float z, float w) {
	glUniform4i(location, x, y, z, w);
}

void _glUniform1fv(int location, int count, float* v) {
	glUniform1fv(location, count, v);
}

void _glUniform1iv(int location, int count, int* v) {
	glUniform1iv(location, count, v);
}

void _glUniform2fv(int location, int count, float* v) {
	glUniform2fv(location, count, v);
}

void _glUniform2iv(int location, int count, int* v) {
	glUniform2iv(location, count, v);
}

void _glUniform3fv(int location, int count, float* v) {
	glUniform3fv(location, count, v);
}

void _glUniform3iv(int location, int count, int* v) {
	glUniform3iv(location, count, v);
}

void _glUniform4fv(int location, int count, float* v) {
	glUniform4fv(location, count, v);
}

void _glUniform4iv(int location, int count, int* v) {
	glUniform4iv(location, count, v);
}

void _glUniformMatrix2fv(int location, int count, int transpose, float* value) {
	glUniformMatrix2fv(location, count, transpose, value);
}

void _glUniformMatrix3fv(int location, int count, int transpose, float* value) {
	glUniformMatrix3fv(location, count, transpose, value);
}

void _glUniformMatrix4fv(int location, int count, int transpose, float* value) {
	glUniformMatrix4fv(location, count, transpose, value);
}

void _glUseProgram(int program) {
	glUseProgram(program);
}

void _glValidateProgram(int program) {
	glValidateProgram(program);
}

void _glVertexAttrib1f(int indx, float x) {
	glVertexAttrib1f(indx, x);
}

void _glVertexAttrib2f(int indx, float x, float y) {
	glVertexAttrib2f(indx, x, y);
}

void _glVertexAttrib3f(int indx, float x, float y, float z) {
	glVertexAttrib3f(indx, x, y, z);
}

void _glVertexAttrib4f(int indx, float x, float y, float z, float w) {
	glVertexAttrib4f(indx, x, y, z, w);
}

void _glVertexAttrib1fv(int indx, float *values) {
	glVertexAttrib1fv(indx, values);
}

void _glVertexAttrib2fv(int indx, float *values) {
	glVertexAttrib2fv(indx, values);
}

void _glVertexAttrib3fv(int indx, float *values) {
	glVertexAttrib3fv(indx, values);
}

void _glVertexAttrib4fv(int indx, float *values) {
	glVertexAttrib4fv(indx, values);
}

void _glVertexAttribPointer(int indx, int size, int type, int normalized, int stride, const void* data) {
	glVertexAttribPointer(indx, size, type, normalized, stride, data);
}

void _glViewport(int x, int y, int width, int height) {
	glViewport(x, y, width, height);
}

} // extern "C"
