//roubado do zanetti

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <locale.h>


//Variáveis criadas quando houver necessidade
ALLEGRO_EVENT_QUEUE *fila = NULL;
ALLEGRO_TIMER *timer = NULL;


//variáveis de imagens
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *capa = NULL;


//tela de carregamento
ALLEGRO_BITMAP *carregamento = NULL;

//usado para resolver um bug
void * __gxx_personality_v0=0;
void * _Unwind_Resume =0;



void allegro()
{
//iniciando allegro, para receber input:
    if (!al_init())
    {
        printf("Não foi possível executar o allegro.\n");
    }
    if (!al_install_keyboard())
    {
        printf("Não foi possível executar o teclado.\n");
    }
    if (!al_install_mouse())
    {
        printf("Não foi possível executar o mouse.\n");
    }
    //criando uma janela
    display = al_create_display(800, 450);
    al_init_image_addon();
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
        al_draw_bitmap(carregamento,300,200,0);
        al_flip_display(); //"Copies or updates the front and back buffers so that what has been drawn previously"
        al_rest(0.1);
    }

}

void fundo()
{

    capa = al_load_bitmap("imagens/landscape.bmp");

    if (!capa)
    {
        printf("Erro em carregar imagens/landscape.bmp\n");
    }
    al_draw_bitmap(capa,0,0,0);
    al_flip_display(); //"Copies or updates the front and back buffers so that what has been drawn previously"
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
    setlocale(LC_ALL,"");


//iniciando allegro
    allegro();
    al_rest(5.0);

//criando tela de carregamento
    tela_de_carregamento();

//criando foto de capa
    fundo();

    al_rest(10.0);

    finalizar_allegro();


    return 0;
}

