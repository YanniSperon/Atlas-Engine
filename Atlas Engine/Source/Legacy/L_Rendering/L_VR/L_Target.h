#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <openvr.h>
#include "Legacy/L_System/L_System.h"

namespace L_Atlas {
	struct L_RenderTarget
	{
		GLuint fbo;

		unsigned int frameWidth; ///< one half the allocated render target width, since we are using side by side stereo
		unsigned int frameHeight;
		unsigned int multisamples;

		L_RenderTarget() :
			frameWidth(0), frameHeight(0), multisamples(0), fbo(0)
		{
			L_System::Log("Initializing basicrendertarget");
		}

		L_RenderTarget(unsigned int width, unsigned int height, unsigned int samples) :
			frameWidth(width), frameHeight(height), multisamples(samples)
		{
			L_System::Log("Initializing rendertarget with arguments");
			glGenFramebuffers(1, &fbo);
			L_System::Log("Finished initializing rendertarget with arguments");
		}
	};

	struct L_BasicRenderTarget : public L_RenderTarget
	{
		GLuint depthTex;

		void prime(GLuint tex)
		{
			L_System::Log("Binding framebuffer");
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			L_System::Log("framebuffer bound");

			if (multisamples > 1)
			{
				glFramebufferTexture2DMultisampleEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0, multisamples);
			}
			else
			{
				L_System::Log("GLframebuffertexture2d");
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
				L_System::Log("finished GLframebuffertexture2d");
			}
			//L_System::Log("Attempting glclear");
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//L_System::Log("finished glclear");
		}

		L_BasicRenderTarget() :
			L_RenderTarget(), depthTex(0)
		{
			L_System::Log("Initializing basicrendertarget");
		}

		L_BasicRenderTarget(int multisamples, unsigned int width, unsigned int height) :
			L_RenderTarget(width, height, multisamples)
		{
			L_System::Log("Initializing basicrendertarget with arguments");
			glGenRenderbuffers(1, &depthTex);
			const GLenum depthFormat = GL_DEPTH_COMPONENT24;
			glBindRenderbuffer(GL_RENDERBUFFER, depthTex);

			if (multisamples > 1)
			{
				L_System::Log("Side by side with multisamples : " + multisamples);
				//glBindFramebuffer(GL_DEPTH_COMPONENT24, fbo);
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisamples, depthFormat, width, height);
			}
			else
			{
				L_System::Log("Side by side without multisampling");
				glRenderbufferStorage(GL_RENDERBUFFER, depthFormat, width, height);
				L_System::Log("Done setting renderbuffer storage format");
			}

			L_System::Log("binding framebuffer object");
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			L_System::Log("setting the depth attachment");
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
			L_System::Log("done setting the depth attachment");

			static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };

			glViewport(0, 0, frameWidth, frameHeight);
			L_System::Log("Finished init basicrendertarget with arguments");
		}
	};
}