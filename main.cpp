//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"



using namespace std;

static const string vs_string =
    "#version 410 core                                                 \n"
    "                                                                   \n"
    "uniform mat4 projectionMatrix;                                    \n"
    "uniform mat4 viewMatrix;                                           \n"
    "uniform mat4 modelMatrix;                                          \n"
    "in vec3 in_Position;                                               \n"
    "                                                                   \n"
    "in vec3 in_Color;                                                  \n"
    "out vec3 pass_Color;                                               \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
    "    pass_Color = in_Color;                                         \n"
    "}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
    "#version 410 core                                                 \n"
    "                                                                  \n"
    "in vec3 pass_Color;                                                 \n"
    "out vec4 color;                                                    \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "    color = vec4(pass_Color, 1.0);                               \n"
    "}                                                                 \n";


glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix


// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;
GLuint vao;

unsigned int vaoID[1]; // Our Vertex Array Object

unsigned int vboID[2]; // Our Vertex Buffer Object


// This is the callback we'll be registering with GLFW for errors.
// It'll just print out the error to the STDERR stream.
void error_callback(int error, const char* description) {
    fputs(description, stderr);
}


// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


void createBox(void)
{
    float* vertices = new float[48];  // Vertices for our square
    float *colors = new float[48]; // Colors for our vertices
    
    // shape_1_front
    vertices[0] = 0.0; vertices[1] = 0.0; vertices[2] = 0.0; // vertex_1
    colors[0] = 1.0; colors[1] = 0.0; colors[2] = 0.0; // vertex_1
    
    vertices[3] = 1.0; vertices[4] = 0.0; vertices[5] = 0.0; // vertex_2
    colors[3] = 1.0; colors[4] = 1.0; colors[5] = 1.0; // vertex_2
    
    vertices[6] = 1.0; vertices[7] = 0.0; vertices[8] = 1.0; // vertex_3
    colors[6] = 0.0; colors[7] = 1.0; colors[8] = 0.0; // vertex_3
    
    vertices[9] = 0.0; vertices[10] = 0.0; vertices[11] = 1.0; // vertex_4
    colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // vertex_4
    
    // shape_1_right
    vertices[12] = 1.0; vertices[13] = 2.0; vertices[14] = 1.0; // vertex_6
    colors[12] = 1.0; colors[13] = 1.0; colors[14] = 0.0; // vertex_6
    
    vertices[15] = 1.0; vertices[16] = 2.0; vertices[17] = 0.0; // vertex_7
    colors[15] = 1.0; colors[16] = 0.0; colors[17] = 1.0; // vertex_7
    
    // shape_1_back
    vertices[18] = 0.0; vertices[19] = 2.0; vertices[20] = 1.0; // vertex_5
    colors[18] = 0.0; colors[19] = 0.5; colors[20] = 0.5; // vertex_5
    
    vertices[21] = 0.0; vertices[22] = 2.0; vertices[23] = 0.0; // vertex_8
    colors[21] = 0.5; colors[22] = 0.5; colors[23] = 0.0; // vertex_8
    
    // shape_1_left
    vertices[24] = 0.0; vertices[25] = 0.0; vertices[26] = 1.0; // vertex_4
    colors[24] = 1.0; colors[25] = 0.0; colors[26] = 0.0; // vertex_4
    
    vertices[27] = 0.0; vertices[28] = 0.0; vertices[29] = 0.0; // vertex_1
    colors[27] = 1.0; colors[28] = 0.0; colors[29] = 0.0; // vertex_1
    
     // shape_1_bottom
    vertices[30] = 1.0; vertices[31] = 0.0; vertices[32] = 0.0; // vertex_2
    colors[30] = 1.0; colors[31] = 0.0; colors[32] = 0.0; // vertex_2
    
    vertices[33] = 1.0; vertices[34] = 2.0; vertices[35] = 0.0; // vertex_7
    colors[33] = 1.0; colors[34] = 1.0; colors[35] = 0.0; // vertex_7
    
    //  shape_1_top
    vertices[36] = 0.0; vertices[37] = 0.0; vertices[38] = 1.0; // vertex_4
    colors[36] = 0.0; colors[37] = 1.0; colors[38] = 0.0; // vertex_4
    
    vertices[39] = 1.0; vertices[40] = 0.0; vertices[41] = 1.0; // vertex_3
    colors[39] = 0.0; colors[40] = 0.3; colors[41] = 0.0; // vertex_3
    
    vertices[42] = 1.0; vertices[43] = 2.0; vertices[44] = 1.0; // vertex_6
    colors[42] = 0.0; colors[43] = 0.8; colors[44] = 0.0; // vertex_6
    
    vertices[45] = 0.0; vertices[46] = 2.0; vertices[47] = 1.0; // vertex_5
    colors[45] = 0.0; colors[46] = 0.5; colors[47] = 0.0; // vertex_5

    // shape_2_front
    vertices[48] = 0.0; vertices[49] = 0.0; vertices[50] = 0.0; // vertex_8
    colors[48] = 1.0; colors[49] = 0.0; colors[50] = 0.0; // vertex_8
    
    vertices[51] = 1.0; vertices[52] = 0.0; vertices[53] = 0.0; // vertex_7
    colors[51] = 1.0; colors[52] = 1.0; colors[53] = 1.0; // vertex_7
    
    vertices[54] = 1.0; vertices[55] = 0.0; vertices[56] = 1.0; // vertex_6
    colors[54] = 0.0; colors[55] = 1.0; colors[56] = 0.0; // vertex_6
    
    vertices[57] = 0.0; vertices[58] = 0.0; vertices[59] = 1.0; // vertex_5
    colors[57] = 0.0; colors[58] = 0.0; colors[59] = 1.0; // vertex_5
    
    // shape_2_right
    vertices[60] = 1.0; vertices[61] = 2.0; vertices[62] = 1.0; // vertex_16
    colors[60] = 1.0; colors[61] = 1.0; colors[62] = 0.0; // vertex_16
    
    vertices[63] = 1.0; vertices[64] = 2.0; vertices[65] = 0.0; // vertex_15
    colors[63] = 1.0; colors[64] = 0.0; colors[65] = 1.0; // vertex_15
    
    // shape_2_back
    vertices[66] = 0.0; vertices[67] = 2.0; vertices[68] = 1.0; // vertex_13
    colors[66] = 0.0; colors[67] = 0.5; colors[68] = 0.5; // vertex_13
    
    vertices[69] = 0.0; vertices[70] = 2.0; vertices[71] = 0.0; // vertex_14
    colors[69] = 0.5; colors[70] = 0.5; colors[71] = 0.0; // vertex_14
    
    // shape_2_left
    vertices[72] = 0.0; vertices[73] = 0.0; vertices[74] = 1.0; // vertex_5
    colors[72] = 1.0; colors[73] = 0.0; colors[74] = 0.0; // vertex_5
    
    vertices[75] = 0.0; vertices[76] = 0.0; vertices[77] = 0.0; // vertex_8
    colors[75] = 1.0; colors[76] = 0.0; colors[77] = 0.0; // vertex_8
    
     // shape_2_bottom
    vertices[78] = 1.0; vertices[79] = 0.0; vertices[80] = 0.0; // vertex_7
    colors[78] = 1.0; colors[79] = 0.0; colors[80] = 0.0; // vertex_7
    
    vertices[81] = 1.0; vertices[82] = 2.0; vertices[83] = 0.0; // vertex_15
    colors[81] = 1.0; colors[82] = 1.0; colors[83] = 0.0; // vertex_15
    
    //  shape_2_top
    vertices[84] = 0.0; vertices[85] = 0.0; vertices[86] = 1.0; // vertex_4
    colors[84] = 0.0; colors[85] = 1.0; colors[86] = 0.0; // vertex_4
    
    vertices[87] = 1.0; vertices[88] = 0.0; vertices[89] = 1.0; // vertex_3
    colors[87] = 0.0; colors[88] = 0.0; colors[89] = 0.0; // vertex_3
    
    vertices[90] = 1.0; vertices[91] = 2.0; vertices[92] = 1.0; // vertex_6
    colors[90] = 0.0; colors[91] = 0.8; colors[92] = 0.0; // vertex_6
    
    vertices[93] = 0.0; vertices[94] = 2.0; vertices[95] = 1.0; // vertex_5
    colors[93] = 0.0; colors[94] = 0.5; colors[95] = 0.0; // vertex_5    

    // shape_3_front
    vertices[96] = 1.0; vertices[97] = 2.0; vertices[98] = 1.0; // vertex_6
    colors[96] = 1.0; colors[97] = 0.0; colors[98] = 0.0; // vertex_6
    
    vertices[99] = 1.0; vertices[100] = 2.0; vertices[101] = 0.0; // vertex_7
    colors[99] = 1.0; colors[100] = 1.0; colors[101] = 1.0; // vertex_7
    
    vertices[102] = 3.0; vertices[103] = 2.0; vertices[104] = 1.0; // vertex_18
    colors[102] = 0.0; colors[103] = 1.0; colors[104] = 0.0; // vertex_18
    
    vertices[105] = 3.0; vertices[106] = 2.0; vertices[107] = 0.0; // vertex_19
    colors[105] = 0.0; colors[106] = 0.0; colors[107] = 1.0; // vertex_19
    
    // shape_3_right
    vertices[108] = 3.0; vertices[109] = 3.0; vertices[110] = 1.0; // vertex_17
    colors[108] = 1.0; colors[109] = 1.0; colors[110] = 0.0; // vertex_17
    
    vertices[111] = 3.0; vertices[112] = 3.0; vertices[113] = 0.0; // vertex_20
    colors[111] = 1.0; colors[112] = 0.0; colors[113] = 1.0; // vertex_20
    
    // shape_3_back
    vertices[114] = 1.0; vertices[115] = 3.0; vertices[116] = 1.0; // vertex_16
    colors[114] = 0.0; colors[115] = 0.5; colors[116] = 0.5; // vertex_16
    
    vertices[117] = 1.0; vertices[118] = 3.0; vertices[119] = 0.0; // vertex_15
    colors[117] = 0.5; colors[118] = 0.5; colors[119] = 0.0; // vertex_15
    
    // shape_3_left
    vertices[120] = 1.0; vertices[121] = 2.0; vertices[122] = 1.0; // vertex_6
    colors[120] = 1.0; colors[121] = 0.0; colors[122] = 0.0; // vertex_6
    
    vertices[123] = 1.0; vertices[124] = 2.0; vertices[125] = 0.0; // vertex_7
    colors[123] = 1.0; colors[124] = 0.0; colors[125] = 0.0; // vertex_7
    
     // shape_3_bottom
    vertices[126] = 3.0; vertices[127] = 2.0; vertices[128] = 0.0; // vertex_19
    colors[126] = 1.0; colors[127] = 0.0; colors[128] = 0.0; // vertex_19
    
    vertices[129] = 3.0; vertices[130] = 3.0; vertices[131] = 0.0; // vertex_20
    colors[129] = 1.0; colors[130] = 1.0; colors[131] = 0.0; // vertex_20
    
    //  shape_3_top
    vertices[132] = 1.0; vertices[133] = 2.0; vertices[134] = 1.0; // vertex_6
    colors[132] = 0.0; colors[133] = 1.0; colors[134] = 0.0; // vertex_6
    
    vertices[135] = 1.0; vertices[136] = 3.0; vertices[137] = 1.0; // vertex_16
    colors[135] = 0.0; colors[136] = 0.3; colors[137] = 0.0; // vertex_16
    
    vertices[138] = 3.0; vertices[139] = 3.0; vertices[140] = 1.0; // vertex_17
    colors[138] = 0.0; colors[139] = 0.8; colors[140] = 0.0; // vertex_17
    
    vertices[141] = 3.0; vertices[142] = 2.0; vertices[143] = 1.0; // vertex_18
    colors[141] = 0.0; colors[142] = 0.5; colors[143] = 0.0; // vertex_18

    // shape_4_front
    vertices[144] = 1.0; vertices[145] = 2.0; vertices[146] = 2.0; // vertex_10
    colors[144] = 1.0; colors[145] = 0.0; colors[146] = 0.0; // vertex_10
    
    vertices[147] = 3.0; vertices[148] = 2.0; vertices[149] = 1.0; // vertex_18
    colors[147] = 1.0; colors[148] = 1.0; colors[149] = 1.0; // vertex_18
    
    vertices[150] = 1.0; vertices[151] = 2.0; vertices[152] = 1.0; // vertex_6
    colors[150] = 0.0; colors[151] = 1.0; colors[152] = 0.0; // vertex_6
    
    // shape_4_right
    vertices[156] = 1.0; vertices[157] = 3.0; vertices[158] = 2.0; // vertex_12
    colors[156] = 1.0; colors[157] = 1.0; colors[158] = 0.0; // vertex_12
    
    vertices[159] = 3.0; vertices[160] = 3.0; vertices[161] = 1.0; // vertex_17
    colors[159] = 1.0; colors[160] = 0.0; colors[161] = 1.0; // vertex_17
    
    // shape_4_back
    vertices[162] = 1.0; vertices[163] = 3.0; vertices[164] = 1.0; // vertex_16
    colors[162] = 0.0; colors[163] = 0.5; colors[164] = 0.5; // vertex_16
    
    // shape_4_left
    vertices[168] = 1.0; vertices[169] = 2.0; vertices[170] = 2.0; // vertex_10
    colors[168] = 1.0; colors[169] = 0.0; colors[170] = 0.0; // vertex_10
    
    vertices[171] = 1.0; vertices[172] = 2.0; vertices[173] = 1.0; // vertex_6
    colors[171] = 1.0; colors[172] = 0.0; colors[173] = 0.0; // vertex_6
    
    // shape_4_bottom
    vertices[174] = 1.0; vertices[175] = 2.0; vertices[176] = 1.0; // vertex_6
    colors[174] = 1.0; colors[175] = 0.0; colors[176] = 0.0; // vertex_6
    
    vertices[177] = 1.0; vertices[178] = 3.0; vertices[179] = 1.0; // vertex_16
    colors[177] = 1.0; colors[178] = 1.0; colors[179] = 0.0; // vertex_16

    vertices[180] = 3.0; vertices[181] = 3.0; vertices[182] = 1.0; // vertex_17
    colors[180] = 0.0; colors[181] = 0.8; colors[182] = 0.0; // vertex_17
    
    vertices[183] = 3.0; vertices[184] = 2.0; vertices[185] = 1.0; // vertex_18
    colors[183] = 0.0; colors[184] = 0.5; colors[185] = 0.0; // vertex_18

    // shape_5_front
    vertices[186] = 0.0; vertices[187] = 2.0; vertices[188] = 1.0; // vertex_5
    colors[186] = 1.0; colors[187] = 0.0; colors[188] = 0.0; // vertex_5
    
    vertices[189] = 1.0; vertices[190] = 2.0; vertices[191] = 1.0; // vertex_6
    colors[189] = 1.0; colors[190] = 1.0; colors[191] = 1.0; // vertex_6
    
    vertices[192] = 1.0; vertices[193] = 2.0; vertices[194] = 2.0; // vertex_10
    colors[192] = 0.0; colors[193] = 1.0; colors[194] = 0.0; // vertex_10
    
    vertices[195] = 0.0; vertices[196] = 2.0; vertices[197] = 2.0; // vertex_9
    colors[195] = 0.0; colors[196] = 0.0; colors[197] = 1.0; // vertex_9
    
    // shape_5_right
    vertices[198] = 1.0; vertices[199] = 3.0; vertices[200] = 2.0; // vertex_12
    colors[198] = 1.0; colors[199] = 1.0; colors[200] = 0.0; // vertex_12
    
    vertices[201] = 1.0; vertices[202] = 3.0; vertices[203] = 1.0; // vertex_16
    colors[201] = 1.0; colors[202] = 0.0; colors[203] = 1.0; // vertex_16
    
    // shape_5_back
    vertices[204] = 0.0; vertices[205] = 3.0; vertices[206] = 2.0; // vertex_11
    colors[204] = 0.0; colors[205] = 0.5; colors[206] = 0.5; // vertex_11
    
    vertices[207] = 0.0; vertices[208] = 3.0; vertices[209] = 1.0; // vertex_13
    colors[207] = 0.5; colors[208] = 0.5; colors[209] = 0.0; // vertex_13
    
    // shape_5_left
    vertices[210] = 0.0; vertices[211] = 2.0; vertices[212] = 2.0; // vertex_9
    colors[210] = 1.0; colors[211] = 0.0; colors[212] = 0.0; // vertex_9
    
    vertices[213] = 0.0; vertices[214] = 2.0; vertices[215] = 1.0; // vertex_5
    colors[213] = 1.0; colors[214] = 0.0; colors[215] = 0.0; // vertex_5
    
     // shape_5_bottom
    vertices[216] = 0.0; vertices[217] = 3.0; vertices[218] = 1.0; // vertex_13
    colors[216] = 1.0; colors[217] = 0.0; colors[218] = 0.0; // vertex_13
    
    vertices[219] = 1.0; vertices[220] = 3.0; vertices[221] = 1.0; // vertex_16
    colors[219] = 1.0; colors[220] = 1.0; colors[221] = 0.0; // vertex_16
    
    //  shape_5_top
    vertices[222] = 0.0; vertices[223] = 2.0; vertices[224] = 2.0; // vertex_9
    colors[222] = 0.0; colors[223] = 1.0; colors[224] = 0.0; // vertex_9
    
    vertices[225] = 1.0; vertices[226] = 2.0; vertices[227] = 2.0; // vertex_10
    colors[225] = 0.0; colors[226] = 0.3; colors[227] = 0.0; // vertex_10
    
    vertices[228] = 1.0; vertices[229] = 3.0; vertices[230] = 2.0; // vertex_12
    colors[228] = 0.0; colors[229] = 0.8; colors[230] = 0.0; // vertex_12
    
    vertices[231] = 0.0; vertices[232] = 3.0; vertices[233] = 2.0; // vertex_11
    colors[231] = 0.0; colors[232] = 0.5; colors[233] = 0.0; // vertex_11
    
    
    glGenVertexArrays(2, &vaoID[0]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(2, vboID); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
  
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    
    delete [] vertices; // Delete our vertices from memory
}


void setupScene(void) {
    createBox();
}



/*!
 This function initializes the GLFW window
 */
int initWindow(void)
{
    // Initialize GLFW, and if it fails to initialize for any reason, print it out to STDERR.
    if (!glfwInit()) {
        fprintf(stderr, "Failed initialize GLFW.");
        exit(EXIT_FAILURE);
    }
    
    // Set the error callback, as mentioned above.
    glfwSetErrorCallback(error_callback);
    
    // Set up OpenGL options.
    // Use GLFW verion 3.3,
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    // Create a window to put our stuff in.
    window = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);
    
    // If the window fails to be created, print out the error, clean up GLFW and exit the program.
    if( window == NULL ){
        cout <<  "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible." << endl;
        glfwTerminate();
        system("pause");
        exit(-1);
    }
    
    // Use the window as the current context (everything that's drawn will be place in this window).
    glfwMakeContextCurrent(window);

    return 1;
}


