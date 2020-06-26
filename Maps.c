#include <ncurses.h>
#include <stdio.h>
#include <string.h>

/********************************* Metodos *********************************/

WINDOW *create_newwin(int height, int width, int starty, int startx);
WINDOW *win_menu(int height, int width, int starty, int startx);
void mover();
void dibujo();
void destroy_win(WINDOW *local_win);
void borde();
void matrizmapa();
void destino();
void menu();
void matrizatxt();
void atxt();
void bordemenu();

/*************************** variables globales ***************************/



int dib_x= 3, dib_y=26, key;
int matrizmap[102][52];
char matriztxt[102][52];
int opcion=0;
int dix=0, diy=0;
char nombre[20];
  int matriz[5][10]=           //matriz mapa
      {    
           1,1,1,0,0,1,0,0,1,0,
           0,0,1,0,0,1,0,0,1,0,
           1,1,1,1,1,1,1,1,1,1,
           0,0,1,0,0,1,0,0,1,0,
           0,0,1,0,0,1,0,0,1,0
      };


/********************************* main *********************************/

int main()
{ 
   initscr();
       keypad( stdscr, TRUE ); /* activa / desactiva las teclas especiales */
       curs_set( FALSE );      /* hace invisible el cursor fisico */    
       start_color();  
            matrizmapa();
            menu();
       
   endwin(); 
}

/********************************* main *********************************/


WINDOW *create_newwin(int height, int width, int starty, int startx)
{ 
   WINDOW *local_win;
   local_win = newwin(height, width, starty, startx);
   borde();
 
      int i, y, x=0, l=0, total= 1;
      int temp =0;
 
      int inix=0,iniy =0;
      int finx=0,finy=0;

      for(x=0; x<5; x++)
      {
          for(y=0; y<10; y++)
          {
           inix = (x*10)+1;
           iniy = (y*10)+1;
 
           finx=inix+10;
           finy=iniy+10;

                if(matriz[x][y]== 0)
                {
                       for(i=inix; i<finx;i++)
                       {
                	   for(l=iniy;l<finy;l++)
                           {
                                   init_pair(6,COLOR_WHITE, COLOR_BLACK);
                                   attron(COLOR_PAIR(6));
       		                      mvprintw(i,l, "@");
                                   attroff(COLOR_PAIR(6));             
                       
                                   init_pair(1,COLOR_WHITE, COLOR_BLUE);
                                   attron(COLOR_PAIR(1));
                                    mvprintw(diy,dix, "DI");  
                                   attroff(COLOR_PAIR(1));
                           }
                       }
                }
                else
                {  
                       for(i=inix; i<finx;i++)
                       {
                	   for(l=iniy;l<finy;l++)
                           {
       		               mvprintw(i,l, " ");     
                             
                           }
                        }       
                 }
          }
       }
  
      wrefresh(local_win); 
      return local_win;
}

void mover()
{

   WINDOW *my_win;
   my_win = create_newwin(52, 102, 0, 0);
  // ruta(30, 40);
    dib_x=2;
    dib_y=25;
    matrizatxt();
     while((key != KEY_F( 2 )))
     {     
          while((dib_x!= dix) || (dib_y!= diy))
          {   
			   WINDOW *my_win;
			   my_win = create_newwin(52, 102, 0, 0);
			    mvprintw(1 ,2 , "su cordenada es %d,%d ", dib_y,dib_x );
			    mvprintw(0 ,3 , "Usted debe llegar a:%d,%d ", diy, dix);
			   dibujo(dib_y,dib_x);
			   key = getch();	   
			      //if(key == KEY_RIGHT){dib_x++;}
			      if((key == KEY_RIGHT) && (matrizmap[dib_x+1][dib_y]== 1)){dib_x++;}
			      if((key == KEY_LEFT)  && (matrizmap[dib_x-1][dib_y]== 1)){dib_x--;}
			      if((key == KEY_DOWN)  && (matrizmap[dib_x][dib_y+1]== 1)){dib_y++;}	   
			      if((key == KEY_UP)    && (matrizmap[dib_x][dib_y-1]== 1)){dib_y--;}  
                              matriztxt[dib_x][dib_y]= 'o';
			  destroy_win(my_win);       
		
			  wclear(my_win); 
			  delwin(my_win);
              
                      
                      endwin();                     
           }
       mvprintw(14 ,25 , " Usted ha llegado a su destino: %d,%d ", diy,dix );
       mvprintw(15 ,25 , " Presione F2 para salir");
       key = getch();
       }
     //  
}
void dibujo(int f, int c)
{
         init_pair(4,COLOR_RED, COLOR_BLACK);
         attron(COLOR_PAIR(4));
   
             mvprintw( f, c,"*" );

         attroff(COLOR_PAIR(4));
}

