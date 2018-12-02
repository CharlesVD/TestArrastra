#include <QCoreApplication>
#include <QTimer>
#include <iostream>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

ALLEGRO_DISPLAY *ventana;
ALLEGRO_KEYBOARD_STATE estadoTeclado;
ALLEGRO_MOUSE_STATE estadoMouse;

int main(int argc, char *argv[])
{
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_mouse();

    const uint Mx=800;
    const uint My=600;

    uint offSetX=50;
    uint offSetY=50;

   uint tamCuadro = 70;
   uint noCuadrosX = 10;
   uint noCuadrosY = 6;

   uint posCuadroX=30;
   uint posCuadroY=510;

   //int tablero[]

    ventana = al_create_display(Mx,My);

    QCoreApplication a(argc, argv);

    QTimer *entradas;
    entradas = new QTimer(&a);
    entradas->start(5);

    QTimer *esenario;
    esenario = new QTimer(&a);
    esenario->start(0);

    QObject::connect(entradas, &QTimer::timeout, [&]()
    {

        al_get_mouse_state(&estadoMouse);
        al_get_keyboard_state(&estadoTeclado);
        if (al_key_down(&estadoTeclado, ALLEGRO_KEY_ESCAPE))
        {
            a.exit(0);
        }
        if(estadoMouse.x>=posCuadroX && estadoMouse.x<posCuadroX+tamCuadro && estadoMouse.y>=posCuadroY && estadoMouse.y<posCuadroY+tamCuadro && estadoMouse.buttons==1)
        {
            posCuadroX=estadoMouse.x-(tamCuadro/2);
            posCuadroY=estadoMouse.y-(tamCuadro/2);
        }
        else
        {
            if(posCuadroX+(tamCuadro/2)<offSetX || posCuadroY+(tamCuadro/2)<offSetY || posCuadroX>=(tamCuadro*noCuadrosX) || posCuadroY>=(tamCuadro*noCuadrosY))
            {
                posCuadroX=30;
                posCuadroY=500;
            }
        }
        if(posCuadroX<=5 || posCuadroY<=5 || posCuadroX+tamCuadro>Mx || posCuadroY+tamCuadro>My)
        {
            posCuadroX=30;
            posCuadroY=500;
        }

        if(estadoMouse.x>=posCuadroX && estadoMouse.x<posCuadroX+tamCuadro && estadoMouse.y>=posCuadroY && estadoMouse.y<posCuadroY+tamCuadro && estadoMouse.buttons==0)
        {
            for(int y=0;y<(tamCuadro*noCuadrosY);y+=tamCuadro)
            {
                for(int x=0;x<(tamCuadro*noCuadrosX);x+=tamCuadro)
                {
                    if(estadoMouse.x>offSetX+x && estadoMouse.x<offSetX+x+tamCuadro && estadoMouse.y>offSetY+y && estadoMouse.y<offSetY+y+tamCuadro)
                    {
                        std::cout << "x:" << x/tamCuadro;
                        std::cout << " y:" << y/tamCuadro  << "\r";
                        posCuadroX=offSetX+x;
                        posCuadroY=offSetY+y;
                    }
                }
            }
        }

    });

    QObject::connect(esenario, &QTimer::timeout, [&]()
    {
        al_flip_display();
        al_clear_to_color(al_map_rgb(255,255,255));

        for(int i=0;i<=tamCuadro*noCuadrosX;i+=tamCuadro)
        {
            al_draw_line(i+offSetX,offSetY,i+offSetX,(tamCuadro*noCuadrosY)+offSetY,al_map_rgb(0,0,0),1);
        }
        for(int j=0;j<=tamCuadro*noCuadrosY;j+=tamCuadro)
        {
            al_draw_line(offSetX,j+offSetY,(tamCuadro*noCuadrosX)+offSetX,j+offSetY,al_map_rgb(0,0,0),1);
        }
        if(posCuadroX<=5 || posCuadroY<=5 || posCuadroX+tamCuadro>Mx || posCuadroY+tamCuadro>My)
        {
            posCuadroX=30;
            posCuadroY=500;
        }
        al_draw_filled_rectangle(posCuadroX,posCuadroY,posCuadroX+tamCuadro,posCuadroY+tamCuadro,al_map_rgb(0,255,0));

    });

    return a.exec();
}
