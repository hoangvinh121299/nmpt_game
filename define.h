#define SAFE_DELETE(p) {if(p) { delete(p); p = NULL;} } 

#define CLASS_NAME	"Castle Vania"
#define FULLSCREEN	false

//Define from main.cpp
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania NES"

#define BRICK_TEXTURE_PATH L"brick.png"
#define MARIO_TEXTURE_PATH L"mario.png"
#define BALL_TEXTURE_PATH L"ball.png"


#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 0, 0)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAX_FRAME_RATE 60
