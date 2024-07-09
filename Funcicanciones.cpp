#include <iostream>
#include <string>
#include <cstdlib>
#include "outdl.h"
#include <fstream>
#include <iomanip>
using namespace std;

struct Users{
    int id;
    string Name;
    string Email;
    int Age;
    string Clave;
    string Country;
   struct Users * siguiente;
};
struct Songs{
    int id; 
    string NameCancion;
    string ArtistsName;
    string genero;
    int LaunchYear; 
    Songs* siguiente;
};

struct repro{
    Songs* IdSongR;
    int cRepro;
    int Likes;
    struct repro* siguiente;
};

struct historial{
    Users* IdUser;
    repro *listRepro;
    struct historial* siguiente;
};


void aggUsuario(Users** P, int& UserID) {
    Users* Newser = new Users;
    cout << "Ingrese Nombre del usuario: ";
    cin >> Newser->Name;

    cout << "Ingrese el Email del usuario: ";
    cin >> Newser->Email;

    cout << "Ingrese edad del usuario: ";
    cin >> Newser->Age;

    cout << "Ingrese pais de origen del usuario: ";
    cin >> Newser->Country;

    cout << "Ingrese Clavesenia del usuario: ";
    cin >> Newser->Clave;

    Newser->id = ++UserID;
    Newser->siguiente = *P;
    *P = Newser;

    ofstream archivo("userlist.txt", ios::app);
    if (archivo.is_open()) {
        archivo << Newser->id << ";"
                << Newser->Name << ";"
                << Newser->Email << ";"
                << Newser->Age << ";"
                << Newser->Clave << ";"
                << Newser->Country << "\n";
        archivo.close();
        cout << "Datos escritos correctamente." << endl;
    }else{
        cout << "No se pudo abrir el archivo." << endl;
    }
}




void AddUserTxt(Users **p, int &idU, int IdUser, int Age, string Name, string Country, string Clave, string Email){
    Users *NewUser = new Users;
    
    if(IdUser > idU){
        idU = IdUser; 
    }
    
    NewUser->id = IdUser; 
    NewUser->Name = Name;
    NewUser->Age = Age;
    NewUser->Email = Email;
    NewUser->Clave = Clave;
    NewUser->Country = Country;
    NewUser->siguiente = *p;
    *p = NewUser;
}


void aggHistorialTxt(historial **p, int UserID, int &IDSong, int NumRep, string Likes) {
    historial *nuevoHistorial = new historial;

    if (Likes == "VERDADERO") {
        nuevoHistorial->listRepro->Likes = 1;
    } else {
        nuevoHistorial->listRepro->Likes = 0;
    }

    nuevoHistorial->IdUser->id = UserID; 
    nuevoHistorial->listRepro->IdSongR->id = IDSong;
    nuevoHistorial->listRepro->cRepro = NumRep;
    nuevoHistorial->siguiente = *p;
    *p = nuevoHistorial;
}



void UserDelete(historial** historialP,Users *Userhisto){
    historial *p = *historialP;
    int a = 1;
    
    if(p->IdUser->id == Userhisto->id){
        historial *aux1 = p;
        p = p->siguiente;
        aux1->IdUser = NULL;
        a = 0;
        delete aux1;
    }

    while ( p !=NULL || a==1 ){
        if(p->siguiente->IdUser->id == Userhisto->id ){
            a == 0;
        }
        p = p -> siguiente;
    }

    if (a==0){
        historial *aux = p->siguiente;
        p->siguiente = p->siguiente->siguiente;

        aux->IdUser = NULL;
        delete aux;
    }
    
}


void SongDeleteH(historial** historialP,Songs *SongHist){
    historial *p = *historialP;
    historial *aux;
    repro *c,*aux1;

    while(p!=NULL){
        c = p->listRepro;

        while(c != NULL ){

            if( c->IdSongR->id == SongHist->id ){
                aux1 = c;
                c = c->siguiente;
                aux1->IdSongR = NULL;
                delete aux1;
            }

            if(c->siguiente->IdSongR->id == SongHist->id ){
                aux1 = c->siguiente;
                c->siguiente = c->siguiente->siguiente;
                aux1->IdSongR = NULL;
                delete aux1;
            }
            c = c->siguiente;
        }
        p = p->siguiente;
    }
    
}


