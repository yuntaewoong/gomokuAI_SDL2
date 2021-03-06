#define _CRT_SECURE_NO_WARNINGS
#include "CustomRenderer.h"
#include "han2unicode.h"


CustomRenderer::CustomRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}
void CustomRenderer::DrawEmptyCircle(int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);
	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);
	while (x >= 0)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
void CustomRenderer::DrawFilledCircle(int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);
	while (x >= 0)
	{
		SDL_RenderDrawLine(renderer, centreX - x, centreY + y, centreX + x, centreY + y);
		SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX + x, centreY - y);
		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
void CustomRenderer::ClearRenderer()
{
	this->DrawColorChange({ 255,255,255,0 });
	SDL_RenderClear(renderer);
}
void CustomRenderer::DrawRect(int x1, int y1, int width, int height)
{
	SDL_Rect r = { x1, y1, width, height };
	SDL_RenderDrawRect(renderer, &r);
}
void CustomRenderer::DrawFilledRect(int x1, int y1, int width, int height)
{
	SDL_Rect r = { x1, y1, width, height };
	SDL_RenderFillRect(renderer, &r);
}

void CustomRenderer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
}
void CustomRenderer::DrawText(string text, int x, int y, int fontSize,SDL_Color textColor)
{
	TTF_Font* font = TTF_OpenFont("c:\\windows\\fonts\\gulim.ttc", fontSize);
	unsigned short unicode[128];
	char temp[128];
	strcpy(temp, text.c_str());
	han2unicode(temp, unicode);
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(font, unicode, textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	SDL_Rect renderQuad = { x, y, text_width, text_height };
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}
void CustomRenderer::DrawColorChange(SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
void CustomRenderer::Render()
{
	SDL_RenderPresent(renderer);
}