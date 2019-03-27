#include "main.h"
#include "timer.h"
#include "ball.h"
#include "floor.h"
#include "mountain.h"
#include "fuelbar.h"
#include "score.h"
#include "bullets.h"
#include "unistd.h"
#include "bomb.h"
#include "fuel.h"
#include "rings.h"
#include "health.h"
#include "compass.h"
#include "checkpoint.h"
#include "parachute.h"
#include "canon.h"
#include "arrow.h"
#include "spots.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int tot_score = 0;
int cnt = 1;
int cnt2 = 1;
int tot_altitude = 999;
float fuel_amt = -90.0f;
float speed = -90.0f;
int view_compass = 0;
Ball ball1;
Floor flr;
vector <Mountain> mnt;
vector <Bullets> bullets;
vector <Bomb> bombs;
vector <Fuel> fuels;
vector <Rings> rings;
vector <Checkpoint> checkpoints;
vector <Parachute> parachutes;
vector <Canon> canon;
vector <Spots> spots;
FuelBar fuelbar;
FuelBar speedbar;
Health healthbar;
Compass compass;
Arrow arrow;
int loop_flag;
int roll_flag;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float eye_view[3],target_view[3];
Score score[3][7], altitude[3][7];


Timer t60(1.0 / 60);
Timer t4(1.0 / 4);
Timer t3(1.0 / 3);
Timer tbull(1.5);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (eye_view[0], eye_view[1], eye_view[2]);
    glm::vec3 eye2 (0, 0, 1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_view[0], target_view[1], target_view[2]);
    glm::vec3 target2 (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    glm::vec3 up2 (0, 1, 0);
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matrices.view2 = glm::lookAt( eye2, target2, up2);
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP2 = Matrices.projection2 * Matrices.view2;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Render Score
    disp_score(tot_score%10,VP2,0);
    disp_score((tot_score%100)/10,VP2,1);
    disp_score(tot_score/100,VP2,2);
    // Render Altitude
    disp_altitude(tot_altitude%10,VP2,0);
    disp_altitude((tot_altitude%100)/10,VP2,1);
    disp_altitude(tot_altitude/100,VP2,2);
    // Scene render
    ball1.draw(VP);
    flr.draw(VP);
    for(int i=0;i<mnt.size();i++)    // MOUNTAINS
        mnt[i].draw(VP);
    fuelbar.draw(VP2, fuel_amt);
    speedbar.draw(VP2, speed);
    for(int i=0;i<bullets.size();i++)
        bullets[i].draw(VP);
    for(int i=0;i<bombs.size();i++)
        bombs[i].draw(VP);
    for(int i=0;i<rings.size();i++)
        rings[i].draw(VP);
    healthbar.draw(VP2);
    if(view_compass)
        compass.draw(VP2, -ball1.rotation_y);
    for(int i=0;i<parachutes.size();i++)
        parachutes[i].draw(VP);
    for(int i=0;i<fuels.size();i++)
        fuels[i].draw(VP);
    for(int i=0;i<checkpoints.size();i++)
    {
        float p[3],q[3];
        for(int j=0;j<3;j++)
        {
            p[j] = ball1.position[j];
            q[j] = checkpoints[i].position[j];
        }
        // checkpoints[0].color = COLOR_MAIN;
        double mod = sqrt( (p[0]-q[0])*(p[0]-q[0]) + (p[1]-q[1])*(p[1]-q[1]) + (p[2]-q[2])*(p[2]-q[2]));
        double beta = atan((p[1]-q[1])/(p[0]-q[0]));
        double gamma = atan(sqrt((p[0]-q[0])*(p[0]-q[0]) + (p[1]-q[1])*(p[1]-q[1]))/(p[2]-q[2]));
        checkpoints[i].draw(VP, beta, gamma, 0);
    }
    checkpoints[0].draw(VP, 0, 0, 1);
    arrow.draw(VP2);
    for(int i=0;i<canon.size();i++)
        canon[i].draw(VP);
    for(int i=0;i<spots.size();i++)
        spots[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    view_compass = 0;
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int V1 = glfwGetKey(window, GLFW_KEY_1); // First Person View
    int V2 = glfwGetKey(window, GLFW_KEY_2); // Top Down View
    int V3 = glfwGetKey(window, GLFW_KEY_3); // Tower View
    int V4 = glfwGetKey(window, GLFW_KEY_4); // Heli-Cam View
    int Q = glfwGetKey(window, GLFW_KEY_Q);
    int E = glfwGetKey(window, GLFW_KEY_E);
    int A = glfwGetKey(window, GLFW_KEY_A);
    int D = glfwGetKey(window, GLFW_KEY_D);
    int W = glfwGetKey(window, GLFW_KEY_W);
    int S = glfwGetKey(window, GLFW_KEY_S);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int T = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int Y = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    // int Y = glfwGetKey(window, GLFW_KEY_Y);
    int correctional_view = glfwGetKey(window, GLFW_KEY_P);
    int U = glfwGetKey(window, GLFW_KEY_U);
    int J = glfwGetKey(window, GLFW_KEY_J);
    int K = glfwGetKey(window, GLFW_KEY_K);
    int L = glfwGetKey(window, GLFW_KEY_L);

    if(!loop_flag && !roll_flag)
    {
        if (V1)// First Person View 
        {
            float theta = ball1.rotation_y * M_PI / 180.0f;
        	for(int i=0;i<2;i++)
            {    
                eye_view[i] = ball1.position[i];
                target_view[i] = ball1.position[i] + 0.01;;
            }
            eye_view[2] = ball1.position.z - 0.75f*cos(theta);
            eye_view[0] -= 0.75f*sin(theta);
            target_view[2] = ball1.position.z - 0.8f*cos(theta);
            target_view[0] -=  0.8f*sin(theta);
        }
        if(V2)// Top View
        {
            for(int i=0;i<3;i++){
                eye_view[i] = ball1.position[i];
                target_view[i] = ball1.position[i] + 0.01;
            }
            eye_view[1] += 10.0f;
        }
        if(V3)// Tower View
        {
            eye_view[0] = eye_view[1] = 4.0f;
            eye_view[2] = 0.0f;
            target_view[0] = target_view[1] = target_view[2] = 0.0f;
        }
        if(V4) // Heli-Cam View
        {
            double _x, _y;
            glfwGetCursorPos(window, &_x, &_y);
            // cout<<_x<<" "<<_y<<endl;
            _x = 300 - _x;
            _y = 300 - _y;
            double base_y = ball1.position.y + 1.0;
            double base_x = ball1.position.x;
            double base_z = ball1.position.z ;
            eye_view[0] = base_x;
            eye_view[1] = base_y + 1.0;
            eye_view[2] = base_z;
            for(int i=0;i<3;i++)
                target_view[i] = ball1.position[i]+0.01;
            double R = 3.0;
            double h = base_y + 0.005 * (_y);
            // x-z radius
            double r = sqrt(R*R - h*h);
            double dx = 0.005 * (_x);
            double nx = dx + base_x;
            double nz = base_z + sqrt(r*r - nx*nx);
            double ny = h;
            // cout<<nx<<" "<<ny<<" "<<nz<<endl;
            eye_view[0] = nx;
            eye_view[1] = ny;
            eye_view[2] = nz;
        }
        if(correctional_view)// Debugging 
        {
            for(int i=0;i<3;i++)
            {
                eye_view[i] = target_view[i] = ball1.position[i];
            }
            eye_view[0] += 2.0f; 
        }
        if(Q)
            ball1.anticlockwise();
        if(E)
            ball1.clockwise();
        if(A)
            ball1.left();
        if(D)
            ball1.right();
        if(W && ball1.mv_speed<=0.09)
            ball1.move_fwd();
        if(S && ball1.mv_speed>=-0.09)
            ball1.move_backward();
        if(up)
            ball1.ascend();
        if(down)
            ball1.descend();
        if(T == GLFW_PRESS && t4.processTick())
        {
            float theta = ball1.rotation_y * M_PI / 180.0f;
            float z_cor = ball1.position.z - 1.00 * cos(theta);
            float x_cor = ball1.position.x - 1.00 * sin(theta);
            bullets.push_back(Bullets(x_cor, ball1.position[1], z_cor, COLOR_GREEN, ball1.rotation_y));
            bullets[bullets.size()-1].trajectory = ball1.rotation_y;
            // cout<<ball1.position.x << ball1.position.y << ball1.position.z << endl;
        }
        if(Y == GLFW_PRESS && t3.processTick())
        {
            bombs.push_back(Bomb(ball1.position.x, ball1.position.y, ball1.position.z, COLOR_BLACK));
        }
        if(U)
            view_compass = 1;
        // Stunts
    }
    if(J)
    {
        // cout<<"h\n";
        loop_flag = 1;
    }
    if(L)
    {
        // cout<<"g\n";
        roll_flag = 1;
    }
}

void tick_camera()
{
    // cout<<"aaa"<<ball1.position.z<<endl;
    float theta = ball1.rotation_y * M_PI/180.00;
    eye_view[0] = ball1.position.x + 2*sin(theta);
    eye_view[1] = ball1.position.y + 1;
    eye_view[2] = ball1.position.z + 2*cos(theta);
    for(int i=0;i<3;i++)
        target_view[i] = ball1.position[i];
}
void tick_elements() {
    if(loop_flag && ball1.rotation_x >= cnt * 359)
    {
        loop_flag = 0;
        cnt++;
    }
    if(roll_flag && ball1.rotation_z >= cnt2 * 359)
    {
        roll_flag = 0;
        cnt2+=1;
    }
    // cout<<cnt2<<endl;
    tot_altitude = (ball1.position.y + (2.0f));
    // cout<<tot_altitude<<endl;
    fuel_amt += 0.1;
    float spd = -ball1.mv_speed;
    speed = spd * 1000;
    // cout<<speed<<endl;
    // cout<<"Speed = "<<spd<<endl;
    if(loop_flag)
        ball1.loop();
    else if(roll_flag)
        ball1.roll();
    else
        ball1.tick();
    tick_camera();
    fuelbar.tick();
    speedbar.tick();
    healthbar.tick();
    float p[3],q[3];
    for(int i=0;i<3;i++)
        p[i] = checkpoints[0].position[i], q[i] = ball1.position[i];
    arrow.tick(p[0], p[2], q[0], q[2], ball1.rotation_y);
    for(int i=0;i<bullets.size();i++)
        bullets[i].tick();
    for(int i=0;i<bombs.size();i++)
        bombs[i].tick();
    for(int i=0;i<parachutes.size();i++)
        parachutes[i].tick();
    for(int i=0;i<canon.size();i++)
        canon[i].tick();
    for(int i=0;i<checkpoints.size();i++)
        checkpoints[i].tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void spoil()
{
    int num = 200;
    for(int i=1;i<num;i++)
        spots.push_back(Spots(rand()%num/2, -1.98f, rand()%num/2, COLOR_RED));
    for(int i=1;i<num;i++)
        spots.push_back(Spots(-rand()%num/2, -1.98f, rand()%num/2, COLOR_RED));
    for(int i=1;i<num;i++)
        spots.push_back(Spots(rand()%num/2, -1.98f, -rand()%num/2, COLOR_RED));
    for(int i=1;i<num;i++)
        spots.push_back(Spots(-rand()%num/2, -1.98f, -rand()%num/2, COLOR_RED));
    // rings.push_back(Rings(0.0f, -1.5f, 0.0f,COLOR_BLACK));
}
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // ONE TIME CREATED
    
    ball1 = Ball(0, 0, 4, COLOR_RED);
    flr = Floor(0, -2.0, COLOR_OCEAN);
    fuelbar = FuelBar(-2.7, -3.8, 0.0, COLOR_RED);
    speedbar = FuelBar(2.7, -3.8, 0.0, COLOR_RED);
    healthbar = Health(0.0, -3.8f, 0.0f, COLOR_SAND);
    compass = Compass(2.0f ,2.8f ,0, COLOR_GREEN);
    arrow = Arrow(0, 2.8f,  COLOR_BLACK);
    for(int j=0;j<3;j++)
        for(int i=0;i<7;i++)
            score[j][i] = Score(3.5-0.3*j,3.7,COLOR_BLACK);
    for(int j=0;j<3;j++)
        for(int i=0;i<7;i++)
            altitude[j][i] = Score(0.3-0.3*j,-2.8,COLOR_BLACK);
    spoil();
    
    // RANDOM OBJECTS

    for(int i=1; i<20 ;i++)
    {
        // mnt.push_back(Mountain(2*i, -1, 2*i*sign, COLOR_SAND));
        // sign *= -1;
        mnt.push_back(Mountain(rand()%50, -1, rand()%50, COLOR_SAND));
        mnt.push_back(Mountain(-rand()%50, -1, rand()%50, COLOR_SAND));
        mnt.push_back(Mountain(-rand()%50, -1, -rand()%50, COLOR_SAND));
        mnt.push_back(Mountain(rand()%50, -1, -rand()%50, COLOR_SAND));

    }
    for(int i=0;i<2;i++)
    {
        fuels.push_back(Fuel(0,0,-2*i,COLOR_ORANGE));
        fuels.push_back(Fuel(rand()%10, 0, rand()%10 , COLOR_VOILET));
        fuels.push_back(Fuel(-rand()%10, 0, -rand()%10 , COLOR_VOILET));
        fuels.push_back(Fuel(rand()%10, 0, -rand()%10 , COLOR_VOILET));
        fuels.push_back(Fuel(-rand()%10, 0, rand()%10 , COLOR_VOILET));

    }
    // rings.push_back(Rings(0,0,-6,COLOR_VOILET));
    
    parachutes.push_back(Parachute(0.0f, 1.0f, -2.0f, COLOR_GREEN, 0.01f));
    parachutes.push_back(Parachute(0.0f, 1.0f, 2.0f, COLOR_GREEN, 0.01f));
    parachutes.push_back(Parachute(4.0f, 1.0f, -2.0f, COLOR_GREEN, 0.01f));
    parachutes.push_back(Parachute(-4.0f, 1.0f, -2.0f, COLOR_GREEN, 0.01f));
    parachutes.push_back(Parachute(-4.0f, 1.0f, -6.0f, COLOR_GREEN, 0.01f));
    
    checkpoints.push_back(Checkpoint(0, -1.99f, 0, COLOR_BLACK));
    for(int i=1;i<5;i++)
    {
        checkpoints.push_back(Checkpoint(rand()%10,-1.99f,rand()%10, COLOR_BLACK));
        checkpoints.push_back(Checkpoint(-rand()%15,-1.99f,-rand()%15, COLOR_BLACK));
        checkpoints.push_back(Checkpoint(rand()%20,-1.99f,-rand()%20, COLOR_BLACK));
        // checkpoints.push_back(Checkpoint(-rand()%8,-1.99f,rand()%8, COLOR_BLACK));
    }
   
    for(int i=1;i<=2;i++)
        rings.push_back(Rings(0, 0.0f, -2*i, COLOR_VOILET));
    rings.push_back(Rings(2, 0, 4, COLOR_VOILET));
    rings.push_back(Rings(-2, 0, -4, COLOR_VOILET));
    rings.push_back(Rings(0, 0, -4, COLOR_VOILET));
    rings.push_back(Rings(-4, 0, 0, COLOR_VOILET));

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void generate_bullets()
{
    if(checkpoints.empty())
        return ;
    float p[3],q[3];
    for(int i=0;i<3;i++)
    {
        p[i] = checkpoints[0].position[i];
        q[i] = ball1.position[i];
    }
    canon.push_back(Canon(p[0],p[1],p[2],0,-p[0]+q[0],-p[1]+q[1],-p[2]+q[2]));
}
int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            for(int i=0;i<bombs.size();i++)
            {
                if(bombs[i].position.y <= -5.0f)
                    bombs.erase(bombs.begin()+i);
            }
            for(int i=0;i<canon.size();i++)
            {
                bounding_box_t player;
                bounding_box_t can;
                player.x = ball1.position.x;
                player.y = ball1.position.y;
                player.z = ball1.position.z - ball1.width;
                player.height = ball1.out_rad;
                player.depth = 2 * ball1.width;
                player.width = ball1.out_rad;
                can.x = canon[i].position.x;
                can.y = (canon[i].position.y + canon[i].height)/2;
                can.z = canon[i].position.z; 
                can.height = (canon[i].height)/2;
                can.width = canon[i].in_rad;
                can.depth = canon[i].in_rad;
                if(detect_collision(player,can,1.0f))
                {
                   healthbar.limit -= 0.01f;
                   canon.erase(canon.begin()+i);
                } 
            }
            for(int i=0;i<bullets.size();i++)
            {
                bounding_box_t can,check;
                can.x = bullets[i].position.x;
                can.y = (bullets[i].position.y + bullets[i].height)/2;
                can.z = bullets[i].position.z; 
                can.height = (bullets[i].height)/2;
                can.width = bullets[i].in_rad;
                can.depth = bullets[i].in_rad;
                if(checkpoints.empty())
                    continue;
                check.x = checkpoints[0].position.x;
                check.y = (checkpoints[0].position.y + checkpoints[0].height)/2;
                check.z = checkpoints[0].position.z;
                check.height = checkpoints[0].height/2;
                check.width = checkpoints[0].rad/2;
                check.depth = checkpoints[0].rad/2;
                if(detect_collision(check, can, 0))
                {
                    checkpoints.erase(checkpoints.begin());
                    bullets.erase(bullets.begin() + i);
                    tot_score += 5;
                    cout<<"hit\n";
                }
            }
            for(int i=0;i<bombs.size();i++)
            {
                bounding_box_t check,bomb;
                check.x = checkpoints[0].position.x;
                check.y = (checkpoints[0].position.y + checkpoints[0].height)/2;
                check.z = checkpoints[0].position.z;
                check.height = checkpoints[0].height/2;
                check.width = checkpoints[0].rad/2;
                check.depth = checkpoints[0].rad/2;
                bomb.x = bombs[i].position.x;
                bomb.y = bombs[i].position.y;
                bomb.z = bombs[i].position.z;
                bomb.width = bomb.height = bomb.depth = 0.05f;
                // cout<<"Checkpoint at "<<checkpoints[0].position.y<<endl;
                // cout<<"Bomb at "<<bombs[i].position.y<<endl;
                // if(detect_collision(bomb,check,0))
                // {
                //     bombs.erase(bombs.begin()+i);
                //     checkpoints.erase(checkpoints.begin());
                // }
                check.y = checkpoints[0].position.y;
                check.width = check.depth = 0.7f;
                check.height = 0.0f;
                if(detect_collision(check, bomb, 0))
                {
                    cout<<"aa gaya\n";
                    checkpoints.erase(checkpoints.begin());
                    bombs.erase(bombs.begin()+i);
                    tot_score += 10;
                    draw();
                    break;
                }
            }
            for(int i=0;i<rings.size();i++)
            {
                float r = rings[i].in_rad;
                float p[3],q[3];
                for(int j=0;j<3;j++)
                {
                    p[j] = rings[i].position[j];
                    q[j] = ball1.position[j];
                }
                if(abs(p[2]-q[2])<=0.01)
                {
                    if((p[0]-q[0])*(p[0]-q[0])+(p[1]-q[1])*(p[1]-q[1])<=r*r)
                    {
                        rings.erase(rings.begin()+i);
                        tot_score += 2;
                    }
                }
            }
            for(int i=0;i<mnt.size();i++)
            {
                bounding_box_t player, mount;
                player.x = ball1.position.x;
                player.y = ball1.position.y;
                player.z = ball1.position.z - ball1.width;
                player.height = ball1.out_rad;
                player.depth = 2 * ball1.width;
                player.width = ball1.out_rad;
                mount.x = mnt[i].position.x;
                mount.y = mnt[i].position.y;
                mount.z = mnt[i].position.z;
                mount.height = 10.0f;
                mount.width = mnt[i].in_rad;
                mount.depth = mnt[i].in_rad;
                if(detect_collision(mount, player, 0))
                {
                    healthbar.limit -= 0.05f;
                    cout<<"NO-FLYING ZONE"<<endl;
                    mnt.erase(mnt.begin() + i);
                }
            }
            for(int i=0;i<fuels.size();i++)
            {
                bounding_box_t player, fuel;
                player.x = ball1.position.x;
                player.y = ball1.position.y;
                player.z = ball1.position.z - ball1.width;
                player.height = ball1.out_rad;
                player.depth = 2 * ball1.width;
                player.width = ball1.out_rad;
                fuel.x = fuels[i].position.x;
                fuel.y = fuels[i].position.y;
                fuel.z = fuels[i].position.z;
                fuel.width = fuel.height = fuel.depth = 0.1f;
                if(detect_collision(fuel, player, 0))
                {
                    cout<<"Fuel detected\n";
                    fuels.erase(fuels.begin() + i);
                    fuel_amt = -90.0f;
                }
            }
           
            for(int i=0;i<parachutes.size();i++)
            {
                bounding_box_t par;
                par.x = parachutes[i].position.x;
                par.y = parachutes[i].position.y;
                par.z = parachutes[i].position.z;
                float rad = parachutes[i].rad;
                for(int j=0;j<bullets.size();j++)
                {
                    bounding_box_t can;
                    can.x = bullets[j].position.x;
                    can.y = bullets[j].position.y;
                    can.z = bullets[j].position.z; 
                    double dx = can.x - par.x;
                    double dy = can.y - par.y;
                    double dz = can.z - par.z;
                    if(dx*dx + dy*dy + dz*dz <= rad*rad)
                    {
                        cout<<"Gone!\n";
                        parachutes.erase(parachutes.begin() + i);
                        bullets.erase(bullets.begin() + j);
                        tot_score += 5;
                    }
                }
            }
            if(game_over())
            {
                exit(0);
            }
            tick_elements();
            tick_input(window);
        }
        if (tbull.processTick()) {
            generate_bullets();
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}
bool game_over()
{
    if(ball1.position.y <= -1.9f )   
        return true;
    if(healthbar.limit <= -1 )
        return true;
    if(fuel_amt >= 90.0f)
        return true;
    return false;
}
bool detect_collision(bounding_box_t a, bounding_box_t b, float offset) {
   float diff_z = abs(a.z - b.z);
   float diff_y = abs(a.y - b.y);
   float diff_x = abs(a.x - b.x);
   // if(b.z <= 2.0f){
   // cout<<diff_x<<" "<<diff_y<<" "<<diff_z<<endl;
   // cout<<(diff_x <= a.width + b.width)<<(diff_z <= a.depth + b.depth)<<(diff_y <= a.height + b.height + 2.0f)<<endl;
   // }
   if (diff_z <= a.depth + b.depth && diff_x <= a.width + b.width && diff_y <= a.height + b.height + offset)
    return true;
   else
    return false;
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(60.0*M_PI/180.0, 1.0, 0.1, 10000.0);
    Matrices.projection2 = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void disp_score(int dig, glm::mat4 VP,int place)
{
    int arr[7][10]={
        {0,2,3,5,6,7,8,9},
        {0,1,2,3,4,7,8,9},
        {0,1,3,4,5,6,7,8,9},
        {0,2,3,5,6,8,9},
        {0,2,6,8},
        {0,4,5,6,8,9},
        {2,3,4,5,6,8,9},
    };
    int sz[7] = {8,8,9,7,4,6,7};
    vector <int> adj[7];
    for(int i=0;i<7;i++)
    {
        adj[i].insert(adj[i].end(), arr[i], arr[i]+sz[i]);
    }
    if(binary_search(adj[0].begin(),adj[0].end(),dig))
        score[place][0].draw(VP,0,0.2,0);
    if(binary_search(adj[1].begin(),adj[1].end(),dig))
        score[place][1].draw(VP,0.1,0.1,90);
    if(binary_search(adj[2].begin(),adj[2].end(),dig))
        score[place][2].draw(VP,0.1,-0.1,90);
    if(binary_search(adj[3].begin(),adj[3].end(),dig))
        score[place][3].draw(VP,0,-0.2,0);
    if(binary_search(adj[4].begin(),adj[4].end(),dig))
        score[place][4].draw(VP,-0.1,-0.1,90);
    if(binary_search(adj[5].begin(),adj[5].end(),dig))
        score[place][5].draw(VP,-0.1,0.1,90);
    if(binary_search(adj[6].begin(),adj[6].end(),dig))
        score[place][6].draw(VP,0,0,0);
}
void disp_altitude(int dig, glm::mat4 VP,int place)
{
    int arr[7][10]={
        {0,2,3,5,6,7,8,9},
        {0,1,2,3,4,7,8,9},
        {0,1,3,4,5,6,7,8,9},
        {0,2,3,5,6,8,9},
        {0,2,6,8},
        {0,4,5,6,8,9},
        {2,3,4,5,6,8,9},
    };
    int sz[7] = {8,8,9,7,4,6,7};
    vector <int> adj[7];
    for(int i=0;i<7;i++)
    {
        adj[i].insert(adj[i].end(), arr[i], arr[i]+sz[i]);
    }
    if(binary_search(adj[0].begin(),adj[0].end(),dig))
        altitude[place][0].draw(VP,0,0.2,0);
    if(binary_search(adj[1].begin(),adj[1].end(),dig))
        altitude[place][1].draw(VP,0.1,0.1,90);
    if(binary_search(adj[2].begin(),adj[2].end(),dig))
        altitude[place][2].draw(VP,0.1,-0.1,90);
    if(binary_search(adj[3].begin(),adj[3].end(),dig))
        altitude[place][3].draw(VP,0,-0.2,0);
    if(binary_search(adj[4].begin(),adj[4].end(),dig))
        altitude[place][4].draw(VP,-0.1,-0.1,90);
    if(binary_search(adj[5].begin(),adj[5].end(),dig))
        altitude[place][5].draw(VP,-0.1,0.1,90);
    if(binary_search(adj[6].begin(),adj[6].end(),dig))
        altitude[place][6].draw(VP,0,0,0);
}