#include "AtlasEngine.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Global.h"
#include "Renderer.h"
#include "MeshGenerator.h"
#include "Scene3D.h"
#include "Shared/S_Input/S_InputHandler.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "Shared/S_Vendor/S_IMGUI/imgui.h"
#include "Shared/S_Vendor/S_IMGUI/imgui_impl_glfw_gl3.h"
#include "Shared/S_Vendor/S_IMGUI/imgui_internal.h"

#include <iostream>

//#define ATLAS_DEBUG
//#define INHERIT_ROTATION

namespace Atlas {

    static void errorCallback(int error, const char* description)
    {
        printf("Error %i: %s\n", error, description);
    }

	bool AtlasEngine::Start() {
        // WINDOW INITIALIZATION

        if (!glfwInit()) {
            printf("Error initializing GLFW!\n");
            return false;
        }

        Global::Variables.window = glfwCreateWindow(Global::Variables.screenWidth, Global::Variables.screenHeight, "Atlas", nullptr, nullptr);

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
        glfwSetErrorCallback(errorCallback);


        // RENDERING INITIALIZATION

        printf("Vendor: %s\n", std::string((char*)glGetString(GL_VENDOR)).c_str());
        printf("Model: %s\n", std::string((char*)glGetString(GL_RENDERER)).c_str());
        printf("Version: %s\n", std::string((char*)glGetString(GL_VERSION)).c_str());

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        //glDebugMessageCallback(L_Callbacks::openglCallbackFunction, nullptr);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);




        // IMGUI INIT
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = nullptr;

        ImGui_ImplGlfwGL3_Init(Global::Variables.window, true);
        ImGui::StyleColorsDark();
        

        // SCENE INIT

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

        scene->SetBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        // TIME INIT
        double timeConstant = 1.0;
        auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = lastTime;

        while (!glfwWindowShouldClose(Global::Variables.window))
        {
            // DELTATIME CALC
            currentTime = std::chrono::high_resolution_clock::now();
            auto deltaTimeNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime);
            lastTime = currentTime;
            double deltaTime = deltaTimeNanoseconds.count() / 1000000000.0 * timeConstant;

            // INPUT PROCESS
            glfwPollEvents();
            Input::InputHandler::ProcessEvents(&Global::Variables.keyIn, &Global::Variables.mouseIn, Global::Variables.shouldReceiveInput);

            scene->Begin();

            // UPDATE

            scene->Update(deltaTime);

            // RENDERING

            scene->Draw(renderer);

            // IMGUI
            ImGui_ImplGlfwGL3_NewFrame();
            {
                {
                    // DEBUG
                    ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)Global::Variables.screenWidth), (20.0f / 1080.0f) * ((float)Global::Variables.screenHeight)));
                    ImGui::SetNextWindowSize(ImVec2((240.0f / 1920.0f) * ((float)Global::Variables.screenWidth), (100.0f / 1080.0f) * ((float)Global::Variables.screenHeight)));
                    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
                    ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.12f).x);
                    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                    ImGui::Checkbox("Enable movement", &Global::Variables.shouldReceiveInput);
                    ImGui::End();
                }
                {
                    // POSITION CHANGER
                    ImGui::Begin("Tranformations");
                    static glm::vec3 gcntranslation = tempNode2->GetTranslation();
                    static glm::vec3 gcnrotation = tempNode2->GetRotation();
                    static glm::vec3 gcnscale = tempNode2->GetScale();
                    std::string temp = "Green cube node " + tempNode2->GetName();
                    ImGui::Text(temp.c_str());
                    ImGui::SliderFloat3("Translation##gcn", &gcntranslation[0], -25.0f, 25.0f);
                    ImGui::SliderFloat3("Rotation##gcn", &gcnrotation[0], -360.0f, 360.0f);
                    ImGui::SliderFloat3("Scale##gcn", &gcnscale[0], -25.0f, 25.0f);
                    tempNode2->SetTranslation(gcntranslation);
                    tempNode2->SetRotation(gcnrotation);
                    tempNode2->SetScale(gcnscale);

                    static glm::vec3 gctranslation = object3->GetLocalTranslation();
                    static glm::vec3 gcrotation = object3->GetLocalRotation();
                    static glm::vec3 gcscale = object3->GetLocalScale();
                    ImGui::Text("Green cube");
                    ImGui::SliderFloat3("Translation##gc", &gctranslation[0], -25.0f, 25.0f);
                    ImGui::SliderFloat3("Rotation##gc", &gcrotation[0], -360.0f, 360.0f);
                    ImGui::SliderFloat3("Scale##gc", &gcscale[0], -25.0f, 25.0f);
                    object3->SetLocalTranslation(gctranslation);
                    object3->SetLocalRotation(gcrotation);
                    object3->SetLocalScale(gcscale);

                    static glm::vec3 ocntranslation = tempNode->GetTranslation();
                    static glm::vec3 ocnrotation = tempNode->GetRotation();
                    static glm::vec3 ocnscale = tempNode->GetScale();
                    std::string temp2 = "Orange cube node " + tempNode->GetName();
                    ImGui::Text(temp2.c_str());
                    ImGui::SliderFloat3("Translation##ocn", &ocntranslation[0], -25.0f, 25.0f);
                    ImGui::SliderFloat3("Rotation##ocn", &ocnrotation[0], -360.0f, 360.0f);
                    ImGui::SliderFloat3("Scale##ocn", &ocnscale[0], -25.0f, 25.0f);
                    tempNode->SetTranslation(ocntranslation);
                    tempNode->SetRotation(ocnrotation);
                    tempNode->SetScale(ocnscale);

                    static glm::vec3 octranslation = object2->GetLocalTranslation();
                    static glm::vec3 ocrotation = object2->GetLocalRotation();
                    static glm::vec3 ocscale = object2->GetLocalScale();
                    ImGui::Text("Orange cube");
                    ImGui::SliderFloat3("Translation##oc", &octranslation[0], -25.0f, 25.0f);
                    ImGui::SliderFloat3("Rotation##oc", &ocrotation[0], -360.0f, 360.0f);
                    ImGui::SliderFloat3("Scale##oc", &ocscale[0], -25.0f, 25.0f);
                    object2->SetLocalTranslation(octranslation);
                    object2->SetLocalRotation(ocrotation);
                    object2->SetLocalScale(ocscale);
                    ImGui::End();
                }
            }
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            // CHANGE FRAMEBUFFERS
            scene->End();

            // INPUT PROCESS
            if (Global::Variables.keyIn.kPressed) {
                glfwSetInputMode(Global::Variables.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                Global::Variables.shouldReceiveInput = false;
            }
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

        // IMGUI CLEANUP
        ImGui_ImplGlfwGL3_Shutdown();
        ImGui::DestroyContext();

        // GLFW CLEANUP
        glfwTerminate();


        // RETURN
        return true;
	}

	void AtlasEngine::Cleanup() {
		
	}
}