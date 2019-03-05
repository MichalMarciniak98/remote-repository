#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#define SZEROKOSC_BOXA 50
#define WYSOKOSC_BOXA 10 

typedef struct Osoba
{
       char *imie;
       char *nazwisko;
       char *numer_telefonu;
       int wiek;
       char *plec;
       struct Osoba * nastepny;
}Osoba;
typedef struct Osoba * wskaznik_na_Osoba;

int dlugosc_listy(wskaznik_na_Osoba poczatek_listy)
{
    int dlugosc = 0;
    wskaznik_na_Osoba wsk = poczatek_listy;
    while(wsk != NULL)
		{
           dlugosc++;
           wsk = wsk -> nastepny;
        }
return dlugosc;
}
    
wskaznik_na_Osoba dodaj_osobe(wskaznik_na_Osoba poczatek_listy)
{    
    wskaznik_na_Osoba nowa = (wskaznik_na_Osoba)malloc(sizeof(Osoba));
    nowa->imie = (char*)malloc(sizeof(char));
    nowa->nazwisko = (char*)malloc(sizeof(char));
    nowa->numer_telefonu = (char*)malloc(sizeof(char));
    nowa->plec = (char*)malloc(sizeof(char));
    if(nowa == NULL)
    {
		printw("Blad alokacji pamieci");
		endwin();
		return 0;
	}
	attron(COLOR_PAIR(1));	
    attron(A_BOLD);
    mvprintw(0, 0, "%s", "Twoje dane przechowywane beda\nw pliku dane_osobowe\n\n");
    attroff(COLOR_PAIR(1));	
    attroff(A_BOLD);
	refresh();
	
    FILE *wp;    
	if((wp = fopen("dane_osobowe", "a+")) == NULL)
	{
		mvprintw(0, 0, "%s", "Blad otwarcia pliku\n");
		refresh();
		exit(EXIT_FAILURE);
	}
	
     attron(A_BOLD); printw("Podaj imie: "); attroff(A_BOLD);
	 scanw("%s", nowa->imie);
	 fprintf(wp, "%s ", nowa->imie);
	 clear();

     attron(A_BOLD); printw("Podaj nazwisko: "); attroff(A_BOLD);
     scanw("%s", nowa->nazwisko);
     fprintf(wp, "%s ", nowa->nazwisko);
     clear();

     podaj_nr:
     attron(A_BOLD); printw("Podaj numer telefonu: "); attroff(A_BOLD);
     scanw("%s", nowa->numer_telefonu);
     clear();
     if(strlen(nowa->numer_telefonu) != 9)
     {
         printw("numer telefonu musi miec 9 cyfr\n");
         goto podaj_nr;
     }
	 fprintf(wp, "%s ", nowa->numer_telefonu);
	 
	 podaj_wiek:
     attron(A_BOLD); printw("Podaj wiek: " ); attroff(A_BOLD);
     scanw("%d", &nowa->wiek);
     clear();
     if( nowa->wiek < 5 || nowa->wiek > 150)
     {
         printw("podano zly wiek\n");
         refresh();
         goto podaj_wiek;
     }
     fprintf(wp, "%d ", nowa->wiek);
     	
	 attron(A_BOLD); printw("Podaj plec: \nm-Mezczyzna\tk-Kobieta\n"); attroff(A_BOLD); 
     refresh();     
     scanw("%s", nowa->plec);
     clear();
     fprintf(wp, "%s \n", nowa->plec);
     
     nowa->nastepny = poczatek_listy;
     
return nowa;     
}

