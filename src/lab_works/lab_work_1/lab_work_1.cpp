#include "lab_work_1.hpp"
#include "imgui.h"
#include "utils/read_file.hpp"
#include <iostream>

namespace M3D_ISICG
{
	const std::string LabWork1::_shaderFolder = "src/lab_works/lab_work_1/shaders/";

	GLuint prg;

	LabWork1::~LabWork1() { 
	glDeleteProgram( prg );
	glDeleteBuffers( 1, &vbo );
	glDisableVertexArrayAttrib( vao, 0 );
	glDeleteVertexArrays( 1, &vao );
	}

	bool LabWork1::init()
	{
		std::cout << "Initializing lab work 1..." << std::endl;
		// Set the color used by glClear to clear the color buffer (in render()).
		glClearColor( _bgColor.x, _bgColor.y, _bgColor.z, _bgColor.w );

		const std::string vertexShaderStr1 = readFile( _shaderFolder + "lw1.vert" );
		const GLuint	  shader1		   = glCreateShader( GL_VERTEX_SHADER );

		const std::string vertexShaderStr2 = readFile( _shaderFolder + "lw1.frag" );
		const GLuint	  shader2		   = glCreateShader( GL_FRAGMENT_SHADER );

		const GLchar * vSrc1 = vertexShaderStr1.c_str();
		const GLchar * vSrc2 = vertexShaderStr2.c_str();

		glShaderSource( shader1, 1, &vSrc1, NULL );
		glShaderSource( shader2, 1, &vSrc2, NULL );

		glCompileShader( shader1 );
		glCompileShader( shader2 );

		GLint compiled;
		glGetShaderiv( shader1, GL_COMPILE_STATUS, &compiled );


		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( shader1, sizeof( log ), NULL, log );
			glDeleteShader( shader1 );
			glDeleteShader( shader2 );
			std ::cerr << " Error compiling vertex shader : " << log << std ::endl;
			return false;
		}
		glGetShaderiv( shader2, GL_COMPILE_STATUS, &compiled );


		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( shader2, sizeof( log ), NULL, log );
			glDeleteShader( shader2 );
			glDeleteShader( shader2 );
			std ::cerr << " Error compiling fragment shader : " << log << std ::endl;
			return false;
		}



		prg = glCreateProgram();

		glAttachShader( prg, shader1 );
		glAttachShader( prg, shader2 );

		glLinkProgram( prg );

		GLint linked;
		glGetProgramiv( prg, GL_LINK_STATUS, &linked );
		if ( !linked )
		{
			GLchar log[ 1024 ];
			glGetProgramInfoLog(prg, sizeof( log ), NULL, log );
			std ::cerr << " Error linking program : " << log << std ::endl;
			return false;
		}




		glUseProgram( prg );

		glDeleteShader( shader1 );
		glDeleteShader( shader2 );

		

		pos = { Vec2f( -0.5f, 0.5f ), Vec2f( 0.5f, 0.5f ), Vec2f( 0.5f, -0.5f ) };
		glCreateBuffers( 1, &vbo );
		glNamedBufferData( vbo, pos.size() * sizeof( Vec2f ), pos.data(), GL_STATIC_DRAW );

		glCreateVertexArrays( 1, &vao );
		glEnableVertexArrayAttrib( vao, 0 );
		glVertexArrayAttribFormat(vao,0,2,GL_FLOAT,GL_FALSE,0);

		glVertexArrayVertexBuffer( vao, 0, vbo, 0, sizeof( Vec2f ) );
		glVertexArrayAttribBinding( vao, 0, 0 );

		

		/* GLint compiled;
		glGetShaderiv( shader1, GL_COMPILE_STATUS, &compiled );
		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( shader1, sizeof( log ), NULL, log );
			glDeleteShader( shader1 );
			glDeleteShader( shader2 );
			std ::cerr << " Error compiling vertex shader : " << log << std ::endl;
			return false;
		}*/

		

		

		

		

		std::cout << "Done!" << std::endl;
		return true;
	}

	void LabWork1::animate( const float p_deltaTime ) {}

	void LabWork1::render() { glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glBindVertexArray( vao );
		glDrawArrays( GL_TRIANGLES, 0, 3 );
		glBindVertexArray( 0 );
	}

	void LabWork1::handleEvents( const SDL_Event & p_event ) {}

	void LabWork1::displayUI()
	{
		ImGui::Begin( "Settings lab work 1" );
		ImGui::Text( "No setting available!" );
		ImGui::End();
	}

} // namespace M3D_ISICG
