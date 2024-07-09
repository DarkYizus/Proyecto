#include <iostream>
#include <string>
#include <cstdlib>
#include "FunctionsM.h"
#include <fstream>
#include <iomanip>

using namespace std;
int Session = 0;
int idRefUser = 0;
Cancion *MusicPrincipal = NULL;
usuarios *SpotyUser = NULL;
historial *ActiveHist = NULL;
usuarios *logUser = NULL; 
int IdUs3r=200000;
int IDSong=100000;

void inicioSession(usuarios *userList,int &UserRID,usuarios **logU){
    int b = 0;
    string pass;
    cout << (" ingrese su id de usuario: ");
    cin >> b;
    if(b>=100000 && b<200000){
        if(UserSearch(b,userList) == 1){

            cout << ("ingrese Clave para poder continuar");
            cin >> pass;

            if(contraUser(pass,userList) == 1){
                usuarios p = UserID(b,userList);
                *logU =  &p;
                UserRID = logUser->id;
                Session=1;
             cout << " Se ha iniciado sesion exitosamente "<< endl;   
            }else{
                cout << "  Clave invalida  " << endl;
            }

        }else{
        cout << (" error, id no encontrado");
        }

    }else{
        cout << "numero invalido " << endl;
    }
    


}

void mostarMenu(){
   
    cout << " realizado por los alumnos: " << endl;
    cout << " Jesus Antonio Suarez " << endl;
    cout << " Christian Vilera " << endl;
    cout << " Luis Delgado " << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
    cout << " \n";

cout << "MENU Ucabify" << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
    cout << ("1- Canciones ");
    cout << ("2- Usuarios ");
    cout << ("3- Reproducir cancion ");
    cout << ("4- Historial de Reproduccion ");
    cout << ("5- Salir del sistema ");
}

void ReprodSubMenu(int &sesi){
    int A; 
    if(sesi){
        cout << (" elige una cancion para reproducir [presiona enter] ");
        cin;
        system("cls");
        ShowSongs(MusicPrincipal);
        cout << "elige una cancion para reproducir ingrese id: " << endl;
        cin >> A;
        if(SearchSong(A,MusicPrincipal)){
            AuxUsers = UserID(idRefUser,SpotyUser
        );
            usuarios *p1;
            Cancion *p2;
            IdtUser(&p1,b,SpotyUser);
            IdtSong(&p2,A,MusicPrincipal);
            MusicReprod(&ActiveHist
        ,p1,p2);
        } 
    }else{
        inicioSession(SpotyUser
    ,idRefUser,&logUser);
        cout << (" elija una cancion para reproducir [presiona enter] ");
        cin;
        system("cls");
        ShowSongs(MusicPrincipal);
        cout << "elija una cancion para reproducir, ingrese id: " << endl;
        cin >> A;
        if(SearchSong(A,MusicPrincipal)){
            AuxUsers = UserID(idRefUser,SpotyUser
        );
            usuarios *p1 = &aux;
            Cancion aux1 = canID(A,MusicPrincipal);
            Cancion *p2 = &aux1;
            MusicReprod(&ActiveHist
        ,p1,p2);
        } 
    }
    

}

void SongSubMenu(){
    int SongOptions;
    do{
        cout << ("Canciones");
        cout << ("1. Agregar Canciones");
        cout << ("2. Eliminar Canciones");
        cout << ("3. Reproducir cancion");
        cout << ("4. Mostrar las canciones");
        cout << ("5. Volver al menu anterior");
        cout << ("Ingrese una opcion: ");
        cin >> SongOptions;
        cin.ignore();
        switch (SongOptions){
            case 1:
                system("cls");
                AddSong(&MusicPrincipal,IDSong);
                break;
            case 2:
                system("cls");
                if(MusicPrincipal == nullptr){
                    cout << "La lista de canciones esta vacia \n";
                }
                else{
                    int IdDelete;
                    cout << "Ingrese el ID de la cancion que desea eliminar: ";
                    cin >> IdDelete;
                    cin.ignore();
                    DeleteSong(IdDelete,&MusicPrincipal,&ActiveHist
                );
                }
                break;
            case 3:
                ReprodSubMenu(Session);
                break;
            case 4: 
                system("cls");
                ShowSongs(MusicPrincipal);
                break;
            case 5:
                system("cls");
                cout << "Volviendo al menu Principal...\n";
                break;
            default:
                cout << " Opcion no valida, intente de nuevo...\n";
        }
    }while(SongOptions !=5);
}

