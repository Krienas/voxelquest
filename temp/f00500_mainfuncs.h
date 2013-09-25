


Singleton* singleton;


void processSpecialKeys(int key, int x, int y) {
    singleton->processSpecialKeys(key,x,y);
}
void processKey(unsigned char key, int x, int y, bool isPressed) {
    singleton->processKey(key,x,y,isPressed);
}
void keyboardUp(unsigned char key, int x, int y) {
    singleton->keyboardUp(key,x,y);
}
void keyboardDown(unsigned char key, int x, int y) {
    singleton->keyboardDown(key,x,y);
}
void mouseMovementWithButton(int x, int y) {
    singleton->mouseMove(x,y);
}
void mouseMovementWithoutButton(int x, int y) {
    singleton->mouseMove(x,y);
}
void mouseClick(int button, int state, int x, int y) {
    singleton->mouseClick(button,state,x,y);
}

void display(void) {
    singleton->display();
}

void reshape (int w, int h) {
    singleton->reshape(w,h);
}
void idleFunc(void) {
    singleton->display();
}

int MAX_CONSOLE_LINES = 500;

void RedirectIOToConsole()

{

    int hConHandle;

    long lStdHandle;

    CONSOLE_SCREEN_BUFFER_INFO coninfo;

    FILE *fp;

    // allocate a console for this app

    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),

                               &coninfo);

    coninfo.dwSize.Y = MAX_CONSOLE_LINES;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),

                               coninfo.dwSize);

    // redirect unbuffered STDOUT to the console

    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "w" );

    *stdout = *fp;

    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console

    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "r" );

    *stdin = *fp;

    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console

    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "w" );

    *stderr = *fp;

    setvbuf( stderr, NULL, _IONBF, 0 );

    std::ios::sync_with_stdio();

}




WebSocketServer myWebsocketServer;


int main(int argc, char* argv[])
{

    int winWidth;
    int winHeight;
    int scaleFactor;
    int resMode = 0;

    switch (resMode) {
        case 0:
            winWidth = 768;
            winHeight = 768;
            scaleFactor = 1;
        break;

        case 1:
            winWidth = 1024;
            winHeight = 512;
            scaleFactor = 1;
        break;

        case 2:
            winWidth = 2048;
            winHeight = 1024;
            scaleFactor = 2;
        break;

        case 3:
            winWidth = 2048;
            winHeight = 1280;
            scaleFactor = 1;
        break;
    }


    RedirectIOToConsole();

    glutInit(&argc, argv);


    //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  //GLUT_SINGLE

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    //glutInitWindowPosition(140, 10);
    glutCreateWindow("VoxelQuest");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        doTrace("There was an error with GLEW");
    }
    else {
        doTrace("GLEW_OK");
    }

    
    ////////////
    singleton = new Singleton();
    singleton->init(winWidth, winHeight, scaleFactor, &myWebsocketServer);
    

    glutDisplayFunc(display);
    glutIdleFunc(idleFunc);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMovementWithoutButton);
    glutMotionFunc(mouseMovementWithButton);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(processSpecialKeys);
    

    myWebsocketServer.run(argc, argv);




    

    return 0;
} 