void wypisz_osobe_po_indeksie(wskaznik_na_Osoba poczatek_listy)
{	
	int ID, i;
    attron(A_BOLD); printw("Podaj indeks osoby: "); attroff(A_BOLD);
    refresh();
    scanw("%d", &ID);
    clear();

        if((ID > dlugosc_listy(poczatek_listy)) || (ID < 1))
            {
                attron(A_BOLD); printw("Nie ma takiego indeksu"); attroff(A_BOLD);
                refresh();
                napms(2000);
                endwin();
            }
            
		wskaznik_na_Osoba wsk = poczatek_listy; 	
        for(i = 1; i < ID; i++)
            {
              wsk = wsk->nastepny;
            }
			attron(COLOR_PAIR(3));	
            attron(A_BOLD);		
			attron(A_UNDERLINE);
			printw("%s %s %s %d %s\n", wsk->imie, wsk->nazwisko, wsk->numer_telefonu, wsk->wiek, wsk->plec);
			attroff(A_UNDERLINE);		
			attroff(A_BOLD);
			attroff(COLOR_PAIR(3));	
refresh();
}

void wypisz_cala_liste(wskaznik_na_Osoba poczatek_listy)
{
     wskaznik_na_Osoba wsk = poczatek_listy;		
     if(wsk == NULL)
     attron(COLOR_PAIR(2));			
	 attron(A_BOLD);
     mvprintw(0, 0, "%s", "LISTA JEST PUSTA!!!");
     attroff(COLOR_PAIR(2));			
	 attroff(A_BOLD);
     refresh();
	 clear();	
     if(dlugosc_listy(poczatek_listy) == 1)
            {
                attron(A_BOLD); printw("Lista zawiera %d element:\n\n", dlugosc_listy(poczatek_listy) ); attroff(A_BOLD);
                refresh();
            }
     else if(dlugosc_listy(poczatek_listy) == 2 || dlugosc_listy(poczatek_listy) == 3 || dlugosc_listy(poczatek_listy) == 4)
              {
                 attron(A_BOLD); printw("Lista zawiera %d elementy:\n\n", dlugosc_listy(poczatek_listy)); attroff(A_BOLD);
                 refresh();
              }
    while(wsk != NULL)
     {
            printw("%s %s %s %d %s\n", wsk->imie, wsk->nazwisko, wsk->numer_telefonu, wsk->wiek, wsk->plec);
            refresh();
            wsk = wsk->nastepny;
     }
clear();
}

wskaznik_na_Osoba usun_osobe_po_indeksie(wskaznik_na_Osoba poczatek_listy)
{
     int ID;
     attron(A_BOLD); printw("Podaj indeks osoby: "); attroff(A_BOLD);
     refresh();
     scanw("%d", &ID);
     clear();
	
     if((ID > dlugosc_listy(poczatek_listy)) || (ID < 1))
           {
           attron(A_BOLD); mvprintw(0, 0, "Nie ma takiego indeksu"); attroff(A_BOLD);
           refresh();
           }
			 wskaznik_na_Osoba poprzedni = NULL;
             wskaznik_na_Osoba biezacy = poczatek_listy;		
             int i;
       do
        {
             for(i = 1; i < ID; i++)
                    {
                        poprzedni = biezacy;
                        biezacy = biezacy->nastepny;
                    }
             if(biezacy==poczatek_listy) poczatek_listy = biezacy->nastepny;
             else poprzedni->nastepny = biezacy->nastepny;
             free(biezacy);
             return poczatek_listy;
         poprzedni = biezacy;
         biezacy = biezacy->nastepny;
		}
		while(biezacy != NULL);
		
return poczatek_listy;
}