void eliminarUsuario(Users** cabeza, int ids,historial **historialAc = NULL) {
    Users* p = *cabeza, * prev = NULL;
    bool encontrado = false;
    if (p == NULL) {
        cout << "La lista de Users está vacía." << endl;
        return;
    }
    while (p != NULL) {
        if (p->id == ids) {
            encontrado = true;
            if (prev == NULL) {
                *cabeza = p->siguiente;
            } else {
                prev->siguiente = p->siguiente;
            }

            delete p;
            break;
        }
        prev = p;
        p = p->siguiente;
    }

    if (!encontrado) {
        cout<< "Usuario no encontrado." << endl;
        return;
    } else {
        cout<< "Usuario eliminado de la lista." << endl;
    }

    ifstream archivoEntrada("userlist.txt");
    ofstream archivoSalida("userlistTemp.txt");
    if(archivoEntrada.is_open() && archivoSalida.is_open()) {
        string linea;
        while (getline(archivoEntrada, linea)) {
            stringstream ss(linea);
            string idStr;
            getline(ss, idStr, ';');
            if (stoi(idStr) != ids) {
                archivoSalida << linea << "\n";  
            }
        }
        archivoEntrada.close();
        archivoSalida.close();

        remove("userlist.txt");
        rename("userlistTemp.txt", "userlist.txt");

        cout << "Usuario eliminado correctamente del archivo." << endl;
    } else {
        cout << "No se pudo abrir el archivo para actualizar." << endl;
    }
}

void ShowUsers(Users *p){
    Users * principal = p;
    if(principal){
        printC("lista de Users");
        cout << "|  ID   |" << setw(18) << "Usuario     |"  << setw(30) << "Email         " << "|" << setw(2) << " Age " << "|" << setw(18) << "Clave     " << "|" <<  setw(10) << "Country   " << " |" << endl;
        while (principal){
            cout << "|" << setw(6) << principal->id << " | " << setw(15) << principal->Name << " | " << setw(28) << principal->Email;
        cout << " | " << setw(4) << principal->Age << " | " << setw(16) << "**************" << " |" <<setw(10) << principal->Country <<" |"<< endl;
            principal = principal->siguiente;
        }
    }else{
        cout<< "No hay Usuarios disponibles \n";
    }
}


void AddSong(Songs** cabeza, int& IDSong) {
    Songs* NewSong = new Songs;
    cout << "Ingrese el nombre de la cancion: ";
    getline(cin, NewSong->SongsName);
    cout << "Ingrese el artista de la cancion: ";
    getline(cin, NewSong->ArtistsName);
    cout << "Ingrese el genero de la cancion: ";
    getline(cin, NewSong->genero);
    cout << "Ingrese el anio de salida de la cancion: ";
    cin >> NewSong->LaunchYear;
    cin.ignore();
    NewSong->id = ++IDSong;
    NewSong->siguiente = *cabeza;
    *cabeza = NewSong;
    cout << "Cancion agregada correctamente \n";

    ofstream archivo("SongsList", ios::app);
    if (archivo.is_open()) {
        archivo << NewSong->id << ";"
                << NewSong->SongsName << ";"
                << NewSong->ArtistsName << ";"
                << NewSong->genero << ";"
                << NewSong->LaunchYear
         << "\n";  
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo SongsList para escribir.\n";
    }
}