void destroy_win(WINDOW *local_win)
{ 
      int i, y, total= 1;
      for(i=1; i<52; i++)
      {
          for(y=1; y<102; y++)
          {
                mvprintw(i ,y , " " );
          }
      }
      wrefresh(local_win);    
}
     
void borde()
{
     init_pair(5,COLOR_YELLOW, COLOR_BLACK);
         attron(COLOR_PAIR(5));
     int i=0;
        for(i=0;i<51;i++) 
        {
        	move(i,0);
        	printw("|");
        	move(i,101 );
        	printw("|");
        }

 	for(i=0;i<101;i++)
	{
		move(0,i);
		printw("-");
		move(51,i);
		printw("-");
	}
     mvprintw(0,101, "*");
     mvprintw(0,0, "*");
     mvprintw(51,0, "*");
     mvprintw(51,101, "*");
    attroff(COLOR_PAIR(5));
}

void bordemenu()
{
     init_pair(5,COLOR_YELLOW, COLOR_BLACK);
     attron(COLOR_PAIR(5));
     int i=0;
        for(i=0;i<15;i++) 
        {
        	move(i,0);
        	printw("|");
        	move(i,75);
        	printw("|");
        }

 	for(i=0;i<75;i++)
	{
		move(0,i);
		printw("-");
		move(15,i);
		printw("-");
	}
     mvprintw(0,75, "*");
     mvprintw(0,0, "*");
     mvprintw(15,0, "*");
     mvprintw(15,75, "*");
   attroff(COLOR_PAIR(5));
}

void matrizmapa()  
{
    int i, y, x=0, l=0, total= 1;
    int temp =0;
 
    int inix=0,iniy =0;
    int finx=0,finy=0;

      for(x=0; x<5; x++)
      {
          for(y=0; y<10; y++)
          {
           inix = (x*10)+1;
           iniy = (y*10)+1;
 
           finx=inix+10;
           finy=iniy+10;

                if(matriz[x][y]== 0)
                {
                       for(i=inix; i<finx;i++)
                       {
                	   for(l=iniy;l<finy;l++)
                           {
       		               matrizmap[l][i]= 0; 
                               
                           }
                       }
                }
                else
                {
                       for(i=inix; i<finx;i++)
                       {
                	   for(l=iniy;l<finy;l++)
                           {
       		                matrizmap[l][i]= 1;   
                           }
                        }     
                }
          }
       }
}
void destino()
{   

    while((key != KEY_F( 2 ) ))
    {
     while((key != KEY_BACKSPACE))
     {
           WINDOW *my_win;
           my_win = create_newwin(52, 102, 0, 0);
           mvprintw(0 ,3 , "Seleccione una ruta presionando 'BORRAR' ");
           
           dibujo(dib_y,dib_x);
           key = getch();	   
	   // mvprintw(31,10, "D"); 
              if((key == KEY_RIGHT) && (matrizmap[dib_x+1][dib_y]== 1)){dib_x++;}
	      if((key == KEY_LEFT)  && (matrizmap[dib_x-1][dib_y]== 1)){dib_x--;}
              if((key == KEY_DOWN)  && (matrizmap[dib_x][dib_y+1]== 1)){dib_y++;}	   
              if((key == KEY_UP)    && (matrizmap[dib_x][dib_y-1]== 1)){dib_y--;}  
              if(key == KEY_BACKSPACE){dix=dib_x; diy=dib_y;}
              destroy_win(my_win);  
              opcion=0;  
              
     } 
     mover();
     atxt();
   }
 
 
}