/*!
 This function initializes glew
 */
bool initGlew(void)
{
    
    // Makes sure all extensions will be exposed in GLEW and initialize GLEW.
    glewExperimental = GL_TRUE;
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        cout <<  "Failed to initialize GLEW\n" << endl;
        system("pause");
        return -1;
    }
    
    cout <<  "OpenGL version supported by this platform " << glGetString(GL_VERSION) <<  endl;
}

/*!
 This function updates the virtual camera
 */
bool updateCamera()
{
    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    viewMatrix = getViewMatrix(); // get the current view matrix
    
    return true;
}



int main(int argc, const char * argv[])
{
    // Init the GLFW Window
    initWindow();
    
    // Set the keyboard callback so that when we press ESC, it knows what to do.
    glfwSetKeyCallback(window, key_callback);
    
    // Init the glew api
    initGlew();
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();

    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
     //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   
    /// IGNORE THE NEXT PART OF THIS CODE
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.57f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
     
    setupScene();
    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST); // ignore this line
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
       
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        // update the virtual camera
        updateCamera();


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        
        // Enable the shader program
        glUseProgram(program);
        
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // send the view matrix to our shader
        
        // Bind the buffer and switch it to an active buffer
        glBindVertexArray(vaoID[0]);
        
        // Draw the triangles
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 16);
        // Unbind our Vertex Array Object
        glBindVertexArray(0);
        
        // Unbind the shader program
        glUseProgram(0);
        
        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
}

