/*
Programa: biblioMovie3
Autor: David Botero  -  Sebastián Beltrán
Fecha: Marzo 23 de 2022
*/

//librerías necesarias
#include <iostream>
#include <cstdio>
#include <string.h>

//Constantes
#define MAXCH 50
#define CAST 5

using namespace std;

//Funciones de presentación
void menu(int menuType);
void head(string message);
void starter();
void encuadrehead(int ancho);
void encuadrefoot(int ancho);
void msgNoMovie();
void msgErrorSel();

//Funciones de proceso
int moviesStatus(FILE *File);
void menu(int menuType);
void insertData(FILE *File);
void findMovie(FILE *File);
void listMovies(FILE *File);
void modifyMovie(FILE *File);
void deleteMovie(FILE *File);

//Estructura
struct Movie{
  char movieName[MAXCH];
  char movieDirector[MAXCH];
  char release[MAXCH];
  char category[MAXCH];
  char cast[CAST][MAXCH];
};

//Apuntador del fichero (base de datos)
FILE *datosPeliculas; 

int main(){
	int Instruction = 1;
	//Constructor de inicio
	string messageHead="Bienvenido";
	starter();
	
	//Proceso principál
	while(Instruction != 0){
		//Constructor de menú general
		head(messageHead);
		menu(1);
		printf("\n\nSelecciona una opci%cn: ",162);
		scanf("%d", &Instruction);
		//Validador de la selección
		while(Instruction < 0 || Instruction > 5){
			msgErrorSel();
			scanf("%d", &Instruction);
		}
		cin.ignore();
		//Direcciónamiento dependiendo de selección
		switch(Instruction){
			case 1:
				messageHead="Nuevo titulo";
            	head(messageHead);
				insertData(datosPeliculas);
            	break;
			case 2:
				messageHead="Eliminar titulo";
            	head(messageHead);
            	deleteMovie(datosPeliculas);
            	break;
			case 3:
				messageHead="Busqueda de titulo";
            	head(messageHead);
				findMovie(datosPeliculas);
				break;
			case 4:
				messageHead="Consulta general";
            	head(messageHead);
				listMovies(datosPeliculas);
				break;
			case 5:
				messageHead="Modificar datos";
            	head(messageHead);
            	modifyMovie(datosPeliculas);
				break;
			case 0:
				//Salida
				system("Color 0F");
				messageHead="Se ha cerrado satisfactoriamente";
            	head(messageHead);
				printf("\n\t%cGracias por usar nuestros servicios!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",173);
				break;
			default:
				printf("\nERROR: Opci%cn no valida.", 162);
				break;
		}
		
		if (Instruction != 0){		
			//Mensaje default para regresar a inicio
			printf("\n\n\tPresiona cualquier tecla para volver al menu de inicio...");
        	messageHead="Inicio";
        	getchar();
		}
    }
	return 0;
}

void head(string message){
	int i;
	//se limpia pantalla
	system("cls");
	//se imprime head general
	cout << "\nBiblioMovie v1.3 - " << message << endl << endl;
	for(i=0;i<100;i++){
    	printf("%c",196);
	}
	cout << endl<< endl;
}

void starter(){
	//ventana de inicio
	cout << "\n\n\n\n\n\t\t\t\t\tBiblioMovie v1.3\n\n";
	cout << "\t\t\t=================================================\n\n\n";
	cout << "\t\t\t\t\t©2022 TECSYSTEMS\n\n\t\t\t\t  TODOS LOS DERECHOS RESERVADOS\n\n\n";
	cout << "\t\t\t       BOTERO, David. - BELTRAN, Sebastian.\n";
	cout << "\t   dsboteron@correo.udistrital.edu.co - scbeltranl@correo.udistrital.edu.co\n\n\n\n\n\n\n\n";
	system("PAUSE");
}

