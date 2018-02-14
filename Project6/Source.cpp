#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
#include <stdio.h>
#include "mappy_A5.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <vector>
using namespace std;

const int WIDTH = 630;
const int HEIGHT = 630;

bool keys[] = { false, false, false, false, false, false,false, false, false };
enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE, ESCAPE, A, B, C };

enum STATE { MENU, GAMEOVER, PLAYER1, PLAYER2 };

void ChangeState(int &state, int newState);


int main(int argc, char **argv)
{
	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool done = false;
	bool render = false;
	srand(time(NULL));
	vector<int> vec;

	int gameTime = 0;
	int frames = 0;
	int gameFPS = 0;


	//==============================================
	//PROJECT VARIABLES
	//==============================================
	int state = -1;

	int mapColumns = 24;
	int mapRows = 24;
	int mapSize = 576; //100
	int tileSize = 63; //zaktualizuj wymiary tile'a
	int boardSize = tileSize*mapColumns;
	int worldWidth = mapRows*tileSize;
	int worldHeight = mapColumns*tileSize;
	int score = 0;
	int maxScore = 3; //uzywam predefiniowanego
	int map[] =
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 0,
		0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
		0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0,// start
		0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0,
		0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0,
		0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0,
		0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	
	
	
	int xOff = -8 * tileSize;
	int yOff = -4 * tileSize;//pozycjonowanie kamery
	
	int enemy1PosCurr = 26;
	int enemy1PosMap = map[26];
	
	int playerPosCurr = 202;
	int playerPosMap = map[202];//pozycjonowanie na mapie
	
	int playerWorldX = 11 * tileSize;
	int playerWorldY = 9 * tileSize; 
	
	int enemy1WorldX = 1 * tileSize;
	int enemy1WorldY = 1 * tileSize;//pozycjonowanie globalne


	
	

	int moves[] = { -24,-1,1,24 };
	int movesSize = 4;   //do generowania ruchow przeciwnika
	

	

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18;
	ALLEGRO_BITMAP *bgSheet = NULL;
	ALLEGRO_BITMAP *pawn1 = NULL;
	ALLEGRO_BITMAP *pawn2 = NULL;
	ALLEGRO_BITMAP *enemy1 = NULL;
	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if (!al_init())
	{
		return -1;
	}
	display = al_create_display(WIDTH, HEIGHT);

	if (!display)
	{
		return -1;
	}

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	if (!al_install_keyboard())
	{
		return -1;
	}
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();


	//==============================================
	//PROJECT INIT
	//==============================================
	font18 = al_load_font("arial.ttf", 18, 0);
	bgSheet = al_load_bitmap("bg.png");
	pawn1 = al_load_bitmap("pawn1.png");
	pawn2 = al_load_bitmap("pawn2.png");
	enemy1 = al_load_bitmap("enemy1.png");
	ChangeState(state, MENU);

	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 20);
	if (!timer)
	{
		return -1;
	}
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();




	//===================================================================================================================================
	//MAIN LOOP
	//===================================================================================================================================
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		int liczba = moves[rand() % movesSize]; //deklaruj tutaj bo musi byc w petli allegrowej
		//==============================================
		//INPUT
		//==============================================
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = true;
				break;
			case ALLEGRO_KEY_B:
				keys[B] = true;
				break;
			case ALLEGRO_KEY_C:
				keys[C] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			case ALLEGRO_KEY_B:
				keys[B] = false;
				break;
			case ALLEGRO_KEY_C:
				keys[C] = false;
				break;
			}
		}
		//==============================================
		//GAME UPDATE
		//==============================================
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS===========
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//=====================

			if (state == MENU)
			{
				if (keys[SPACE])
					ChangeState(state, PLAYER1);
			}
			
			//==============================================
			//LOGIC PLAYER1
			//==============================================
			
			else if (state == PLAYER1)
			{
				if (keys[ESCAPE])
				{
					ChangeState(state, GAMEOVER);
				}

				
				if (keys[RIGHT])
				{
					xOff -= keys[RIGHT] * tileSize;
					playerPosCurr = playerPosCurr + 1;
					playerPosMap = map[playerPosCurr];
					cout << "ppc" << playerPosCurr << endl;
					cout << "map" << map[playerPosCurr] << endl;
					if (map[playerPosCurr] == 0)
					{
						playerPosCurr = playerPosCurr - 1;
						playerPosMap = map[playerPosCurr];
					
						cout << "ppc" << playerPosCurr << endl;
						cout << "map" << map[playerPosCurr] << endl;
						xOff = xOff + tileSize;
					}
				}

				if (keys[LEFT])
				{
					xOff += keys[LEFT] * tileSize;
					playerPosCurr = playerPosCurr - 1;
					playerPosMap = map[playerPosCurr];
					cout << "ppc" << playerPosCurr << endl;
					cout << "map" << map[playerPosCurr] << endl;
					if (map[playerPosCurr] == 0)
					{
						playerPosCurr = playerPosCurr + 1;
						playerPosMap = map[playerPosCurr];
						cout << "ppc" << playerPosCurr << endl;
						cout << "map" << map[playerPosCurr] << endl;
						xOff = xOff - tileSize;
					}
				}
					
					if (keys[DOWN])
					{
						yOff -= keys[DOWN] * tileSize;
						playerPosCurr = playerPosCurr + 24;
						playerPosMap = map[playerPosCurr];
						cout << "ppc" << playerPosCurr << endl;
						cout << "map" << map[playerPosCurr] << endl;
						if (map[playerPosCurr] == 0)
						{
							playerPosCurr = playerPosCurr - 24;
							playerPosMap = map[playerPosCurr];
							cout << "ppc" << playerPosCurr << endl;
							cout << "map" << map[playerPosCurr] << endl;
							yOff = yOff + tileSize;
						}
					
					}

					if (keys[UP])
					{
						yOff += keys[UP] * tileSize;
						playerPosCurr = playerPosCurr - 24;
						playerPosMap = map[playerPosCurr];
						cout << "ppc" << playerPosCurr << endl;
						cout << "map" << map[playerPosCurr] << endl;
						if (map[playerPosCurr] == 0)
						{
							playerPosCurr = playerPosCurr + 24;
							playerPosMap = map[playerPosCurr];
							cout << "ppc" << playerPosCurr << endl;
							cout << "map" << map[playerPosCurr] << endl;
							yOff = yOff - tileSize;
						}
					}
					render = true;
					
					// enemy1PosCurr =enemy1PosCurr+ moves[rand() % movesSize]; //losowy ruch int liczba = moves[rand()% moveSize];
				
					
					enemy1PosCurr = enemy1PosCurr + liczba;
					cout << "e1pc"<<enemy1PosCurr<<endl;
					vec.push_back(liczba);///////////////////////////////////////////////////////////////////////////////////TUTEJ
					enemy1PosMap = map[enemy1PosCurr];
					
					
					if (map[enemy1PosCurr] == 0 && vec.back()==-24) ////////////////////////////////random w gore
					{
						enemy1PosCurr = enemy1PosCurr + 24;
						enemy1PosMap = map[enemy1PosCurr];
						cout << "e1PosCurr" << enemy1PosCurr << endl;
						cout << "e1map" << map[enemy1PosCurr] << endl;
					//	yOff = yOff - tileSize;
						enemy1WorldY = enemy1WorldY + 24 * tileSize;
					
					}
					else if (map[enemy1PosCurr] == (1||2) && vec.back() == -24)
					{
						enemy1WorldY = enemy1WorldY - 24 * tileSize;
						enemy1PosMap = map[enemy1PosCurr];
					}
					
					if (map[enemy1PosCurr] == 0 && vec.back() == -1) ////////////////////////////////random w lewo
					{
						enemy1PosCurr = enemy1PosCurr + 1;
						enemy1PosMap = map[enemy1PosCurr];
						cout << "e1PosCurr" << enemy1PosCurr << endl;
						cout << "e1map" << map[enemy1PosCurr] << endl;
						//	yOff = yOff - tileSize;
						enemy1WorldX = enemy1WorldX + 24 * tileSize;

					}
					else if (map[enemy1PosCurr] == (1||2) && vec.back() == -1)
					{
						enemy1WorldY = enemy1WorldY -1 * tileSize;
						enemy1PosMap = map[enemy1PosCurr];
					}
					
					if (map[enemy1PosCurr] == 0 && vec.back() == 1) ////////////////////////////////random w prawo
					{
						enemy1PosCurr = enemy1PosCurr - 1;
						enemy1PosMap = map[enemy1PosCurr];
						cout << "e1PosCurr" << enemy1PosCurr << endl;
						cout << "e1map" << map[enemy1PosCurr] << endl;
						//	yOff = yOff - tileSize;
						enemy1WorldX = enemy1WorldX -1 * tileSize;

					}
					else if (map[enemy1PosCurr] == (1||2) && vec.back() == 1)
					{
						enemy1WorldY = enemy1WorldY + 1 * tileSize;
						enemy1PosMap = map[enemy1PosCurr];
					}
					
					if (map[enemy1PosCurr] == 0 && vec.back() == 24) ////////////////////////////////random w dol
					{
						enemy1PosCurr = enemy1PosCurr - 24;
						enemy1PosMap = map[enemy1PosCurr];
						cout << "e1PosCurr" << enemy1PosCurr << endl;
						cout << "e1map" << map[enemy1PosCurr] << endl;
						//	yOff = yOff - tileSize;
						enemy1WorldY = enemy1WorldY - 24 * tileSize;

					}
					else if (map[enemy1PosCurr] == (1||2) && vec.back() == 24)
					{
						enemy1WorldY = enemy1WorldY + 24 * tileSize;
						enemy1PosMap = map[enemy1PosCurr];
					}
					
					if (map[playerPosCurr] == 2) ///////////////////////////////zbieranie punktow
					{
						map[playerPosCurr] = 1; 
						score++;
					
					}
					
					if (score == maxScore)
					{
						done = true;
					}
					
					if (enemy1PosCurr == playerPosCurr) /////////////////////////koniec gry
					{
						done = true;
					}


				}
				////////////////////////////////////////////////////////////////////////////////////////////
				else if (state == GAMEOVER)
				{
					if (keys[SPACE])
						done = true;

					if (keys[UP])
						ChangeState(state, MENU);
				}
			}

			//==============================================
			//RENDER
			//==============================================

			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;
				al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS);    

																								//BEGIN PROJECT RENDER================
				if (state == MENU)
				{

					al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "spacja by grac");
				}
				else if (state == PLAYER1)
				{
					al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "escape by wyjsc");
					render = true;

					for (int i = 0; i < mapSize; i++)
					{
						al_draw_bitmap_region(bgSheet, tileSize*map[i], 0, tileSize, tileSize, xOff + tileSize*(i % mapColumns), yOff + tileSize*(i / mapColumns), 0);
					}
					//al_draw_bitmap(pawn1, tileSize / 2 + 20 + 20 * turnp1, tileSize / 2, 0);
				
					al_draw_bitmap(pawn2, tileSize * 2, tileSize * 4, 0);////srednie wspolrzedne na centrowanie kamery
					
				//	int x = enemy1WorldX + xOff;
				//	int y = enemy1WorldY + yOff; 
					al_draw_bitmap(enemy1, enemy1WorldX + xOff, enemy1WorldY + yOff, 0); //rysowanie na globalu
					

				
				}

				else if (state == GAMEOVER)
				{
					al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "spacja by wyjsc z gry, gora by wyjsc do menu");
				}

				//FLIP BUFFERS========================
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}

		//==============================================
		//DESTROY PROJECT OBJECTS
		//==============================================

		//SHELL OBJECTS=================================
		al_destroy_font(font18);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(pawn1);
		al_destroy_bitmap(pawn2);
		al_destroy_bitmap(enemy1);
		al_destroy_bitmap(bgSheet);
		al_destroy_display(display);
		MapFreeMem();
		return 0;
	}

	void ChangeState(int &state, int newState)
	{
		if (state == MENU)
		{
			cout << "wychodzisz z MENU\n";
		}
		else if (state == PLAYER1)
		{

			cout << "wychodziz z PLAYER1\n";
		}
		
		else if (state == GAMEOVER)
		{
			cout << "wychodzisz z GAMEOVER\n";
		}

		state = newState;

		if (state == MENU)
		{
			cout << "wchodzisz do MENU\n";
		}
		else if (state == PLAYER1)
		{
			cout << "wchodzisz do PLAYER1\n";
		}
		
		else if (state == GAMEOVER)
		{
			cout << "wchodzisz do GAMEOVER\n";
		}
	}