#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

char* prog = "arrowkey";

int width;
int height;
float pad;

SDL_Surface *screen = NULL;

int fontsize = 24;

TTF_Font* font = NULL;

int rows = 5;
int cols = 13;

const char* keys[] = { "`1234567890-=",
                       "qwertyuiop/\3",
                       "asdfghjkl;'\1",
                       "\2zxcvbnm,.[]",
                       "\4\\", };

const char* caps[] = { "~!@#$%^&*()_+",
                       "QWERTYUIOP?\3",
                       "ASDFGHJKL:\"\1",
                       "\5ZXCVBNM<>{}",
                       "\4|", };

int iscaps = 0;

enum
{
    _X = 0,
    _Y = 1,
};

int cursor[] = { 0, 0 };

int start (void);
void clear (SDL_Surface *sur);
void rect (SDL_Surface *sur, float x, float y, float w, float h, int color);
int text (char* s, int x, int y);
int poll_sdl (void);
void finish (void);
void cursor_y (int y);
void cursor_x (int x);

int last_x;

int start (void)
{
    if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
    {
        fprintf (stderr, "%s: %s\n", prog, SDL_GetError ());
        return 1;
    }
    putenv(strdup("SDL_VIDEO_CENTERED=1"));
    screen = SDL_SetVideoMode (width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption (prog, NULL);
    if (SDL_Flip (screen) == -1)
    {
        fprintf (stderr, "%s: %s\n", prog, SDL_GetError ());
        finish ();
        return 1;
    }
    // load font
    if (TTF_Init () != 0)
    {
        fprintf (stderr, "%s: %s\n", prog, TTF_GetError ());
        finish ();
        return 1;
    }
    font = TTF_OpenFont ("/usr/share/fonts/TTF/DejaVuSans.ttf", fontsize);
    return 0;
}

int draw_keyboard (void)
{
    int xstep = width/cols;
    int ystep = height/rows;
    int pad = ((width > height) ? width : height)/200;
    int xstart = (width - xstep * cols)/2;
    int ystart = (height - ystep * rows)/2;
    int w;
    int h = ystep - pad*2;
    int off = pad;
    int i;
    int j;
    int joff;
    int color;
    int jwidth;
    float x, y;
    char s [10];
    clear (screen);
    for (i = 0; i < rows; i++)
    {
        for (j = 0, joff = 0; j + joff < cols; j++)
        {
            if (j == cursor[_X] && i == cursor[_Y])
            {
                if (keys [i][j] == '\2' && iscaps)
                {
                    if (iscaps == 1)
                        color = 0xA8A8B0;
                    if (iscaps == 2)
                        color = 0x9898A0;
                }
                else
                    color = 0xB0B0B8;
            }
            else
            {
                if (keys [i][j] == '\2' && iscaps)
                {
                    if (iscaps == 1)
                        color = 0xB8B8C0;
                    if (iscaps == 2)
                        color = 0xA8A8B0;
                }
                else
                    color = 0xCCCCD0;
            }
            switch (keys [i][j])
            {
                case '\1':
                    strcpy (s, "Enter");
                    jwidth = 2;
                    break;
                case '\2':
                    if (iscaps == 1)
                        strcpy (s, "Shift");
                    else if (iscaps == 2)
                        strcpy (s, "Caps");
                    else
                        strcpy (s, "Shift");
                    jwidth = 2;
                    break;
                case '\3':
                    strcpy (s, "Back");
                    jwidth = 2;
                    break;
                case '\4':
                    strcpy (s, "Space");
                    jwidth = cols - 1;
                    break;
                default:
                    if (iscaps)
                        s [0] = caps [i][j];
                    else
                        s [0] = keys [i][j];
                    s [1] = '\0';
                    jwidth = 1;
                    break;
            }
            w =  xstep*jwidth - pad*2;
            x = (j + joff) * xstep + off + xstart;
            y = i * ystep + off + ystart;
            rect (screen, x, y, w, h, color);
            text (s, x + w/2, y + h/2);
            joff += jwidth - 1;
        }
    }
    if (SDL_Flip (screen) == -1)
    {
        fprintf (stderr, "%s: %s\n", prog, SDL_GetError ());
        finish ();
        return 1;
    }
    return 0;
}

void clear (SDL_Surface *sur)
{
    SDL_FillRect (sur, NULL, 0xEEEEEE);
}

void rect (SDL_Surface *sur, float x, float y, float w, float h, int color)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_FillRect (sur, &rect, color);
}