void menu(int menuType){
	switch(menuType){
		case 1:
      		system("Color 70");
      		//menú general
      		printf("Sistema de gesti%cn de pel%cculas, a continuaci%cn puedes ver las opciones disponibles: \n",162,161,162);
        	printf("\n\t[1] - Ingresar pel%ccula.\n\t[2] - Eliminar pel%ccula.\n\t[3] - Buscar pel%ccula.\n\t[4] - Enlistar pel%cculas.\n\t[5] - Editar pel%ccula.\n\t[0] - Salir",161,161,161,161,161);
        	break;
      	case 2:
	      	//menú de edición
	        printf("\n\t[1] - Todos los campos.\n\t[2] - Nombre pel%ccula.\n\t[3] - Director pel%ccula.\n\t[4] - Fecha lanzamiento.\n\t[5] - G%cnero.\n\t[6] - Elenco.\n\t[0] - Volver al men%c de inicio",161,161,130,163);
	        break;
    	case 3:
    		//menú de confirmación
			printf("\n\t[1] - Confirmar.\n\t[2] - Volver al men%c de inicio.\n",163);
    		break;
    	default:
    		printf("Se ha generado un error");
    		break;
    } 
}

void encuadrehead(int ancho){
	int i;
	printf("\n%c",201);
	for(i=0;i<ancho;i++){
    	printf("%c",205);
	}
	printf("%c\n",187);
}

void encuadrefoot(int ancho){
	int i;
	printf("\n%c",200);
    for(i=0;i<ancho;i++){
    	printf("%c",205);
	}
	printf("%c\n",188);
}

void msgNoMovie(){
	printf("\nNo hay ning%cna pel%ccula registrada, por favor a%cade una primero.", 163,161,164);
}

void msgErrorSel(){
	printf("Opci%cn no valida, por favor ingrese una opci%cn existente en el men%c: ",162,162,163);
}

int moviesStatus(FILE *File){
	int status = 0;
	Movie molde;
	File=fopen("peliculas", "rb");
	status=fread(&molde, sizeof(molde), 1, File);
	fclose(File);
	return status;
}

void insertData(FILE *File){
	File = fopen("peliculas", "ab+");
	int i;
	Movie molde;
	
	if(!File){
		msgNoMovie();
		return;
	}
		
	printf("Ingresa el nombre de la pel%ccula: ", 161);
	cin.getline(molde.movieName, MAXCH);
	printf("Ingresa el nombre del/la director/a: ");
	cin.getline(molde.movieDirector, MAXCH);
	printf("Ingresa la fecha del estreno de la pel%ccula: ",161);
	cin.getline(molde.release, MAXCH);
	printf("Ingresa el g%cnero de la pel%ccula: ", 130, 161);
	cin.getline(molde.category, MAXCH);
	printf("Ingresa a continuaci%cn el elenco de la pel%ccula: \n", 162, 161);
	for(i=0; i<CAST; i++){
		printf("\t- ");
		cin.getline(molde.cast[i], MAXCH);
	}
	
	fwrite(&molde, sizeof(struct Movie), 1, File);
	printf("\nPel%ccula registrada con %cxito\n",161,130);
	fclose(File);
	return;
}

void findMovie(FILE *File){
	char filmName[MAXCH];
	Movie molde; //Almacenamiento de variables en busqueda
	int nMovies, i;
	File = fopen("peliculas", "rb");
	//Verificación de existencia de fichero y bucle de busqueda
	if(!File || moviesStatus(File)==0){
	    msgNoMovie();
  	}else{
		printf("Por favor ingresa el titulo de la pel%ccula: ", 161);
        cin.getline(filmName, MAXCH); //Stdin del nómbre de la película
        while ((nMovies=fread(&molde, sizeof(molde), 1, File))!=0 && stricmp(molde.movieName,filmName)!=0);
        if (nMovies==0){
			printf("\nNo hay ning%cna pel%ccula registrada con el nombre [%s].", 163, 161, filmName);
			return;
    	}else{
			encuadrehead(60);
			printf(" T%ctulo: %s \n Director: %s \n Estreno: %s \n G%cnero: %s \n Elenco:",161,molde.movieName,molde.movieDirector,molde.release, 130,molde.category);
			for(i=0; i<CAST; i++){
        		printf("\n\t- %s", molde.cast[i]);
			}
			encuadrefoot(60);
    	}
	}
	fclose(File);
}

