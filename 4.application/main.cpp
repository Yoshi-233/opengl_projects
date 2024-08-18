#include <glad/glad.h>  // 必须为首句
#include <GLFW/glfw3.h>
#include <iostream>
#include "Application/include/Application.h"
#include "common/include/check_err.h"

// 窗口大小改变回调函数
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
        glViewport(0, 0, width, height);
}

/*
 * key_callback() 函数用于处理键盘事件
 * 参数：
 * GLFWwindow *window：当前窗口的句柄
 * int key：按下的键的键码
 * int scancode：按下的键的扫描码, 物理按键码, 有些键盘排布不一致，根据位置推算按键，一般不用
 * int action：键的动作，如按下或释放
 * int mode：当前窗口的输入模式， 如shift、ctrl等
 * */
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
        if ((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) ||
            (key == GLFW_KEY_C && action == GLFW_RELEASE && mode == GLFW_MOD_CONTROL)) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
}


int main()
{
        auto application = APP;
        if(!application->init(800, 600, "LearnOpenGL")) {
                std::cout << "Failed to initialize Application" << std::endl;
                return -1;
        }


//        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//        glfwSetKeyCallback(window, key_callback);
        while (application->update()) {
                // 清屏
                GL_CHECK_ERR(glClear(GL_COLOR_BUFFER_BIT));
                // 绘制代码
        }
        application->close();
        return 0;
}