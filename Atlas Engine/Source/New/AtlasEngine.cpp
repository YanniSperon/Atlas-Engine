#include "AtlasEngine.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Global.h"
#include "Renderer.h"
#include "MeshGenerator.h"
#include "Scene3D.h"
#include "Shared/S_Input/S_InputHandler.h"

#include <iostream>

namespace Atlas {

	bool AtlasEngine::Start() {
        // WINDOW INITIALIZATION

        if (!glfwInit()) {
            printf("Error initializing GLFW!\n");
            return false;
        }

        Global::Variables.window = glfwCreateWindow(Global::Variables.screenWidth, Global::Variables.screenHeight, "Atlas", NULL, NULL);

        if (!Global::Variables.window)
        {
            printf("Error initializing GLFW!\n");
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(Global::Variables.window);

        if (glewInit() != GLEW_OK) {
            printf("Error initializing GLEW (OpenGL)\n");
            return false;
        }

        glfwSetInputMode(Global::Variables.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(Global::Variables.window, Input::InputHandler::MousePositionCallback);
        //glfwSetFramebufferSizeCallback(L_Global::Variables.window, L_Callbacks::framebufferSizeCallback);
        //glfwSetErrorCallback(L_Callbacks::errorCallback);
        glfwSetKeyCallback(Global::Variables.window, Input::InputHandler::KeyCallback);



        // RENDERING INITIALIZATION

        printf("Vendor: %s\n", std::string((char*)glGetString(GL_VENDOR)).c_str());
        printf("Model: %s\n", std::string((char*)glGetString(GL_RENDERER)).c_str());
        printf("Version: %s\n", std::string((char*)glGetString(GL_VERSION)).c_str());

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        //glDebugMessageCallback(L_Callbacks::openglCallbackFunction, NULL);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);

        //Font arial24pt = Font("Resources/fonts/arial/", "arial.ttf", 24);
        //Font timesnewroman32pt = Font("Resources/fonts/times new roman/", "times.ttf", 32);
        //GLuint leftEyeFrameBuffer;
        //glGenFramebuffers(1, &leftEyeFrameBuffer);
        //GLuint rightEyeFrameBuffer;
        //glGenFramebuffers(1, &rightEyeFrameBuffer);
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //GLuint leftEyeFrameBuffer;
        //glGenFramebuffers(1, &leftEyeFrameBuffer);
        //GLuint rightEyeFrameBuffer;
        //glGenFramebuffers(1, &rightEyeFrameBuffer);
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);




        Renderer* renderer = new Renderer();

        Shader* shader = new Shader("Resources/shaders/Basic.shader");

        Texture* texture = new Texture("Resources/images/colors/white.png");
        Texture* texture2 = new Texture("Resources/images/colors/orange.png");
        Texture* texture3 = new Texture("Resources/images/colors/green.png");
        Texture* skyboxTex = new Texture("Resources/images/textures/skybox.png");

        Object3D* object = new Object3D(MeshGenerator::LoadTexturedShape("Resources/models/plane.obj"), shader, texture);
        object->SetLocalTranslation(glm::vec3(0.0f, -5.0f, 0.0f));
        object->SetLocalScale(glm::vec3(10.0f, 10.0f, 10.0f));
        object->LoadIntoVRAM();

        Object3D* object2 = new Object3D(MeshGenerator::CreateCube(glm::vec3(-1.0f), glm::vec3(1.0f)), shader, texture2);
        object2->LoadIntoVRAM();

        Object3D* object3 = new Object3D(MeshGenerator::CreateCube(glm::vec3(-1.0f), glm::vec3(1.0f)), shader, texture3);
        object3->LoadIntoVRAM();

        Object3D* skyboxObject = new Object3D(MeshGenerator::LoadTexturedShape("Resources/models/skybox.obj"), shader, skyboxTex);
        //skyboxObject->SetLocalScale(glm::vec3(25.0f, 25.0f, 25.0f));
        skyboxObject->LoadIntoVRAM();

        Scene3D* scene = new Scene3D();

        Node3D* cameraNode = scene->CreateChildNode();
        Camera* camera = new Camera();
        cameraNode->SetScale(glm::vec3(50.0f, 50.0f, 50.0f));
        camera->SetTranslation(glm::vec3(0.0, 0.0f, 5.0f));
        cameraNode->SetCamera(camera);
        cameraNode->SetObject(skyboxObject);
        scene->SetActiveCamera(cameraNode);
        
        Node3D* tempNod = scene->CreateChildNode();
        tempNod->SetObject(object);

        Node3D* tempNode = scene->CreateChildNode();
        tempNode->SetObject(object2);

        Node3D* tempNode2 = new Node3D(tempNode);
        tempNode2->SetTranslation(glm::vec3(5.0f, 5.0f, 5.0f));
        tempNode2->SetRotation(glm::vec3(45.0f, 0.0f, 0.0f));
        tempNode2->SetObject(object3);




        double timeConstant = 1.0;
        auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = lastTime;

        while (!glfwWindowShouldClose(Global::Variables.window))
        {
            currentTime = std::chrono::high_resolution_clock::now();
            auto deltaTimeNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime);
            lastTime = currentTime;
            double deltaTime = deltaTimeNanoseconds.count() / 1000000000.0 * timeConstant;

            glfwPollEvents();
            Input::InputHandler::ProcessEvents(&Global::Variables.keyIn, &Global::Variables.mouseIn);

            scene->Update(deltaTime);

            scene->Draw(renderer);





            if (Global::Variables.keyIn.leftAltPressed) {
                glfwSetInputMode(Global::Variables.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            if (Global::Variables.keyIn.leftAltReleased) {
                glfwSetInputMode(Global::Variables.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }
            if (Global::Variables.keyIn.leftControlHeld && Global::Variables.keyIn.qHeld) {
                glfwSetWindowShouldClose(Global::Variables.window, true);
            }
            Input::InputHandler::Flush(&Global::Variables.keyIn, &Global::Variables.mouseIn);
        }

        glfwTerminate();
        return true;
	}

	void AtlasEngine::Cleanup() {
		
	}
}