void ShowSongs(Songs *cabeza){
    Songs* actual = cabeza;
    if(actual == NULL){
        cout<< "No hay canciones...  \n";
        return;
    }
    cout<< "\nLista de canciones: \n";
    cout << "|  ID   |" << setw(27) << "Name       |"  << setw(22) << "Artista        " << "|" << setw(16) << "Genero    " << "|" << setw(8) << "Year " << "|" << endl;
    while(actual != NULL){
        cout << "|" << setw(6) << actual->id << " | " << setw(24) << actual->SongsName << " | " << setw(20) << actual->ArtistsName;
        cout << " | " << setw(14) << actual->genero << " | " << setw(6) << actual->LaunchYear
 << " |" << endl;    
        actual = actual -> siguiente;
    }
}

void DeleteSong(int id, Songs** cabeza, historial **historalAc = NULL) {
    if (*cabeza == NULL) {
        cout << "La lista de canciones esta vacia.\n";
        return;
    }
    Songs* actual = *cabeza;
    Songs* anterior = NULL;
    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (actual == NULL) {
        cout << "cancion con ID: " << id << " no encontrada.\n";
        return;
    }

    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    cout << "Cancion eliminada correctamente.\n";

    ifstream archivoEntrada("SongsList");
    ofstream archivoSalida("temp.txt");
    string linea;
    while (getline(archivoEntrada, linea)) {
        size_t pos = linea.find(';');
        int idArchivo = stoi(linea.substr(0, pos));
        if (idArchivo != id) {
            archivoSalida << linea << "\n";  
        }
    }
    archivoEntrada.close();
    archivoSalida.close();

    remove("SongsList");
    rename("temp.txt", "SongsList");
}

void AddSongTxt(Songs **p,int &idC,int id, string SongsName, string ArtistsName,string genero, int LaunchYea){
    Songs *SongNew = new Songs;
    if(id > idC){
        idC = id;
    }
    SongNew->id = id;
    SongNew->SongsName = SongsName;
    SongNew->ArtistsName = ArtistsName;
    SongNew->genero = genero;
    SongNew->LaunchYear = LaunchYear;
    SongNew->siguiente = *p;
    *p = SongNew;
}

int SearchHystC(historial *historialRef,Users *RuseR){
    historial *p = historialRef;
    int i = 1;
    while (p!=NULL && i == 1){
        if(p->IdUser->id = RuseR->id){
            i = 0;
            return 1;
        }
        p = p->siguiente;
    }
    return 0;
}

int SearchHystCC(historial *historialRef,Songs *canR){
    historial *p = historialRef;
    repro *j = p->listRepro;
    int i = 1;
    while (j!=NULL && i == 1){
        if(j->IdSongR->id = canR->id){
            i = 0;
            return 1;
        }
        j = j->siguiente;
    }
    return 0;
}

void PlaySongs(historial **historiaProyect,Users *Userhisto,Songs *SongHist){
    historial *p = *historiaProyect;
    int Likess;
    if(p == NULL){
        historial *aux = new historial;
        repro *aux1 = new repro;
        aux->IdUser = Userhisto;
        aux->listRepro = aux1;
        aux->siguiente= p;
        aux1->IdSongR = SongHist;
        aux1->cRepro = 1;
        cout<< "deseas dar Likes a esta cancion ( 1. si | 2. no )?" << endl;
        cin >> Likess;
        if (Likess==1){
            aux1->Likes = 1;
        }else{
            aux1->Likes = 0;
        }
 
        *historiaProyect = aux;
    }else{

        if(p != NULL){
            if(SearchHystC(p,Userhisto)==1){
                int i = 0;
                while(p !=NULL && i == 0){
                    if(p->IdUser->id = Userhisto->id){
                        if(SearchHystCC(p,SongHist) == 1){      
                            repro *j = p->listRepro;
                            int Q=0;
                            while(j != NULL && Q==0){
                                if(j->IdSongR->id == SongHist->id){
                                    j->cRepro++;
                                    if(j->Likes == 0){
                                        cout<< "deseas dar Likes a esta cancion ( 1. si | 2. no )?" << endl;
                                        cin >> Likess;
                                        if (Likess==1){
                                            j->Likes = 1;
                                        }else{
                                            j->Likes = 0;
                                        }
                                    }  
                                }
                                j = j->siguiente;
                            }
                        }else{
                        
                            repro *aux2 = new repro;
                            aux2->IdSongR = SongHist;
                            aux2->cRepro = 1;
                            cout<< "deseas dar Likes a esta cancion ( 1. si | 2. no )?" << endl;
                            cin >> Likess;
                            if (Likess==1){
                                aux2->Likes = 1;
                            }else{
                                aux2->Likes = 0;
                            }
                            aux2->siguiente = p->listRepro;
                            p->listRepro = aux2;
                            
                        }
                        
                        i=1;
                    }
                    p = p->siguiente;
                }
            }else{

                historial *aux = new historial;
                repro *aux1 = new repro;
                aux->IdUser = Userhisto;
                aux->listRepro = aux1;
                aux->siguiente= p;
                aux1->IdSongR = SongHist;
                aux1->cRepro = 1;
                cout<< "deseas dar Likes a esta cancion ( 1. si | 2. no )?" << endl;
                cin >> Likess;
                if (Likess==1){
                    aux1->Likes = 1;
                }else{
                    aux1->Likes = 0;
                }
                
                *historiaProyect = aux;
            }
        }
    }
}