void deleteMovie(FILE *File){
	FILE *faux;
	File = fopen("peliculas", "rb+");
	Movie molde;
	int change, i, exist;
	char filmName[MAXCH];
	if(!File || moviesStatus(File)==0){
		msgNoMovie();
    	fclose(File);
		return;
	}
	else
	{
		printf("Por favor ingresa el titulo de la pel%ccula: ", 161);
	    cin.getline(filmName, MAXCH); 
	    
	    //Lectura fichero, verificación de existencia registro y almacenamiento de datos en molde
	    while((exist = fread(&molde, sizeof(molde), 1, File))!=0 && stricmp(molde.movieName,filmName)!=0);
	    
	    //Condicionál bajo existencia
	    if(exist==0){
			printf("\nNo hay ning%cna pel%ccula registrada con el nombre [%s]", 163, 161, filmName);
			fclose(File);
			return;
		}
		else
		{
	    	encuadrehead(60);
			printf("\t PEL%cCULA A ELIMINAR\n", 214);
			printf(" Nombre: %s \n Director: %s \n Estreno: %s \n G%cnero: %s \n Elenco:",molde.movieName,molde.movieDirector,molde.release, 130,molde.category);
			for(i=0; i<CAST; i++){
				printf("\n\t- %s", molde.cast[i]);
			}
			encuadrefoot(60);
			printf("\nLa eliminaci%cn ser%c permanente, %cestas seguro de continuar?\n",162,160,168);
			menu(3);
			printf("\n\nOpci%cn: ",162);
			scanf("%d", &change);
			//Menu choice validator: Type and options
			while(change != 1 && change != 2){
				msgErrorSel();
				scanf("%d", &change);
			}
			cin.ignore();
			if(change==1)
			{
				faux=fopen("temporal.$$$","wb");  //Apertura y creación archivo temporál
				if(!(faux))
				{
			    	printf("\n Error al borrar \n");
			    	fclose(faux);
					fclose(File);
				}
				else
				{
			    	while((fread(&molde, sizeof(molde), 1, File))!=0)
					{
			    		if(stricmp(molde.movieName,filmName)!=0)
						{
			        		fwrite(&molde, sizeof(molde), 1, faux);
						}
					}
					fclose(faux);
					fclose(File);
					remove("peliculas");	//Eliminación archivo antíguo
			        rename("temporal.$$$", "peliculas");
					printf("\n Pelicula borrada exitosamente!\n");
				}	
			}
			else
			{
				fclose(File);
			}
		}
	}
}

void listMovies(FILE *File){
	int index=1, i;
	Movie molde;
	File = fopen("peliculas","rb");
	if(!File || moviesStatus(File)==0){
    	msgNoMovie();
    	fclose(File);
		return;
  	}else{
    	while((fread(&molde, sizeof(molde), 1, File))!=0){
			encuadrehead(60);
			printf("\n\t\t PEL%cCULA %d",214,index);
      		printf("\n Nombre: %s \n Director: %s \n Estreno: %s \n G%cnero: %s \n Elenco:",molde.movieName,molde.movieDirector,molde.release, 130,molde.category);
			for(i=0; i<CAST; i++){
				printf("\n\t- %s", molde.cast[i]);
			}
			encuadrefoot(60);
			index++;
		}
	}
  	fclose(File);
}

