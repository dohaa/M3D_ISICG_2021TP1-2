#include "imgui.h"
#include "lab_work_2.hpp"
#include "utils/read_file.hpp"
#include <iostream>
#include <ctime>

using namespace std;

namespace M3D_ISICG
{
	const std::string LabWork2::_shaderFolder = "src/lab_works/lab_work_2/shaders/";

	

	LabWork2::~LabWork2()
	{
		//glDeleteProgram( prg );
		glDeleteBuffers( 1, &vbo );
		glDeleteBuffers( 1, &vbo2 );
		glDisableVertexArrayAttrib( vao, 0 );
		glDeleteVertexArrays( 1, &vao );
	}

	bool LabWork2::init()
	{
		
		std::cout << "Initializing lab work 2..." << std::endl;
		// Set the color used by glClear to clear the color buffer (in render()).
		glClearColor( _bgColor.x, _bgColor.y, _bgColor.z, _bgColor.w );
		
		// Vertex Shader
		const std::string vertexShaderStr = readFile( _shaderFolder + "lw1.vert" );
		const GLuint	  vertexShader	  = glCreateShader( GL_VERTEX_SHADER );
		const GLchar *	  vSrc			  = vertexShaderStr.c_str();
		glShaderSource( vertexShader, 1, &vSrc, NULL );
		glCompileShader( vertexShader );

		GLint compiled;
		glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &compiled );
		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( vertexShader, sizeof( log ), NULL, log );
			glDeleteShader( vertexShader );
			std ::cerr << " Error compiling vertex shader : " << log << std ::endl;
			return false;
		}
		
		// Fragment Shader
		const std::string fragmentShaderStr = readFile( _shaderFolder + "lw1.frag" );
		const GLuint	  fragmentShader	= glCreateShader( GL_FRAGMENT_SHADER );
		const GLchar *	  fSrc				= fragmentShaderStr.c_str();
		glShaderSource( fragmentShader, 1, &fSrc, NULL );
		glCompileShader( fragmentShader );

		glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &compiled );
		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( fragmentShader, sizeof( log ), NULL, log );
			glDeleteShader( fragmentShader );
			std ::cerr << " Error compiling fragment shader : " << log << std ::endl;
			return false;
		}
		

		prg = glCreateProgram();



		glAttachShader( prg, vertexShader );
		glAttachShader( prg, fragmentShader );

		glLinkProgram( prg);
		

		GLint linked;
		glGetProgramiv( prg, GL_LINK_STATUS, &linked );
		if ( !linked )
		{
			GLchar log[ 1024 ];
			glGetProgramInfoLog( prg, sizeof( log ), NULL, log );
			std ::cerr << " Error linking program : " << log << std ::endl;
			return false;
		}

		
		//glUniform1i( loc, 5 );
		/* GLenum errorState = glGetError();
		if ( loc == -1 || errorState != GL_NO_ERROR )
		{
			fprintf(
				stderr, "Erreur (%d) lors de la rcupration de l'id de la variable uniforme 'couleur'\n", errorState );
		}*/

		//glUseProgram( prg );

		//glDeleteShader( vertexShader );
		//glDeleteShader( fragmentShader );

		pos = { Vec2f( -0.5f, 0.5f ), Vec2f( 0.5f, 0.5f ),
				 Vec2f( -0.5f, -0.5f ), Vec2f( 0.5f, -0.5f ) };

		colors = {
			Vec3f( 1.0f, 0.0f, 0.0f ), Vec3f( 0.0f, 1.0f, 0.0f ), Vec3f( 1.0f, 0.0f, 1.0f ), Vec3f( 0.0f, 0.0f, 1.0f )
		};

		//loc = glGetUniformLocation( prg, "uTranslationX" );
		
		//glProgramUniform1f( prg, loc, 6 );

		
		// VBO
		glCreateBuffers( 1, &vbo );
		glCreateBuffers( 1, &vbo2 );
		glNamedBufferData( vbo, pos.size() * sizeof( Vec2f ), pos.data(), GL_STATIC_DRAW );
		glNamedBufferData( vbo2, colors.size() * sizeof( Vec3f ), colors.data(), GL_STATIC_DRAW );

		// EBO
		indices = { 0, 1, 3, 0, 2, 3 };
		glCreateBuffers( 1, &ebo );
		glNamedBufferData( ebo, indices.size() * sizeof( int ), indices.data(), GL_STATIC_DRAW );
		

		// VAO
		glCreateVertexArrays( 1, &vao );
		glEnableVertexArrayAttrib( vao, 0 );
		glVertexArrayAttribFormat( vao, 0, 2, GL_FLOAT, GL_FALSE, 0 );
		glVertexArrayVertexBuffer( vao, 0, vbo, 0, sizeof( Vec2f ) );

		glEnableVertexArrayAttrib( vao, 1 );
		glVertexArrayAttribFormat( vao, 1, 3, GL_FLOAT, GL_FALSE, 0 );


		
		glVertexArrayVertexBuffer( vao, 1, vbo2, 0, sizeof( Vec3f ) );

		//lier le vao avec vs
		glVertexArrayAttribBinding( vao, 0, 0 );
		glVertexArrayAttribBinding( vao, 1, 1 );

		glVertexArrayElementBuffer( vao, ebo );
	
	

		glUseProgram( prg );

		loc = glGetUniformLocation( prg, "uTranslationX" );
		lum = glGetUniformLocation( prg, "shade" );
		//glProgramUniform1f( prg, loc, 1 );

		//glDeleteShader( vertexShader );
		//glDeleteShader( fragmentShader );

		// glDeleteProgram( Program );
		
		
		std::cout << "Done!" << std::endl;
		return true;
	}

	void LabWork2::animate( const float p_deltaTime ) {
	
		//std::cout << "C'est la loc avant" << loc << std::endl;
	
		const float res = glm::sin( _time ) * 0.5f;
		glProgramUniform1f( prg, loc, res );
		//std::cout << "C'est la loc apres" << loc << std::endl;
		_time += p_deltaTime;
	
	}

	void LabWork2::render()
	{	
		glClear( GL_COLOR_BUFFER_BIT );
		glBindVertexArray( vao );
		
		//glDrawArrays( GL_TRIANGLES, 0, (GLsizei) pos.size() );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
		
	}
	 
	void LabWork2::handleEvents( const SDL_Event & p_event ) {}

	void LabWork2::displayUI()
	{
		Vec4f col1 = { 1.0f, 0.0f, 0.2f ,1.f};
		static float l;
		ImGui::Begin( "Settings lab work 2" );
		ImGui::Text( "No setting available!" );
		if (ImGui::SliderFloat("luminosité",&l, -1.f, 1.f)) {
			glProgramUniform1f( prg,lum,l);
		}
		
		if ( ImGui::ColorEdit3( "Color back", glm::value_ptr( _bgColor ) ) )
		{
			glClearColor( _bgColor.x, _bgColor.y, _bgColor.z, _bgColor.w );
			
		}
		
		ImGui::End();
	}

} // namespace M3D_ISICG
