#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <atlimage.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define WINDOW_X 1280
#define WINDOW_Y 720

#define FRAME_X 135
#define FRAME_Y 150
#define MOVE 0
#define DEATH 1

#pragma comment(lib, "msimg32.lib")

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif

typedef struct _Point {
	int x;
	int y;

	_Point& operator=(_Point& rhs)
	{
		x = rhs.x;
		y = rhs.y;

		return *this;
	}
} Point;

typedef struct _Bullet
{
	bool view = false;
	int HP = 1;

	Point position; //자신의 위치
	int direction; //자신의 방향 
	CImage sprite_image; // 자신의 이미지 
	Point sprite_Size;
	int sprite_entirecount;
	int sprite_currentindex;
	int Move_speed;
	RECT boundingBox;// 충돌처리
	Point RealSize; // 실제사이즈

	void init() // 초기화 
	{
		sprite_image.Load(TEXT("./이미지/bullet.png"));
		sprite_Size.x = 50;
		sprite_Size.y = 50;
		sprite_entirecount = 1;
		sprite_currentindex = 0;


		RealSize.x = 50;
		RealSize.y = 50;

		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;
		Move_speed = 30;

	}
	void Draw(HDC hdc, HWND hwnd)
	{
		int SpriteWidth = sprite_image.GetWidth() / sprite_Size.x;
		int SpriteHeight = sprite_image.GetHeight() / sprite_Size.y;

		int xCoord = sprite_currentindex % SpriteWidth;
		int yCoord = sprite_currentindex / SpriteWidth;

		sprite_image.Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
			xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

	}
	void Update()
	{
		(++sprite_currentindex) %= sprite_entirecount;
		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;
		Move();
	}
	void Move()
	{
		switch (direction)
		{
		case UP:
		{
			if (boundingBox.top > 0)
			{
				position.y -= Move_speed;
			}
			else
			{
				view = false;
			}
		}
		break;
		case DOWN:
		{
			if (boundingBox.bottom < WINDOW_Y)
			{
				position.y += Move_speed;
			}
			else
			{
				view = false;
			}
		}
		break;
		case LEFT:
		{
			if (boundingBox.left > 0)
			{
				position.x -= Move_speed;
			}
			else
			{
				view = false;
			}
		}
		break;
		case RIGHT:
		{
			if (boundingBox.right < WINDOW_X)
			{
				position.x += Move_speed;
			}
			else
			{
				view = false;
			}
		}
		break;
		}
	}
}Bullet;
Bullet bullet[100];
typedef struct _Character
{
	Point position; //자신의 위치
	int direction; //자신의 방향 
	CImage sprite_image; // 자신의 이미지 
	Point sprite_Size;
	int sprite_entirecount;
	int sprite_currentindex;
	int Move_speed;
	RECT boundingBox;// 충돌처리
	Point RealSize; // 실제사이즈
	void init() // 초기화 
	{
		sprite_image.Load(TEXT("./이미지/yeti2.png"));
		sprite_Size.x = 123;
		sprite_Size.y = 175;
		sprite_entirecount = 3;
		sprite_currentindex = 0;
		srand((unsigned int)time(NULL));
		direction = rand() % 4 + 1;
		position.x = WINDOW_X / 2;
		position.y = WINDOW_Y / 2;
		RealSize.x = 150;
		RealSize.y = 150;
		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;
		Move_speed = 25;

	}
	void Draw(HDC hdc, HWND hwnd)
	{
		int SpriteWidth = sprite_image.GetWidth() / sprite_Size.x;
		int SpriteHeight = sprite_image.GetHeight() / sprite_Size.y;

		int xCoord = sprite_currentindex % SpriteWidth;
		int yCoord = sprite_currentindex / SpriteWidth;

		sprite_image.Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
			xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

	}
	void Update()
	{
		(++sprite_currentindex) %= sprite_entirecount;
		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;
		Move();
	}
	void Move()
	{
		switch (direction)
		{
		case UP:
		{
			if (boundingBox.top > 0)
			{
				position.y -= Move_speed;
			}
			else
			{
				direction = DOWN;
			}
		}
		break;
		case DOWN:
		{
			if (boundingBox.bottom < WINDOW_Y)
			{
				position.y += Move_speed;
			}
			else
			{
				direction = UP;
			}
		}
		break;
		case LEFT:
		{
			if (boundingBox.left > 0)
			{
				position.x -= Move_speed;
			}
			else
			{
				direction = RIGHT;
			}
		}
		break;
		case RIGHT:
		{
			if (boundingBox.right < WINDOW_X)
			{
				position.x += Move_speed;
			}
			else
			{
				direction = LEFT;
			}
		}
		break;
		}
	}
}Character;
typedef struct _Object
{
	Point position; //자신의 위치

	CImage sprite_image; // 자신의 이미지 
	Point sprite_Size;
	int sprite_entirecount;
	int sprite_currentindex;
	bool view = true;
	RECT boundingBox;// 충돌처리
	Point RealSize; // 실제사이즈
	int hp = 3;
	void init() // 초기화 
	{
		sprite_image.Load(TEXT("./이미지/BLOCK.png"));
		sprite_Size.x = 448;
		sprite_Size.y = 442;
		sprite_entirecount = 1;
		sprite_currentindex = 0;
		srand((unsigned int)time(NULL));

		RealSize.x = 250;
		RealSize.y = 250;

		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;

	}
	void Draw(HDC hdc, HWND hwnd)
	{
		int SpriteWidth = sprite_image.GetWidth() / sprite_Size.x;
		int SpriteHeight = sprite_image.GetHeight() / sprite_Size.y;

		int xCoord = sprite_currentindex % SpriteWidth;
		int yCoord = sprite_currentindex / SpriteWidth;

		sprite_image.Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
			xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

	}
	void Update()
	{
		if (hp <= 0)
			view = false;
		if (check(bullet) == true)
		{
			hp -= 1;

		}
		(++sprite_currentindex) %= sprite_entirecount;
		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;

	}
	bool check(Bullet* bullet)
	{
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].view)
			{
				for (int i = 0; i < 100; i++)
				{
					if (bullet[i].view)
					{
						if (bullet[i].boundingBox.right < boundingBox.left)
						{
							return false;
						}
						if (bullet[i].boundingBox.bottom < boundingBox.top)
						{
							return false;
						}
						if (bullet[i].boundingBox.left > boundingBox.right)
						{
							return false;
						}
						if (bullet[i].boundingBox.top > boundingBox.bottom)
						{
							return false;
						}

						bullet[i].HP = 0;
						bullet[i].view = false;
						return true;
					}
				}
			}
		}
	}


}Object;

