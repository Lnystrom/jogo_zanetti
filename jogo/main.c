//roubado do zanetti
//cu de coelho

#include <locale.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

//Variáveis criadas quando houver necessidade
ALLEGRO_EVENT_QUEUE *fila = NULL;
ALLEGRO_TIMER *timer = NULL;

//variáveis de imagens
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *capa = NULL;

//tela de carregamento
ALLEGRO_BITMAP *carregamento = NULL;

//usado para resolver um bug
void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;

void allegro()
{
    //iniciando allegro, para receber input:
    if (!al_init())
    {
        printf("Não foi possível executar o allegro.\n");
    }

    if (!al_install_mouse())
    {
        printf("Não foi possível executar o mouse.\n");
    }
    if (!al_install_audio())
    {
        printf("Não foi possível instalar o áudio.\n");
    }

    //criando uma janela
    al_set_new_display_flags(ALLEGRO_FRAMELESS);
    display = al_create_display(800, 450);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "O bêbado e o equilibrista");
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
}

void tela_de_carregamento()
{
    int contador;
    int quadros = 79;
    char frame[100];
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
        al_destroy_bitmap(carregamento);
    }
}

void audio_menu()
{
    al_init_acodec_addon();
    ALLEGRO_SAMPLE *tema_sample;
    al_reserve_samples(1);
    tema_sample = al_load_sample("audio/tema.wav");
    al_play_sample(tema_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,0);
}
void jogo()
{
    printf("batata");
}
void fundo()
{

    ALLEGRO_KEYBOARD_STATE teclado;

    audio_menu();
    capa = al_load_bitmap("imagens/landscape.bmp");
    if (!capa)
    {
        printf("Erro em carregar imagens/landscape.bmp\n");
    }
    if (!al_install_keyboard())
    {
        printf("Não foi possível executar o teclado.\n");
    }
    while(1)
    {

        al_get_keyboard_state(&teclado);
        al_draw_bitmap(capa, 0, 0, 0);
          ALLEGRO_FONT * fonte24 = al_load_ttf_font("fonte.ttf",16,0);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_textf(fonte24, al_map_rgb(16, 6, 159), 180, 225, 0, "Pressione Enter Para Continuar ");
        al_flip_display(); //"Copies or updates the front and back buffers so that what has been drawn previously"


        if (al_key_down(&teclado, ALLEGRO_KEY_ENTER))
        {
            jogo();
        }
        if (al_key_down(&teclado, ALLEGRO_KEY_ESCAPE))
        {
            break;
        }
    }

}
void finalizar_allegro()
{
    al_destroy_display(display);
    al_uninstall_system();
    al_destroy_bitmap(capa);
}

int main(int argc, char **argv)
{

    //acentuação
    setlocale(LC_ALL, "Portuguese");

    //iniciando allegro
    allegro();

    //criando tela de carregamento
    tela_de_carregamento();

    //criando foto de capa
    fundo();

    finalizar_allegro();

    return 0;
}
