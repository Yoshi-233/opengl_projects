#include <glad/glad.h>  // 必须为首句
#include <GLFW/glfw3.h>
#include <iostream>
#include "Application/include/Application.h"
#include "common/include/check_err.h"

// 窗口大小改变回调函数
void OnResize(GLFWwindow *window, int width, int height)
{
        GL_CHECK_ERR(glViewport(0, 0, width, height));
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
void OnKeyBoard(GLFWwindow *window, int key, int scancode, int action, int mode)
{
        if ((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) ||
            (key == GLFW_KEY_C && action == GLFW_RELEASE && mode == GLFW_MOD_CONTROL)) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
}

void prepareVBO()
{
        GLuint vbo = 0;
        GL_CHECK_ERR(glGenBuffers(1, &vbo));
        std::cout << vbo << std::endl;
        GL_CHECK_ERR(glDeleteBuffers(1, &vbo));
        std::cout << vbo << std::endl;

        GLuint vbo_arr[3] = {0};
        GL_CHECK_ERR(glGenBuffers(3, vbo_arr));
        std::cout << vbo_arr[0] << vbo_arr[1] << vbo_arr[2] << std::endl;
        GL_CHECK_ERR(glDeleteBuffers(1, vbo_arr + 2));

        GL_CHECK_ERR(glGenBuffers(1, &vbo));
        std::cout << vbo << std::endl;
        GL_CHECK_ERR(glDeleteBuffers(1, &vbo));

        std::cout << vbo_arr[0] << vbo_arr[1] << vbo_arr[2] << std::endl;
        GL_CHECK_ERR(glDeleteBuffers(2, vbo_arr));
}

void prepare()
{
        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,0.5f, 0.0f
        };
        GLuint vbo = 0;
        GL_CHECK_ERR(glGenBuffers(1, &vbo));
        // GL_ARRAY_BUFFER current vbo
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK_ERR(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        GL_CHECK_ERR(glDeleteBuffers(1, &vbo));

}

void prepareSingleBuffer()
{
        float position[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f,  0.0f
        };

        float color[] = {
                1.0f, 0.0f, 0.0f,
                0.5f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
        };
        GLuint posVbo = 0, colorVbo = 0;
        GL_CHECK_ERR(glGenBuffers(1, &posVbo));
        GL_CHECK_ERR(glGenBuffers(1, &colorVbo));

        // GL_ARRAY_BUFFER current vbo
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
        GL_CHECK_ERR(glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW));
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
        GL_CHECK_ERR(glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW));

        GL_CHECK_ERR(glDeleteBuffers(1, &posVbo));
        GL_CHECK_ERR(glDeleteBuffers(1, &colorVbo));

}

void prepareInterleaveBuffer()
{
        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 0.5f, 1.0f, 0.0f,
                0.0f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f
        };

        GLuint vbo = 0;
        GL_CHECK_ERR(glGenBuffers(1, &vbo));

        // GL_ARRAY_BUFFER current vbo
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK_ERR(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        GL_CHECK_ERR(glDeleteBuffers(1, &vbo));

}

int main()
{
        if (!APP.init(800, 600, "LearnOpenGL")) {
                std::cout << "Failed to initialize Application" << std::endl;
                return -1;
        }

        APP.setResizeCallback(OnResize);
        APP.setKeyCallback(OnKeyBoard);

        // opengl渲染的区域
        GL_CHECK_ERR(glViewport(0, 0, 800, 600));
        // 设置清屏颜色
        GL_CHECK_ERR(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

//        prepareVBO();
        prepareSingleBuffer();
        prepareInterleaveBuffer();

        while (APP.update()) {
                // 清屏
                GL_CHECK_ERR(glClear(GL_COLOR_BUFFER_BIT));
                // 绘制代码
        }
        APP.close();
        return 0;
}