typedef struct _Monster
{// 이미지 사이즈 엔타이어 카운트
	bool view = false;
	int HP=1;

	Point position; //자신의 위치
	int direction; //자신의 방향 
	CImage sprite_image[2]; // 자신의 이미지 
	Point sprite_Size[2];
	int sprite_entirecount[2];
	int sprite_currentindex;
	int Move_speed;


	RECT boundingBox;// 충돌처리
	Point RealSize; // 실제사이즈
	void init() // 초기화 
	{
		sprite_image[MOVE].Load(TEXT("./이미지/move.png"));
		sprite_image[DEATH].Load(TEXT("./이미지/dead.png"));

		sprite_Size[MOVE].x = 109;
		sprite_Size[MOVE].y = 67;

		sprite_Size[DEATH].x = 105;
		sprite_Size[DEATH].y = 67;


		sprite_entirecount[MOVE] = 3;
		sprite_entirecount[DEATH] = 4;

		sprite_currentindex = 0;

		RealSize.x = 100;
		RealSize.y = 100;

		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;
		Move_speed = 10;

	}
	void Draw(HDC hdc, HWND hwnd, int life)
	{
		if (life == 0)
		{
			int SpriteWidth = sprite_image[DEATH].GetWidth() / sprite_Size[DEATH].x;
			int SpriteHeight = sprite_image[DEATH].GetHeight() / sprite_Size[DEATH].y;

			int xCoord = sprite_currentindex % SpriteWidth;
			int yCoord = sprite_currentindex / SpriteWidth;

			sprite_image[DEATH].Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
				xCoord * sprite_Size[DEATH].x, yCoord * sprite_Size[DEATH].y, sprite_Size[DEATH].x, sprite_Size[DEATH].y);

		}
		else
		{
			
			int SpriteWidth = sprite_image[MOVE].GetWidth() / sprite_Size[MOVE].x;
			int SpriteHeight = sprite_image[MOVE].GetHeight() / sprite_Size[MOVE].y;

			int xCoord = sprite_currentindex % SpriteWidth;
			int yCoord = sprite_currentindex / SpriteWidth;

			sprite_image[MOVE].Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
				xCoord * sprite_Size[MOVE].x, yCoord * sprite_Size[MOVE].y, sprite_Size[MOVE].x, sprite_Size[MOVE].y);
		}
	}



	void Update()
	{
		if (HP == 0)
		{
			(++sprite_currentindex) %= sprite_entirecount[DEATH];
		}


		else
		{
			(++sprite_currentindex) %= sprite_entirecount[MOVE];
		}


		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;

		Move();
	}
	void Move()
	{
		switch (direction)
		{
		case UP:
		{
			if (boundingBox.top > 0)
			{
				position.y -= Move_speed;
			}
			else
			{
				view = false;
			}
		}
		break;
		case DOWN:
		{
			if (boundingBox.bottom < WINDOW_Y)
			{
				position.y += Move_speed;
			}
			else
			{
				view = false;
			}
		}
		break;
		case LEFT:
		{
			if (boundingBox.left > 0)
			{
				position.x -= Move_speed;
			}
			else
			{
				view = false;
			}
		}
		break;
		case RIGHT:
		{
			if (boundingBox.right < WINDOW_X)
			{
				position.x += Move_speed;
			}
			else
			{
				view = false;
			}
		}
		break;
		}

	}

}Monster;