WINDOW *win_menu(int height, int width, int starty, int startx)
{ 
   WINDOW *win_menu;
   win_menu = newwin(height, width, starty, startx);
   wrefresh(win_menu); 
   return win_menu;
}


void matrizatxt()
{
    int i, y, x=0, l=0, total= 1;
    int temp =0;
 
    int inix=0,iniy =0;
    int finx=0,finy=0;
 
  
      for(x=0; x<5; x++)
      {
          for(y=0; y<10; y++)
          {
           inix = (x*10)+1;
           iniy = (y*10)+1;
 
           finx=inix+10;
           finy=iniy+10;

                if(matriz[x][y]== 0)
                {
                       for(i=inix; i<finx;i++)
                       {
                	   for(l=iniy;l<finy;l++)
                           {
       		                 matriztxt[l][i]= '@'; 
                              
                           }
                       }
                }
                else
                {
                       for(i=inix; i<finx;i++)
                       {
                	   for(l=iniy;l<finy;l++)
                           {
                               matriztxt[l][i]= ' ';
                           }
                        }     
                }
               
          }
       }
  
}

void atxt()
{
   int cont=0, i=0, l=0;
   FILE *arc1;
   char a1;
   char salto= '\n';
    
   
     arc1= fopen("archivo.txt", "a");
       fputs(&salto,arc1);
      fprintf(arc1, "Usuario: %s", nombre);
      fputs(&salto,arc1);

 	for(i=0; i<52;i++)
        {
      	   for(l=0;l<102;l++)
           {
               
               fprintf(arc1, "%c", matriztxt[l-1][i-1] );
                
                if(cont==102)
                {                        
                    fputs(&salto,arc1);
                    cont=0;
                }
                cont++;
           }
        }
   

   fclose(arc1);
}

void menu()
{  
      while((key != KEY_F( 2 ) ))
      {
	       WINDOW *w;
	       w = newwin( 25, 12, 9,9); // create a new window
	       init_pair(3,COLOR_BLUE, COLOR_BLACK);
	       bkgd( COLOR_PAIR( 3 ) | A_BOLD );      
	       bordemenu();
		  
		   init_pair(2,COLOR_YELLOW, COLOR_BLACK);
		   mvprintw( 3, 15, " **   **     ***     *****     ***     ******  ");                    
		   mvprintw( 4, 15, " *** ***    ** **    **  *    ** **    **      ");
		   mvprintw( 5, 15, " ** * **   *******   *****   *******   ******  ");
		   mvprintw( 6, 15, " **   **  ***   ***  **     ***   ***      **  ");
		   mvprintw( 7, 15, " **   ** ****   **** **    ****   **** ******  ");

                  mvprintw( 11, 15, " Digite su Nombre: ");
                  //nombre= getchar();
                  attroff(COLOR_PAIR(3));
                  scanw("%s", &nombre);
                  
	          //mvprintw( 7, 15, "%c", nombre);
                  key = getch();	   
             destino();
      }
     destino();
} 




/*
void ruta(int dix, int diy)
{
  //dix diy
  int x=3;
  int y=26;
  while((x!=dix) && (y!=diy))
  {
	  if((x<dix)&&(x+1==0))
	  {
	      x++;
	  }
	  else if((x>dix)&&(x-1==0))
	      { 
		 x--;
	      }
	      else if((y<diy)&&(y+1==0))
		   {
		      y++;
		   }else if((y>diy)&&(y-1==0))
		         { 
		              y--;
		         }else if((x<dix)&&(y<diy)&&(x+1!=0)&&(y-1!=0))
		               {
		                      while(x+1 != 0)
		                      {
		                           x--;
		                      }
		               }
      mvprintw(x ,y , "R" );
  }
} */    


/*
           mvprintw( 3, 5, " **   **     ***     *****     ***     ******  ");                    
           mvprintw( 3, 5, " *** ***    ** **    **  *    ** **    **      ");
           mvprintw( 3, 5, " ** * **   *******   *****   *******   ******  ");
           mvprintw( 3, 5, " **   **  ***   ***  **     ***   ***      **  ");
           mvprintw( 3, 5, " **   ** ****   **** **    ****   **** ******  ");

*/


















