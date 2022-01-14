#ifndef __LAB_WORK_2_HPP__
#define __LAB_WORK_2_HPP__

#include "GL/gl3w.h"
#include "base_lab_work.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "define.hpp"
#include <vector>
#include <ctime>




namespace M3D_ISICG
{
	class LabWork2 : public BaseLabWork
	{
	  public:
		LabWork2() : BaseLabWork() {}
		~LabWork2();

		bool init() override;
		void animate( const float p_deltaTime ) override;
		void render() override;

		void handleEvents( const SDL_Event & p_event ) override;
		void displayUI() override;

	  private:
		// ================ Scene data.
		std::vector<Vec2f> pos;
		std::vector<int> indices;
		std::vector<Vec3f> colors;
		// ================

		// ================ GL data.
		GLuint vbo;
		GLuint vbo2;
		GLuint vao;
		GLuint prg;
		GLuint ebo;
		GLint  loc = GL_INVALID_INDEX;
		GLfloat  lum = 1.f;
		// ================
		// GL_INVALID_INDEX
		//float _time=0.f;
		float _time = 0.f ;
		// ================ Settings.
		Vec4f _bgColor = Vec4f( 0.8f, 0.8f, 0.8f, 1.f ); // Background color
		// ================

		static const std::string _shaderFolder;
	};
} // namespace M3D_ISICG

#endif // __LAB_WORK_2_HPP__