int SearchSong(int canR,Songs *listCan){
    Songs *p = listCan;
    int i =0;

    while(p != NULL || i == 1){

        if( p->id == canR ){
            i = 1;
            return 1;
        }

        p = p->siguiente;
    }
        return 0;   
}

Songs canID(int canR,Songs *listCan){
    Songs *p = listCan;
    int i =0;
    while(p != NULL || i == 1){
        if( p->id == canR ){
            i = 1;
           
            return *p;
        }
        p = p->siguiente;
    }
 
    return *p;
}

Users UserID(int userR,Users *listUser){
    Users *p = listUser;
    int i = 0;
    while(p != NULL || i == 0){
        if( p->id == userR ){
            i = 1;
            return *p;
        }
        p = p->siguiente;
    }
        return *p;   
}

void UserIdTUser(Users **principal,int idR,Users *cabeza){
    Users *p = cabeza;
    int i = 0;
    while(p != NULL || i == 0){
        if( p->id == idR ){
            i = 1;
            *principal = p;
        }
        p = p->siguiente;
    } 
}

void canIdTC(Songs **principal,int idR,Songs *cabeza){
    Songs *p = cabeza;
    int i = 0;
    while(p != NULL || i == 0){
        if( p->id == idR ){
            i = 1;
            *principal = p;
        }
        p = p->siguiente;
    } 
}
int SearchUser(int userR,Users *listUser){
    Users *p = listUser;
    int i =0;
    while(p != NULL || i == 1){
        if( p->id == userR ){
            i = 1;
            return 1;
        }
        p = p->siguiente;
    }
    return 0;
}

int ClaveUser(string userR,Users *listUser){
    Users *p = listUser;
    int i =0;
    while(p != NULL || i == 1){
        if( p->Clave == userR ){
            i = 1;
            return 1;
        }
        p = p->siguiente;
    }
    return 0;
}

void ShowHist(historial *histoacutal){
    historial *Historialep = histoacutal;
    repro *aux;

    if (Historialep != NULL ){

        printC("historial de usuarios");
        while (Historialep != NULL){
            cout << " usuario: " << Historialep->IdUser->Name << endl;
            cout << "historial de musica: "<< endl;
            aux = Historialep->listRepro;
            while (aux != NULL){
                cout << "nombre de la cancion : " << aux->IdSongR->SongsName << endl;
                cout << "cantidad de veces escuchada: " << aux->cRepro << endl;
                cout << "Likes 1 si | 0 no: " << aux->Likes << endl;
                aux = aux->siguiente;
            }
            Historialep = Historialep->siguiente;
        }

    }else{
       cout<< "No hay historial disponible \n"; 
    }

}