void modifyMovie(FILE *File){
	Movie molde;
	int nPeliculas, flag, change, i;
	char filmName[MAXCH];

	File = fopen("peliculas", "rb+");
	if(!File || moviesStatus(File)==0){
		msgNoMovie();
		fclose(File);
	}else{
		//Nombre película buscada
		printf("Por favor ingresa el nombre de la pel%ccula a cambiar: ", 161);
		cin.getline(filmName, MAXCH); //Stdin del nómbre de la película
		while((nPeliculas = fread(&molde, sizeof(molde), 1, File))!=0 && stricmp(molde.movieName,filmName)!=0);
		if(nPeliculas==0){
			printf("\nNo hay ning%cna pel%cicula registrada con el nombre [%s]", 163, 161, filmName);
		}else{
			encuadrehead(60);
			printf("\t PEL%cCULA A CAMBIAR\n", 214);
			printf(" Nombre: %s \n Director: %s \n Estreno: %s \n G%cnero: %s \n Elenco:",molde.movieName,molde.movieDirector,molde.release, 130,molde.category);
			for(i=0; i<CAST; i++){
				printf("\n\t- %s", molde.cast[i]);
			}
			encuadrefoot(60);
			printf("\nPor favor seleccione el campo a cambiar: \n");
			menu(2);
			printf("\n\nOpci%cn: ",162);
			scanf("%d", &change);
			
			//Menu choice validator: Type and options
			while(change < 0 || change > 6){
				msgErrorSel();
				scanf("%d", &change);
			}
			
			//Menu switch case
			cin.ignore();
			switch(change){
				case 1:
					//Cambio nombre de la película
					printf("Ingresa el nombre de la pel%ccula: ", 161);
					cin.getline(molde.movieName, MAXCH);
					//Cambio nombre director
					printf("Ingresa el nombre del/la director/a: ");
					cin.getline(molde.movieDirector, MAXCH);
					//Cambio fecha de estreno
					printf("Ingresa la fecha del estreno de la pel%ccula: ", 161);
					cin.getline(molde.release, MAXCH);
					//Cambio elenco
					printf("Ingresa a continuaci%cn el elenco de la pel%ccula: ",162,161);
					for(i=0; i<CAST; i++){
				    	printf("\n\t- ");
				    	cin.getline(molde.cast[i], MAXCH);
				  	}
					break;
				case 2:
					//Cambio nombre de la película
					printf("\nIngresa el nombre de la pel%ccula: ", 161);
					cin.getline(molde.movieName, MAXCH);
					break;
				case 3:
					//Cambio nombre director
					printf("\nIngresa el nombre del/la director/a: ");
					cin.getline(molde.movieDirector, MAXCH);
					break;
				case 4:
					//Cambio fecha de estreno
					printf("\nIngresa la fecha del estreno de la pel%ccula: ", 161);
					cin.getline(molde.release, MAXCH);
					break;
				case 5:
					//CAMBIAR GENERO DE LA PELÍCULA
					printf("\nIngresa el g%cnero de la pel%ccula: ",130,161);
					cin.getline(molde.category, MAXCH);
					break;
				case 6:
					//Cambio elenco
					printf("\nIngresa a continuaci%cn el elenco de la pel%ccula: ",162,161);
					for(i=0; i<CAST; i++){
				    	printf("\n\t- ");
				    	cin.getline(molde.cast[i], MAXCH);
				  	}
					break;
				case 0:
					fclose(File);
					return;
				default:
					printf("\nERROR: Opci%cn no valida.", 162);
					break;
			}
			
			head("Modificar datos");
			encuadrehead(60);
			printf("\t PEL%cCULA NUEVOS CAMBIOS \n", 214);
      		printf(" Nombre: %s \n Director: %s \n Estreno: %s \n G%cnero: %s \n Elenco:",molde.movieName,molde.movieDirector,molde.release, 130,molde.category);			
			for(i=0; i<CAST; i++){
				printf("\n\t- %s", molde.cast[i]);
			}
			encuadrefoot(60);
			
			//Confirmación cambios o volver a menú principal
			printf("\n%cEst%cs seguro que deseas realizar los cambios, estos ser%cn permanentes?\n",168,160,160);
			menu(3);
			printf("\n\nOpci%cn: ",162);
			scanf("%d", &flag);
			
			//Menu choice validator: options
			while(flag !=1 && flag !=2){
				msgErrorSel();
				scanf("%d", &flag);
			}
			cin.ignore();
			if(flag == 1){
				//Busqueda registro y cambio
				printf("%cCambios realizados con %cxito!",173,130);
				fseek(File,-1*sizeof(molde), SEEK_CUR); 
				fwrite(&molde, sizeof(molde), 1, File);
				fclose(File);
			}else{
				fclose(File);
				return;
			}
		}
	}
	//Cierre
	fclose(File);
}