Character hero;
Object object[3];
Monster monster[50];

bool Checkcollision(Bullet gun, Object obstacle)
{
	if (gun.boundingBox.right > obstacle.boundingBox.left)
	{
		return true;
	}
	if (gun.boundingBox.bottom > obstacle.boundingBox.top)
	{
		return true;
	}
	if (gun.boundingBox.left < obstacle.boundingBox.right)
	{
		return true;
	}
	if (gun.boundingBox.top < obstacle.boundingBox.bottom)
	{
		return true;
	}
	return false;
}
HINSTANCE g_hInstance;
LPCTSTR lpszClass = "Window Class Name";
LPCTSTR lpszWindowName = "Window Program 5-5";

// 함수 선언
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInstance = hInstance;

	// 윈도우 클래스 구조체 값 설정
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// 윈도우 클래스 등록
	RegisterClassEx(&WndClass);

	RECT rt = { 0, 0, WINDOW_X, WINDOW_Y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 생성
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 50, 50,
		rt.right - rt.left, rt.bottom - rt.top, NULL, (HMENU)NULL, hInstance, NULL);

	// 윈도우 출력
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 이벤트 루프 처리
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;

	static int startX, startY;
	static bool Drag;
	static int endX, endY;
	static HBITMAP hBitmap, hOldBitmap;
	static int BulletIndex;
	static int monsterindex;
	static float time = 0.0f;

	// 메시지 처리하기
	switch (uMsg)
	{
	case WM_CREATE:
	{   hdc = GetDC(hWnd);
	GetClientRect(hWnd, &crt);
	Drag = false;
	BulletIndex = 0;

	hero.init();
	for (int i = 0; i < 3; i++)
	{
		object[i].init();
	}
	for (int i = 0; i < 100; i++)
	{
		bullet[i].init();
	}
	for (int i = 0; i < 50; i++)
	{
		monster[i].init();
	}
	SetTimer(hWnd, 0, 150, NULL);

	object[0].position.x = 100;
	object[0].position.y = 100;

	object[1].position.x = 800;
	object[1].position.y = 10;

	object[2].position.x = 400;
	object[2].position.y = 300;
	ReleaseDC(hWnd, hdc);


	}
	break;
	case WM_TIMER:
	{
		hdc = GetDC(hWnd);
		hero.Update();
		for (int i = 0; i < 3; i++)
		{
			if (object[i].view == true)
			{
				object[i].Update();

			}

		}
		for (int i = 0; i < 50; i++)
		{
			if (bullet[i].view == true)
			{
				bullet[i].Update();

			}
		}

		time += 0.01f;
		if (time > 0.1f)
		{
			int a = rand() % 3;
			monster[monsterindex].view = true;
			monster[monsterindex].direction = rand() % 4 + 1;
	
			monster[monsterindex].position = object[a].position;
			monsterindex++;
			time = 0.0f;
		}
		for (int i = 0; i < 100; i++)
		{
			if (monster[i].view == true)
			{
				monster[i].Update();

			}
		}

		/*for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (bullet[j].view == true)
				{
					if (Checkcollision(bullet[j], object[j]) == true)
					{
						bullet[j].HP = 0;
						object[j].hp -= 1;
					}

				}
			}
		}*/
		InvalidateRgn(hWnd, NULL, false);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		memdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
		hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);
		Rectangle(memdc, 0, 0, WINDOW_X, WINDOW_Y);

		for (int i = 0; i < 3; i++)
		{
			if (object[i].view == true)
			{
				object[i].Draw(memdc, hWnd);
			}

		}
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].view == true)
			{
				bullet[i].Draw(memdc, hWnd);
			}
		}

		for (int i = 0; i < 50; i++)
		{

			if (monster[i].view == true)
			{
				if (monster[i].HP > 0)
				{
					monster[i].Draw(memdc, hWnd, 1);
				}
				else
				{
					monster[i].Draw(memdc, hWnd, 0);
				}

			}
		}

		hero.Draw(memdc, hWnd);
		BitBlt(hdc, 0, 0, crt.right, crt.bottom, memdc, 0, 0, SRCCOPY); // 더블 버퍼링 

		DeleteObject(SelectObject(memdc, hOldBitmap));
		DeleteDC(memdc);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CHAR:
	{hdc = GetDC(hWnd);
	switch (wParam)
	{
	case 'j': case 'J':
	{
	}
	case 'q': case 'Q':
	{
		PostQuitMessage(0);
	}
	break;
	case 'e': case 'E':
	{
	}
	break;
	case 's': case 'S':
	{
	}
	break;
	case 't': case 'T':
	{
	}
	break;
	}
	ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_KEYDOWN:
	{hdc = GetDC(hWnd);
	switch (wParam)
	{
	case VK_UP:
	{
		hero.direction = UP;
	}
	break;
	case VK_DOWN:
	{
		hero.direction = DOWN;
	}
	break;
	case VK_LEFT:
	{
		hero.direction = LEFT;
	}
	break;
	case VK_RIGHT:
	{
		hero.direction = RIGHT;
	}
	break;
	case VK_SPACE:
	{
		bullet[BulletIndex].view = true; // 총 발사!
		bullet[BulletIndex].position.x = hero.position.x + (hero.RealSize.x / 2);
		bullet[BulletIndex].position.y = hero.position.y + (hero.RealSize.y / 2);
		bullet[BulletIndex].direction = hero.direction;
		if (BulletIndex < 100)
		{
			BulletIndex++;

		}

	}

	break;
	}
	ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		int mousex = LOWORD(lParam);
		int mousey = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int mousex = LOWORD(lParam);
		int mousey = HIWORD(lParam);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}