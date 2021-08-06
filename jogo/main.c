#include <stdio.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;

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
        al_draw_bitmap(carregamento, 300, 200, 0);
        al_flip_display(); //"Copies or updates the front and back buffers so that what has been drawn previously"
        al_rest(0.1);
    }
}

void funfa(bool teste, const char *descricao)
{
    if(teste)
        return;

    printf("couldn't initialize %s\n", descricao);
    exit(1);
}

void menu(ALLEGRO_BITMAP *capa, ALLEGRO_FONT* font, ALLEGRO_SAMPLE* tema, ALLEGRO_KEYBOARD_STATE ks, int *game_state)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(capa,0,0,0);
    if (fmod(al_get_time(), 2) < 1.0)
    {
        al_draw_textf(font, al_map_rgb(255, 255, 255), 640/2, 480/2, ALLEGRO_ALIGN_CENTER, "Press Enter");
    }
    al_play_sample(tema,1,1,1, ALLEGRO_PLAYMODE_LOOP, NULL);
    al_flip_display();
    al_get_keyboard_state(&ks);
     if (al_key_down(&ks, ALLEGRO_KEY_ENTER))
        {
         *game_state = 1;
        }
}

void jogo()
{
    printf("batata");
}

int main(int argc, char **argv)
{
    funfa(al_init(), "allegro");
    funfa(al_install_keyboard(), "teclado");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    funfa(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    funfa(queue, "queue");

    int altura = 800;
    int largura =450;

    al_set_new_display_flags(ALLEGRO_FRAMELESS);
    ALLEGRO_DISPLAY* disp = al_create_display(altura, largura);
    funfa(disp, "display");
    al_set_window_position(disp, 200, 200);
    al_set_window_title(disp, "O bêbado e o equilibrista");

    al_init_font_addon();
    al_init_ttf_addon();
    funfa(al_init_ttf_addon(), "ttf addon");
    ALLEGRO_FONT* font = al_load_ttf_font("fonte.ttf", 18, 0);
    funfa(font, "font");

    funfa(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP *capa = al_load_bitmap("imagens/landscape.bmp");
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

    ALLEGRO_KEYBOARD_STATE ks;

    int game_state = 0;

    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // game logic goes here.
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_CHAR:
            if(event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            break;
        }

        if(redraw && game_state == 0 && al_is_event_queue_empty(queue))
        {
            menu(capa, font, tema, ks, &game_state);
            redraw = false;
        }
        else if(redraw && game_state == 1 && al_is_event_queue_empty(queue))
        {
            jogo();
            redraw = false;
        }
    }
    al_destroy_bitmap(capa);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_sample(tema);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
