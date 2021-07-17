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

/*void desenhar()
{

}
*/

int main(int argc, char **argv)
{
//acentuação
    setlocale(LC_ALL,"");

//iniciando allegro
    allegro();

//criando tela de carregamento


//criando foto de capa
    fundo();

    al_rest(10.0);

    finalizar_allegro();


    return 0;
}

