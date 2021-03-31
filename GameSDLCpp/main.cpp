#include "Common_Function.h"
#include "MainObject.h"

bool Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return false;
  }
  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if (g_screen == NULL)
  {
    return false;
  }
  return true;
}

int main(int arc, char*argv[])
{
	bool is_quit = FALSE;
	if(Init()==false)
		return 0;
	g_bkground = SDLCommonFunc::LoadImage("darkbg.jpg");
	if(g_bkground == NULL)
	return 0;
	

	MainObject human_object;
	human_object.SetRect(100, 200);
	bool ret = human_object.LoadImg("pew.png");
	if(!ret)
	{
		return 0;
	}

	while(!is_quit)
	{
		while(SDL_PollEvent(&g_even))
		{
			if(g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			human_object.HandleinputAction(g_even);
		}

		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
		human_object.Show(g_screen);
		human_object.HandleMove();

		for(int i=0; i < human_object.GetAmoList().size();i++)
		{
			std::vector<AmoObject*> amo_list = human_object.GetAmoList();
			AmoObject* p_amo = amo_list.at(i);
			if(p_amo->get_is_move())
			{
				p_amo->Show(g_screen);
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				if(p_amo != NULL)
				{
					amo_list.erase(amo_list.begin()+i);
					human_object.SetAmoList(amo_list);
					delete p_amo;
					p_amo = NULL;
				}
			}
		}

		if(SDL_Flip(g_screen)==-1)
			return 0;
	}
	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 0;
}