void UserSubMenu(){
    int UserOptions;
    do{
        cout << ("Usuarios");
        cout << ("1. Agregar Usuarios");
        cout << ("2. Eliminar Usuarios");
        cout << ("3. Mostrar usuarios";
        cout << ("4. iniciar Sesion");
        cout << ("5. Volver al menu anterior");
        cout << ("Ingrese una opcion: ");
        cin >> UserOptions;
        switch (UserOptions){
            case 1:
                system("cls");
                AddUser(&SpotyUser
            ,IdUs3r);
                break;
            case 2:
                system("cls");
                int N;
                cout( << "Ingresa id para poder eliminar al usuario");
                cout << ("1. Ingresar id");
                cout << ("2. Salir");
                cin >>  N;
                if(N==1){
                    int ides;
                    cout << "Ingrese id: ";
                    cin >> ides;
                    UserDelete(&SpotyUser
                ,ides,&ActiveHist
            );
                }
                break;
            case 3:
                system("cls");
                ShowUsers(SpotyUser
            );
                break;
            case 4:
                system("cls");
                inicioSession(SpotyUser
            ,idRefUser,&logUser);
            );
                break;
            case 5:
                system("cls");
                cout << "Volviendo al menu Principal...\n";
                break;
            default:
                cout << " Opcion no valida, intente de nuevo...\n";
        }
    }while(UserOptions != 5);
}

void HistSubMenu(){
    int op= 0;   
    do{
        cout << ("historial");
        cout << ("1. mostrar historial");
        cout << ("1. mostrar historial propio");
        cout << ("2. Volver al menu anterior");
        cin >> op;
        switch (op)
        {
        case 1:
            ShowHist(ActiveHist
        ); 
            break;
        case 2:
        cout << " volviendo "<< endl;
        break;
        default:
            break;
        }
        }while(op !=2);
}

void LoadMusic(int &idCans){
    string linea;
    ifstream archmusic("SongList.txt");
    if (!archmusic.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    while (getline(archmusic, linea)) {
        size_t pos_coma1 = linea.find(';');
        size_t pos_coma2 = linea.find(';', pos_coma1 + 1);
        size_t pos_coma3 = linea.find(';', pos_coma2 + 1);
        size_t pos_coma4 = linea.find(';', pos_coma3 + 1);
        int id = stoi(linea.substr(0, pos_coma1));
        string SongsName = linea.substr(pos_coma1 + 1, pos_coma2 - pos_coma1 - 1);
        string ArtistsName = linea.substr(pos_coma2 + 1, pos_coma3 - pos_coma2 - 1);
        string genero = linea.substr(pos_coma3 + 1, pos_coma4 - pos_coma3 - 1);
        int anioSalida = stoi(linea.substr(pos_coma4 + 1));
        aggcanTxt(&MusicPrincipal,idCans, id, SongsName, ArtistsName, genero, anioSalida);
    }

    archmusic.close();
}


void LoadUsers(int &IdUsers){
    string linea;
    ifstream archUser("userlist.txt");

 = NULL;
    if (!archUser.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    while (getline(archUser, linea)) {
        size_t pos_coma1 = linea.find(';');
        size_t pos_coma2 = linea.find(';', pos_coma1 + 1);
        size_t pos_coma3 = linea.find(';', pos_coma2 + 1);
        size_t pos_coma4 = linea.find(';', pos_coma3 + 1);
        size_t pos_coma5 = linea.find(';', pos_coma4 + 1);
        int id = stoi(linea.substr(0, pos_coma1));
        string nombre = linea.substr(pos_coma1 + 1, pos_coma2 - pos_coma1 - 1);
        string correo = linea.substr(pos_coma2 + 1, pos_coma3 - pos_coma2 - 1);
        int edad = stoi(linea.substr(pos_coma3 + 1, pos_coma4 - pos_coma3 - 1));
        string Clave = linea.substr(pos_coma4 + 1, pos_coma5 - pos_coma4 - 1);
        string pais = linea.substr(pos_coma5 + 1);
        AddUserTxt(&SpotyUser
    ,IdUsers, id, edad, nombre, pais, Clave, correo);
    }
    archUser.close();
}



bool UserListVal(const string &filename) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << filename << endl;
        return false;
    }

    string linea;
    int lineNumber = 0;
    while (getline(archivo, linea)) {
        lineNumber++;
        stringstream ss(linea);
        string idStr, nombre, correo, edadStr, Clave, pais;

        if (!getline(ss, idStr, ';') || 
            !getline(ss, nombre, ';') || 
            !getline(ss, correo, ';') || 
            !getline(ss, edadStr, ';') || 
            !getline(ss, Clave, ';') || 
            !getline(ss, pais, ';')) {
            cout << "Error en el formato del archivo " << filename << " en la linea " << lineNumber << endl;
            return false;
        }

        try {
            int id = stoi(idStr);
            int edad = stoi(edadStr);
        } catch (exception &e) {
            cout << "Error en el formato del archivo " << filename << " en la linea " << lineNumber << ": " << e.what() << endl;
            return false;
        }
    }

    archivo.close();
    return true;
}