wskaznik_na_Osoba edytuj_dane(wskaznik_na_Osoba poczatek_listy)
{
	int i, ID, wybor;
		FILE *wp;
		if((wp = fopen("dane_osobowe", "r")) == NULL)
		{
			fprintf(stderr, "Blad otwarcia pliku\n"); 
		}

		attron(COLOR_PAIR(3));			
		attron(A_BOLD);
		mvprintw(0, 0, "%s", "Podaj numer indeksu osoby ktorej\ndane chcesz edytowac:\n\n");
		attroff(COLOR_PAIR(3));			
		attroff(A_BOLD);
		refresh();
		
		scanw("%d", &ID);
		clear();
			       
        wskaznik_na_Osoba wsk = poczatek_listy, tymczasowy;		
			
             for(i = 1; i < ID; i++)
                    {
                        tymczasowy = wsk;
                        wsk = wsk->nastepny;
                    }

    attron(A_BOLD); mvprintw(0, 0, "%s", "Edytuj:\n\n1-Imie\n2-Nazwisko\n3-Numer telefonu\n4-Wiek\n5-Plec\n\n"); attroff(A_BOLD);
    refresh();
	scanw("%d", &wybor);
	clear();
			switch(wybor)
			  {
				attron(A_BOLD);
				case 1:
				mvprintw(0, 0, "%s", "Podaj nowe imie\n"); refresh();
				int dlugosc_imienia = strlen(wsk->imie); 
				for(i=0; i<dlugosc_imienia; i++) wsk->imie[i] = ' ';
				scanw("%s", wsk->imie); 
				fprintf(wp, "%s", wsk->imie); clear();
				break;
				
				case 2:
				mvprintw(0, 0, "%s", "Podaj nowe nazwisko\n"); refresh();
				int dlugosc_nazwiska = strlen(wsk->nazwisko); 
				for(i=0; i<dlugosc_nazwiska; i++) wsk->nazwisko[i] = ' ';
				scanw("%s", wsk->nazwisko); fprintf(wp, "%s", wsk->nazwisko); 
				clear();
				break;
				
				case 3:
				mvprintw(0, 0, "%s", "Podaj nowy numer telefonu\n"); refresh();
				int dlugosc_numeru = strlen(wsk->numer_telefonu);  
				for(i=0; i<dlugosc_numeru; i++) wsk->numer_telefonu[i] = ' ';
				scanw("%s", wsk->numer_telefonu); fprintf(wp, "%s", wsk->numer_telefonu);
				clear();
				break;
				
				case 4:
				mvprintw(0, 0, "%s", "Podaj nowy wiek\n"); refresh();
				scanw("%d", wsk->wiek); clear();
				break;
				
				case 5:
				mvprintw(0, 0, "%s", "Podaj nowa plec\n"); refresh();
				int dlugosc_plec = strlen(wsk->plec);   
				for(i=0; i<dlugosc_plec; i++) wsk->plec[i] = ' ';
				scanw("%s", wsk->plec); fprintf(wp, "%s", wsk->plec);
				clear();
				break;
				attroff(A_BOLD);
			  }
return wsk;
}

wskaznik_na_Osoba wyczysc_cala_liste(wskaznik_na_Osoba poczatek_listy)
{
         wskaznik_na_Osoba biezacy = poczatek_listy, tymczasowy;        
         while(biezacy != NULL)
         {				 		 
             tymczasowy = biezacy;
             biezacy = biezacy->nastepny;
             free(tymczasowy);
		 } 
return biezacy;   
}

char *wybor_opcji[] = { 
			"Wyjscie z programu", 
			"Dodaj nowa osobe", 
			"Usun osobe o podanym indeksie", 
			"Wyswietl osobe o podanym indeksie", 
			"Wyswietl cala liste",
			"Wyczysc cala liste",
			"Edytuj dane osobowe", "Sortuj"
		  }; 
int poczatkowe_x = 0;
int poczatkowe_y = 0;
		  
int liczba_opcji = sizeof(wybor_opcji) / sizeof(char *);
int wyswietl_menu(WINDOW *menu_win, int wskazanie_na_opcje);

void wyswietl_dane(wskaznik_na_Osoba poczatek_listy, int);
int sortuj_wiek (const void *, const void *);
int sortuj_nazwisko (const void *, const void *);