int text (char* s, int x, int y)
{
    SDL_Surface* sur = NULL;
    SDL_Color color = { 0xFF, 0xFF, 0xFF };
    SDL_Rect offset;
    sur = TTF_RenderText_Solid (font, s, color);
    if (sur == NULL)
    {
        fprintf (stderr, "%s: %s\n", prog, TTF_GetError ());
        return 1;
    }
    offset.x = x - sur->w/2;
    offset.y = y - sur->h/2;
    if (SDL_BlitSurface (sur, NULL, screen, &offset) < 0)
    {
        fprintf (stderr, "%s: %s\n", prog, TTF_GetError ());
        return 1;
    }
    return 0;
}

int poll_sdl (void)
{
    SDL_Event event;
    while (SDL_PollEvent (&event) != 0)
    {
        if (event.type == SDL_QUIT)
            return 1;
        else if (event.type == SDL_KEYDOWN)
        {
            int key = event.key.keysym.sym;
            switch (key)
            {
                case SDLK_ESCAPE:
                    return 1;
                    break;
                case SDLK_UP:
                    cursor_y (-1);
                    draw_keyboard ();
                    break;
                case SDLK_DOWN:
                    cursor_y (+1);
                    draw_keyboard ();
                    break;
                case SDLK_LEFT:
                    cursor_x (-1);
                    draw_keyboard ();
                    break;
                case SDLK_RIGHT:
                    cursor_x (+1);
                    draw_keyboard ();
                    break;
                case SDLK_SPACE:
                    switch (keys [cursor[_Y]][cursor[_X]])
                    {
                        case '\1':
                            return 1;
                            break;
                        case '\2':
                            if (iscaps < 2)
                                iscaps++;
                            else
                                iscaps = 0;
                            draw_keyboard ();
                            break;
                        case '\3':
                            printf ("\b");
                            break;
                        case '\4':
                            printf (" ");
                            break;
                        default:
                            if (iscaps)
                                printf ("%c", caps [cursor [_Y]][cursor [_X]]);
                            else
                            {
                                printf ("%c", keys [cursor [_Y]][cursor [_X]]);
                            }
                            if (iscaps == 1)
                            {
                                iscaps = 0;
                                draw_keyboard ();
                            }
                            break;
                    }
                    fflush (stdout);
                    break;
            }
        }
    }
    return 0;
}

void wait (void)
{
    SDL_Delay ((Uint32) 100);
}

void cursor_x (int x)
{
    char c;
    cursor[_X] += x;
    // wrap
    if (cursor[_X] < 0)
        cursor[_X] = strlen (keys[cursor[_Y]]) - 1;
    else
        cursor[_X] %= strlen (keys[cursor[_Y]]);
    c = keys[cursor[_Y]][cursor[_X]];
    if (c == '\4' && x < 0)
        last_x = cols -2;
    return;
}

void cursor_y (int y)
{
    char c;
    c = keys [cursor [_Y]][cursor [_X]];
    if (c == '\\')
        cursor [_X] = cols;
    if (c == '\4')
    {
        cursor[_X] = last_x;
    }
    if (keys[cursor[_Y]][0] == '\2')
    {
        if (cursor[_X] == 0)
            cursor[_X] = 0;
        else
            cursor[_X] += 1;
    }
    cursor[_Y] += y;
    if (cursor[_Y] < 0)
        cursor[_Y] = rows - 1;
    else if (cursor[_Y] >= rows)
        cursor[_Y] = 0;
    if (keys[cursor[_Y]][0] == '\2')
    {
        if (cursor[_X] < 2)
            cursor[_X] = 0;
        else
            cursor[_X] -= 1;
    }
    if (keys[cursor[_Y]][0] == '\4')
    {
        if (cursor[_X] == cols - 1)
            cursor[_X] = 1;
        else
        {
            last_x = cursor[_X];
            cursor[_X] = 0;
        }
    }
    if (strlen (keys[cursor[_Y]]) - 1 < cursor [_X])
        cursor [_X] = strlen (keys[cursor[_Y]]) - 1;
}

void finish (void)
{
    SDL_FreeSurface (screen);
    TTF_Quit ();
    SDL_Quit ();
}

int main (int argc, const char **argv)
{
    int status = 0;
    width = 1040;
    height = 400;
    status = start ();
    if (status)
    {
        finish ();
        exit (status);
    }
    status = draw_keyboard ();
    if (status)
    {
        finish ();
        exit (status);
    }
    while (1)
    {
        status = poll_sdl ();
        if (status)
        {
            break;
        }
    }
    finish ();
    exit (status);
}
