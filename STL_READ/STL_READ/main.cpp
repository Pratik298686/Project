#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Vertex
{
public:
    float x, y, z;
};

class Normal
{
public:
    float x, y, z;
    //std::vector<Vertex> vertex;
};

class Facet
{
public:
    Normal faceNormal;
    std::vector<Vertex> vert2;
    float normal[3]; 
    float v1[3]; 
    float v2[3]; 
    float v3[3];
};

void display()
{

    //std::ifstream file("C:\\Users\\Pratik Padman\\Downloads\\STL\\STL\\ASCII\\cube with hole_fine.stl");
    std::ifstream file("C:\\Users\\Pratik Padman\\Downloads\\asciistlcube1.stl");
    std::string line, name1, name2;
    float x, y, z;
    //Normal norm;
    Vertex vert;
    Facet face;

    std::vector<Facet> allTriangleFacets;
    int p = 0, q = 0;
    std::vector<std::string> vec;
    std::getline(file, line);

    int i = 0, j = 0, k;
    if (file.is_open())
    {
        Facet* ptr = new Facet();
        while (std::getline(file, line))
        {
            if (i > 4 && j > 6)
            {
                i = 0;
                j = 0;
            }
            std::stringstream ss(line);
            if (std::string::npos != line.find("face normal"))
            {
                ptr = new Facet();
            }
            else if (std::string::npos != line.find("endfacet"))
            {
                delete ptr;
            }
            if (std::string::npos != line.find("normal"))
            {
                
                sscanf_s(line.c_str(), "facet normal %f %f %f", &ptr->normal[0], &ptr->normal[1], &ptr->normal[2]);
            }
            else if (std::string::npos != line.find("vertex"))
            {
                
                sscanf_s(line.c_str(), "vertex %f %f %f", &ptr->v1[0], &ptr->v1[1], &ptr->v1[2]);
                ptr->vert2.push_back(vert);
            }
            if ((std::string::npos != line.find("normal") || std::string::npos != line.find("vertex")) && i == 4)
            {
                allTriangleFacets.push_back(*ptr);
            }
            i++;
            j++;
        }
        file.close();
    }
   //  Draw a triangle 
    //glEnable(GL_DEPTH_TEST);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    //glPointSize(2);
    glBegin(GL_QUADS);
    for (int i = 0; i < allTriangleFacets.size(); i++)
    {
        glNormal3f(allTriangleFacets[i].normal[0], allTriangleFacets[i].normal[1], allTriangleFacets[i].normal[2]);
        for (int j = 0; j < 3; j++)
        {
            glVertex3f(allTriangleFacets[i].v1[0], allTriangleFacets[i].v1[1], allTriangleFacets[i].v1[2]);
        }
    }
    glEnd();
}

int main()
{
    GLFWwindow* window;
    float angle = 0.0f;

   //  Initialize the library 
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(1280, 960, "Triangle Example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

   //  Make the window's context current 
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window 
    while (!glfwWindowShouldClose(window))
    {
        // Set the viewport 
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Clear the background to black 
        glShadeModel(GL_LINEAR);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
        // Set up the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -6.0f);
        glScalef(20.0, 20.0, 20.0);
        angle += 0.1f;
        glRotatef(angle, 1.0f, 1.0f, 0.0f);

        display();

        // Swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events 
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#define GLEW_STATIC 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
struct Triangle {
    float normal[3];
    float v1[3];
    float v2[3];
    float v3[3];
};
float angle = 0;
void display(GLFWwindow* window, const std::vector<Triangle>& triangles)
{

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);

    for (int i = 0; i < triangles.size(); i++)
    {
        glNormal3f(triangles[i].normal[0], triangles[i].normal[1], triangles[i].normal[2]);
        glVertex3f(triangles[i].v1[0], triangles[i].v1[1], triangles[i].v1[2]);

        glVertex3f(triangles[i].v2[0], triangles[i].v2[1], triangles[i].v2[2]);

        glVertex3f(triangles[i].v3[0], triangles[i].v3[1], triangles[i].v3[2]);

    }
    //for (int i = 0; i < triangles.size(); i++)
    //{
    //	glVertex3f(triangles[i].v1[0], triangles[i].v1[1], triangles[i].v1[2]);
    //	//glVertex3f(triangles[i+1].v2[0], triangles[i + 1].v2[1], triangles[i + 1].v2[2]);
    //	//glVertex3f(triangles[i + 2].v3[0], triangles[i].v3[1], triangles[i].v3[2]);
    //}
    glEnd();
    glfwSwapBuffers(window);
}
int main() {
    //std::ifstream file("C:\\Users\\Atharva Jagtap\\Downloads\\asciistlcube (1).stl");
    std::ifstream file("C:\\Users\\Pratik Padman\\Downloads\\asciistlcube1.stl");

    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    std::vector<Triangle> triangles;
    std::string line;
    Triangle t;
    bool reading_triangles = false;

    while (std::getline(file, line)) {
        if (line.find("facet normal") != std::string::npos) {
            sscanf_s(line.c_str(), "facet normal %f %f %f", &t.normal[0], &t.normal[1], &t.normal[2]);
        }
        else if (line.find("vertex") != std::string::npos) {
            sscanf_s(line.c_str(), "vertex %f %f %f", &t.v1[0], &t.v1[1], &t.v1[2]);
            std::getline(file, line);
            sscanf_s(line.c_str(), "vertex %f %f %f", &t.v2[0], &t.v2[1], &t.v2[2]);
            std::getline(file, line);
            sscanf_s(line.c_str(), "vertex %f %f %f", &t.v3[0], &t.v3[1], &t.v3[2]);
            triangles.push_back(t);
        }
    }


    // Initialize GLFW 
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl; return -1;
    }
    // Create a GLFW window 
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Triangle Color", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl; glfwTerminate(); return -1;
    }
    // Make the window's context current 
    glfwMakeContextCurrent(window);
    // Initialize GLEW 
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl; glfwTerminate();
        return -1;
    }

    // Set the background color of the window 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render the triangle 
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Set up the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)1000 / (double)1000, 0.1, 100.0);
        // Set up the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -6.0f);
        glScalef(20.0f, 20.0f, 20.0f);
        angle += 0.1f;
        glRotatef(angle, 1.0f, 1.0f, 0.0f);
        display(window, triangles);
        // Wait for events with a timeout of 10 milliseconds 
        glfwWaitEventsTimeout(0.0001);
        // Poll for and process events 
        glfwPollEvents();
    }
    // Clean up 
    glfwTerminate();
}
*/