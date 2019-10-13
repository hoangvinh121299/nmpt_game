#define SAFE_DELETE(p) {if(p) { delete(p); p = NULL;} } 

#define CLASS_NAME	"Castle Vania"
#define FULLSCREEN	false

//Define from main.cpp
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania NES"

#define SIMON_TEX_PATH L"Sprites\\simon.png"
#define SIMON_FLIPPED_TEX_PATH L"Sprites\\simon_flipped.png"
#define TITLESCR_TEX_PATH L"Sprites\\title_scr.png"
#define GROUND_INTRO_TEX_PATH L"Sprites\\intro.png"


#define BACKGROUND_COLOR D3DCOLOR_XRGB(250, 0, 0)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAX_FRAME_RATE 60

//ID Texture xxx
#define ID_TEX_SIMON 101
#define ID_TEX_SIMON_FLIPPED 102
#define ID_TEX_GROUND_INTRO 103
//ID Animation xxxxx
#define ID_ANI_SIMON_WALKING_LEFT 10001
#define ID_ANI_SIMON_WALKING_RIGHT 10002
