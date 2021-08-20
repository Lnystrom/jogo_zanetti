#include <stdio.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>


void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;


void funfa(bool teste, const char *descricao)
{
    if(teste)
        return;

    printf("couldn't initialize %s\n", descricao);
    exit(1);
}

void tela_de_carregamento()
{
    int contador;
    int quadros = 79;
    char frame[100];
    ALLEGRO_BITMAP *carregamento;
    for (contador = 1; contador < quadros; contador++)
    {
        sprintf(frame, "imagens/frames/frame_%.2d_delay-0.1s.gif", contador);
        // ("%s\n", frame); --> ver se está funcionado printf
        carregamento = al_load_bitmap(frame);
        if (!carregamento)
        {
            printf("Erro em carregar %s\n", frame);
        }
        al_draw_bitmap(carregamento,350, 250, 0);
        al_flip_display(); //"Copies or updates the front and back buffers so that what has been drawn previously"
        al_rest(0.1);
    }
    al_destroy_bitmap(carregamento);
}


void menu(ALLEGRO_BITMAP *capa, ALLEGRO_FONT* font, ALLEGRO_SAMPLE* tema, ALLEGRO_KEYBOARD_STATE ks, int *game_state)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(capa,0,0,0);
    if (fmod(al_get_time(), 2) < 1.0)
    {
        al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 480/2, ALLEGRO_ALIGN_CENTER, "Pressione Enter");
    }
    al_play_sample(tema,1,0,1, ALLEGRO_PLAYMODE_LOOP, NULL);
    al_get_keyboard_state(&ks);
    if (al_key_down(&ks, ALLEGRO_KEY_ENTER))
    {
        *game_state = 1;
        al_destroy_sample(tema);
    }

}

void cenario(ALLEGRO_BITMAP *parallax, float cenario_x)
{
        al_draw_bitmap(parallax, (int)cenario_x, 0, 0);

}

void jogo(ALLEGRO_SAMPLE* tema, float x, float y, ALLEGRO_BITMAP *cenario_3, ALLEGRO_BITMAP *cenario_2, ALLEGRO_BITMAP *cenario_1, const float FPS, int altura, int largura)
{
    al_clear_to_color(al_map_rgb(0,0,0));

    //-----------------------------------------------------
    static float cenario_x_1=0;
    static float cenario_x_2=0;
    static float cenario_x_3=0;
    cenario_x_1 -=  50.0/FPS;
    cenario_x_2 -=  75.0/FPS;
    cenario_x_3 -=  100.0/FPS;

    cenario( cenario_1, cenario_x_1);
    cenario( cenario_2, cenario_x_2);
    cenario( cenario_3, cenario_x_3);

    al_draw_filled_rectangle(x, y, x + 30, y + 30, al_map_rgb(255,255,0));

}

int main(int argc, char **argv)
{
    funfa(al_init(), "allegro");
    funfa(al_install_keyboard(), "teclado");

    const float FPS = 30.0;
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    funfa(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    funfa(queue, "queue");

    int largura = 1000;
    int altura = 600;

    al_set_new_display_flags(ALLEGRO_FRAMELESS);
   al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY* disp = al_create_display(largura, altura);
    funfa(disp, "display");
    //al_set_window_position(disp, 100, 100);
    al_set_window_title(disp, "O bêbado e o equilibrista");

    al_init_primitives_addon();


    al_init_font_addon();
    al_init_ttf_addon();
    funfa(al_init_ttf_addon(), "ttf addon");
    ALLEGRO_FONT* font = al_load_ttf_font("fonte.ttf", 18, 0);
    funfa(font, "font");

    funfa(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP *capa = al_load_bitmap("imagens/sprites/landscape.bmp");
    funfa(capa, "capa");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    tela_de_carregamento();

    funfa(al_install_audio(), "audio");
    funfa(al_init_acodec_addon(), "audio codecs");
    funfa(al_reserve_samples(16), "reserve samples");
    ALLEGRO_SAMPLE* botao = al_load_sample("audio/botao.wav");
    funfa(botao, "botao");
    ALLEGRO_SAMPLE* tema = al_load_sample("audio/tema.wav");
    funfa(tema, "musica tema");



     ALLEGRO_BITMAP *cenario_1;
    cenario_1 = al_load_bitmap("imagens/sprites/cenario_1.png");
    funfa(cenario_1, "cenario 1");
    al_convert_mask_to_alpha(cenario_1, al_map_rgb(255,255,255));

     ALLEGRO_BITMAP *cenario_2;
    cenario_2 = al_load_bitmap("imagens/sprites/cenario_2.png");
    funfa(cenario_2, "cenario 2");
    al_convert_mask_to_alpha(cenario_2, al_map_rgb(255,255,255));

    ALLEGRO_BITMAP *cenario_3;
    cenario_3 = al_load_bitmap("imagens/sprites/cenario_3.png");
    funfa(cenario_3, "cenario 3");
    al_convert_mask_to_alpha(cenario_3, al_map_rgb(255,255,255));

    ALLEGRO_KEYBOARD_STATE ks;

    int game_state = 0;

    float mov_x = 100;
    float mov_y = 400;

    bool done = false;

#define KEY_SEEN     1
#define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    while(!done)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if(key[ALLEGRO_KEY_UP])
                mov_y--;
            if(key[ALLEGRO_KEY_DOWN])
                mov_y++;
            if(key[ALLEGRO_KEY_LEFT])
                mov_x--;
            if(key[ALLEGRO_KEY_RIGHT])
                mov_x++;
            if(key[ALLEGRO_KEY_ESCAPE])
                done = true;

            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;

        redraw = true;
        break;


        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }


        if(redraw && game_state == 0 && al_is_event_queue_empty(queue))
        {
            menu(capa, font, tema, ks, &game_state);
            redraw = false;
        }
        else if(redraw && game_state == 1 && al_is_event_queue_empty(queue))
        {
            jogo(tema, mov_x, mov_y, cenario_3, cenario_2, cenario_1, FPS, altura, largura);
            redraw = false;
        }
       /* else if (redraw && game_state == 2 && al_is_event_queue_empty(queue))
        {
            break;
        }
        */
        al_flip_display();
    }

    al_destroy_bitmap(capa);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_sample(tema);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
