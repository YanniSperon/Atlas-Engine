#include "L_VRHandler.h"

namespace L_Atlas {

	static L_VRHandler::L_OpenVRApplication* app = nullptr;
	static L_BasicRenderTarget* leftRT = nullptr;
	static L_BasicRenderTarget* rightRT = nullptr;
	static GLuint leftEyeTexture;
	static GLuint rightEyeTexture;

	void L_VRHandler::Setup()
	{
		if (L_Global::Variables.hasVR) {
			L_System::Log("Attempting to initialize OpenVRApplication");
			app = new L_OpenVRApplication();
			L_System::Log("Initialized OpenVRApplication");
			if (app->initialized) {
				if (vr::VR_IsHmdPresent()) {
					//vr::EVRInitError eError = vr::VRInitError_None;
					//vr_pointer = VR_Init(&eError, vr::VRApplication_Scene); // VRApplication_Background OR VRApplication_Scene OR VRApplication_Overlay OR VRApplication_Utility
					//if (eError != vr::VRInitError_None)
					//{
					//	vr_pointer = nullptr;
					//	std::string error = VR_GetVRInitErrorAsEnglishDescription(eError);
					//	L_System::Err("Unable to init VR runtime: \"" + error + "\"");
					//}
					try {
						L_System::Log("Generating left eye textures");
						glGenTextures(1, &leftEyeTexture);
						L_System::Log("Setting left eye texture storage type");
						glBindTexture(GL_TEXTURE_2D, leftEyeTexture);
						glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, app->rtWidth, app->rtHeight);
						//glTextureStorage2D(leftEyeTexture, 1, GL_RGBA8, app->rtWidth, app->rtHeight);

						L_System::Log("Generating right eye textures");
						glGenTextures(1, &rightEyeTexture);
						L_System::Log("Setting right eye texture storage type");
						glBindTexture(GL_TEXTURE_2D, rightEyeTexture);
						glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, app->rtWidth, app->rtHeight);
						//glTextureStorage2D(rightEyeTexture, 1, GL_RGBA8, app->rtWidth, app->rtHeight);

						leftRT = new L_BasicRenderTarget(1, app->rtWidth, app->rtHeight);
						rightRT = new L_BasicRenderTarget(1, app->rtWidth, app->rtHeight);

						L_System::Log("Completed initialization of both framebuffers and attached depth buffers!");

						L_System::Log("Attempting priming");
						leftRT->prime(leftEyeTexture);
						rightRT->prime(rightEyeTexture);
						L_System::Log("Finished priming");

						glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
						glBindFramebuffer(GL_FRAMEBUFFER, leftRT->fbo);
						//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

						GLenum temp = glCheckFramebufferStatus(GL_FRAMEBUFFER);
						switch (temp) {
						case GL_FRAMEBUFFER_COMPLETE:
							L_System::Log("Complete!");
							break;
						case GL_FRAMEBUFFER_UNDEFINED:
							L_System::Err("FRAMEBUFFER IS DEFAULT DRAW BUFFER AT INDEX 0!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
							L_System::Err("INCOMPLETE ATTACHMENT!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
							L_System::Err("INCOMPLETE MISSING ATTACHMENT!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
							L_System::Err("INCOMPLETE DRAW BUFFER!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
							L_System::Err("INCOMPLETE READ BUFFER!");
							break;
						case GL_FRAMEBUFFER_UNSUPPORTED:
							L_System::Err("UNSUPPORTED FRAMEBUFFER FORMAT!");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
							L_System::Err("INCOMPLETE MULTISAMPLE");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
							L_System::Err("INCOMPLETE LAYER TARGETS!");
							break;
						default:
							break;
						}
						//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
						//{
						//	L_System::Err("Left RT Incomplete");
						//}

						glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
						glBindFramebuffer(GL_FRAMEBUFFER, rightRT->fbo);
						//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

						if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
						{
							L_System::Err("Right RT Incomplete");
						}

						glBindFramebuffer(GL_FRAMEBUFFER, 0);
					}
					catch (const std::exception & e) {
						L_System::Err("Fatal error, cannot initialize OpenVR display");
					}
				}
				else {
					L_System::Err("Cannot initialize OpenVR runtime, no headset detected!");
				}
			}
			else {
				L_System::Err("Error initializing OpenVR application");
			}
		}
	}

	std::string L_VRHandler::GetTrackedDeviceString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError)
	{
		//vr::IVRSystem* vr_pointer = nullptr;
		//if (Global::Variables.hasVR) {
		//	vr::EVRInitError eError = vr::VRInitError_None;
		//	vr_pointer = VR_Init(&eError, vr::VRApplication_Scene); // VRApplication_Background OR VRApplication_Scene OR VRApplication_Overlay OR VRApplication_Utility
		//	if (eError != vr::VRInitError_None)
		//	{
		//		vr_pointer = nullptr;
		//		std::string error = VR_GetVRInitErrorAsEnglishDescription(eError);
		//		L_System::Err("Unable to init VR runtime: \"" + error + "\"");
		//	}
		//}
		if (L_Global::Variables.hasVR) {
			uint32_t unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, nullptr, 0, peError);
			if (unRequiredBufferLen == 0)
				return "";

			char* pchBuffer = new char[unRequiredBufferLen];
			unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, pchBuffer, unRequiredBufferLen, peError);
			std::string sResult = pchBuffer;
			delete[] pchBuffer;
			return sResult;
		}
		else {
			return "INVALID";
		}
	}

	void L_VRHandler::Submit()
	{
		if (L_Global::Variables.hasVR) {
			app->submitFramesOpenGL(leftEyeTexture, rightEyeTexture);
		}
	}

	void L_VRHandler::Cleanup()
	{
		if (L_Global::Variables.hasVR) {
			vr::VR_Shutdown();
		}
	}
}