int main()
{	
	wskaznik_na_Osoba poczatek_listy = NULL;
	int d = dlugosc_listy(poczatek_listy);
	wskaznik_na_Osoba tablica_osob[d];
	WINDOW *menu_win;
	int wskazanie_na_opcje = 1;
	int wybor = 0;
	int c;		  
 
    initscr();    
    cbreak();
    curs_set(0);	
	poczatkowe_x = 1;
	poczatkowe_y = 0;
	
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	
	menu_win = newwin(WYSOKOSC_BOXA, SZEROKOSC_BOXA, poczatkowe_y, poczatkowe_x*40);
	keypad(menu_win, TRUE);	
        			
	while(1)
	{
		wyswietl_menu(menu_win, wskazanie_na_opcje);
		c = wgetch(menu_win);
		switch(c)
			{	
			case KEY_UP:
				if(wskazanie_na_opcje == 1)
					wskazanie_na_opcje = liczba_opcji;
				else
					--wskazanie_na_opcje;
				break;
			case KEY_DOWN:
				if(wskazanie_na_opcje == liczba_opcji)		//zapętlanie wybierania opcji
					wskazanie_na_opcje = 1;
				else 
					++wskazanie_na_opcje;
				break;
			case '\n':			
				wybor = wyswietl_menu(menu_win, wskazanie_na_opcje);	
						
				switch(wybor-1)
				{	
					case 0:
					system("clear");
					endwin();
					return 0;
					break;
					
					case 1:
					poczatek_listy = dodaj_osobe(poczatek_listy);
					break;
					
					case 2:
					poczatek_listy = usun_osobe_po_indeksie(poczatek_listy);
					clear();
					break;
					
					case 3:
					wypisz_osobe_po_indeksie(poczatek_listy);
					clear();
					break;
					
					case 4:
					wypisz_cala_liste(poczatek_listy);
					break;
					
					case 5:
					poczatek_listy = wyczysc_cala_liste(poczatek_listy);
					break;
					
					case 6:
					poczatek_listy = edytuj_dane(poczatek_listy);
					break;
					
					case 7:
					qsort(tablica_osob,d, sizeof(Osoba),sortuj_wiek);
					wyswietl_dane(*tablica_osob, d);
					qsort(tablica_osob, d, sizeof(Osoba),sortuj_nazwisko);
					wyswietl_dane(*tablica_osob, d);
					break;
				}			
				break;
				
			default:
				break;
			}		
	}	
	endwin();
return 0;
}

void wyswietl_dane(wskaznik_na_Osoba tab, int m)
{
int i;
	for (i=0;i<m;i++)
		{
			mvprintw(0, 0, "Osoba nr %2d\t wiek:%2d\t nazwisko:%s\n",i+1,tab[i].wiek,tab[i].nazwisko);
		}
}

int sortuj_wiek(const void * a, const void * b)
{
    const Osoba* el1=a;
    const Osoba* el2=b;
    if (el1->wiek < el2->wiek)
        return -1;
    else if (el1->wiek == el2->wiek)
        return 0;
    else
        return 1;
}

int sortuj_nazwisko(const void * a, const void * b)
{
    const Osoba* el1=a;
    const Osoba* el2=b;
    return strcmp(el1->nazwisko, el2->nazwisko);
return 0;
}

int wyswietl_menu(WINDOW *menu_win, int wskazanie_na_opcje)
{	
	int x, y, i;	
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < liczba_opcji; ++i)
	{	if(wskazanie_na_opcje == i + 1)
		{	
			wattron(menu_win, COLOR_PAIR(1));			
			wattron(menu_win, A_BOLD);	
			mvwprintw(menu_win, y-1, x, "%s", wybor_opcji[i]);
			wattroff(menu_win, A_BOLD);
			wattroff(menu_win, COLOR_PAIR(1));
		}
		else
			mvwprintw(menu_win, y-1, x, "%s", wybor_opcji[i]);
			++y;
	}
	wrefresh(menu_win);
return wskazanie_na_opcje;
}