bool SongListVal(const string &filename) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << filename << endl;
        return false;
    }
    string linea;
    int lineNumber = 0;
    while (getline(archivo, linea)) {
        lineNumber++;
        stringstream ss(linea);
        string idStr, SongsName, ArtistsName, genero, LaunchYear;

        if (!getline(ss, idStr, ';') || 
            !getline(ss, SongsName, ';') || 
            !getline(ss, ArtistsName, ';') || 
            !getline(ss, genero, ';') || 
            !getline(ss, LaunchYear, ';')) {
            cout << "Error en el formato del archivo " << filename << " en la linea " << lineNumber << endl;
            return false;
        }

        try {
            int id = stoi(idStr);
            int anioSalida = stoi(LaunchYear);
        } catch (exception &e) {
            cout << "Error en el formato del archivo " << filename << " en la linea " << lineNumber << ": " << e.what() << endl;
            return false;
        }
    }

    archivo.close();
    return true;
}

bool ListStoryVal(const string &filename) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << filename << endl;
        return false;
    }

    string linea;
    int lineNumber = 0;
    while (getline(archivo, linea)) {
        lineNumber++;
        stringstream ss(linea);
        string idUsStr, idCanStr, NumRepStr, Likes;
        if (!getline(ss, idUsStr, '.') || 
            !getline(ss, idCanStr, ';') || 
            !getline(ss, NumRepStr, ';') ){
            cout << "Error en el formato del archivo " << filename << " en la linea " << lineNumber << endl;
            return false;
        }

        try {
            int idUs= stoi(idUsStr);
            int IdCan= stoi(idCanStr);
            int NumRep= stoi(NumRepStr);

        } catch (exception &e) {
            cout << "Error en el formato del archivo " << filename << " en la linea " << lineNumber << ": " << e.what() << endl;
            return false;
        }
    }
    archivo.close();
    return true;
}

int main(){

    if (!UserListVal("userlist.txt") || !SongListVal("SongList.txt")) {
        cout << "Corrija los archivos e intente nuevamente." << endl;
        return 1;
    }

   
    LoadMusic(IDSong);
    LoadUsers(IdUs3r);

    int opcion;
    do {
        
        mostarMenu();
        cout<< "\n Ingrese Una Opcion: ";
        cin>> opcion;
        switch (opcion){
            case 1:
                system("cls");

                SongSubMenu();
                break;
            case 2:
                system("cls");

                UserSubMenu();
                break;
            case 3:
                system("cls");
                ReprodSubMenu(Session);

                break;
            case 4:
                system("cls");
                HistSubMenu();

                break;
            case 5:

                cout << "Saliendo De UCABIFY... \n";
                break;
            default:
                cout << "Opcion No Valida, Intente de nuevo... \n";

        }
    }while(opcion!=5);


    return 0;
}
