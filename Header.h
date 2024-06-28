#pragma once
using namespace std;
using namespace System;
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>

void colorAssign(int codeColor) {
    switch (codeColor) {
    case 1: Console::ForegroundColor = ConsoleColor::Black; break;
    case 2: Console::ForegroundColor = ConsoleColor::DarkBlue; break;
    case 3: Console::ForegroundColor = ConsoleColor::DarkGreen; break;
    case 4: Console::ForegroundColor = ConsoleColor::DarkRed; break;
    case 5: Console::ForegroundColor = ConsoleColor::DarkMagenta; break;
    case 6: Console::ForegroundColor = ConsoleColor::DarkYellow; break;
    case 7: Console::ForegroundColor = ConsoleColor::Gray; break;
    case 8: Console::ForegroundColor = ConsoleColor::DarkGray; break;
    case 9: Console::ForegroundColor = ConsoleColor::Blue; break;
    case 10: Console::ForegroundColor = ConsoleColor::Green; break;
    case 11: Console::ForegroundColor = ConsoleColor::Cyan; break;
    case 12: Console::ForegroundColor = ConsoleColor::Red; break;
    case 13: Console::ForegroundColor = ConsoleColor::Magenta; break;
    case 14: Console::ForegroundColor = ConsoleColor::Yellow; break;
    case 15: Console::ForegroundColor = ConsoleColor::White; break;
    case 16: Console::BackgroundColor = ConsoleColor::Blue; break;
    case 17: Console::BackgroundColor = ConsoleColor::Yellow; break;
    case 18: Console::BackgroundColor = ConsoleColor::Red; break;
    case 19: Console::BackgroundColor = ConsoleColor::Green; break;
    case 20: Console::BackgroundColor = ConsoleColor::White; break;
    case 21: Console::BackgroundColor = ConsoleColor::Black; break;
    case 22: Console::BackgroundColor = ConsoleColor::Cyan; break;
    }
}

void charge() { std::cout << "\n\n CARGANDO.."; Sleep(1000); }

void barCharge() { 
    for (size_t i = 0; i < 51; i++) {
        Console::SetCursorPosition(0, 24); std::cout << " COMPLETADO " << char(175) << " " << i * 2 << " %";
        std::cout << " ------------------------------";
        if (i < 50)Console::SetCursorPosition((i), 25); std::cout << char(219);
        Sleep(25);
    };
}

void applicationLogo() {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    string logo[24] = {
        "                                        \n",
        "                                        \n",
        "   ##              ##   #############   \n",
        "   ##              ##              ##   \n",
        "   ##              ##              ##   \n",
        "   ##              ##              ##   \n",
        "   ##              ##              ##   \n",
        "   ##       ##     ##              ##   \n",
        "   ##     ##  ##   ##   #          ##   \n",
        "   ##   ##     ##  ##    ##        ##   \n",
        "   ## ##        ## ##      ##      ##   \n",
        "   ###           ####        #######    \n",
        "                                        \n",
        "                                        \n",
    };
    for (int i = 0; i < 24; i++) {
        Console::SetCursorPosition(35, 5 + i); std::cout << logo[i];
        Sleep(100);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    _getch();
}

void applicationExit() {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    string logo[32] = {
        "                                                                             \n",
        "                                                                             \n",
        "   GGGGGGGG  RRRRRRR    AAAAAAA   CCCCCC   II  AAAAAAAAA    SSSSSSSSS        \n",
        "  GG         RR     R  AA     AA  CC     C  II  AA     AA  SS                \n",
        "  GG         RRRRRRR   AA     AA  CC        II  AA     AA  SS                \n",
        "  GG   GGGG  RR RR     AAAAAAAAA  CC        II  AAAAAAAAA   SSSSSSSS         \n",
        "  GG     GG  RR  RR    AA     AA  CC        II  AA     AA           SS       \n",
        "  GG     GG  RR   RR   AA     AA  CC     C  II  AA     AA          SS        \n",
        "   GGGGGGGG  RR    RR  AA     AA   CCCCCC   II  AA     AA  SSSSSSSSS         \n",
        "                                                                             \n",
        "                                                                             \n",
    };
    for (int i = 0; i < 32; i++) {
        Console::SetCursorPosition(36, 5 + i); std::cout << logo[i];
        Sleep(100);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    _getch();
}


void backGroundMenu() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    string logo[24] = {
        "                                        \n",
        "                                        \n",
        "                                        \n",
        "      ------------------------          \n",
        "        BIENVENIDO DE VUELTA            \n",
        "      ------------------------          \n",
        "                                        \n",
        "          Por Favor Espere              \n",
        "                                        \n",
        "                                        \n",
        "                                        \n",
        "                                        \n",
        "                                        \n",
    };
    for (int i = 0; i < 24; i++) {
        Console::SetCursorPosition(35, 5 + i); std::cout << logo[i];
        Sleep(100);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    charge();
}

void settings() {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    std::cout << " ----------------------------------------- " << endl;
    std::cout << "   [ ALGORITMOS Y ESTRUCTURAS DE DATOS ]   " << endl;
    std::cout << "           CC182 - 202401 - SS34           " << endl;
    std::cout << " ----------------------------------------- " << endl;
    std::cout << " PROFESOR: John Edward Arias Orihuela " << endl << endl;
    std::cout << " Integrantes: " << endl;
    std::cout << " [2] Alison Jimena Arrieta Quispe - U202312031 " << endl;
    std::cout << " [1] Alessandra Nicole Becerra Tejeda - U202318947 " << endl;
    std::cout << " [3] Leandro Saul Contreras Lopez - U20231E215 " << endl;
    std::cout << " Grupo 02 - WhatJourney " << endl << endl;
    std::cout << " --- [ Historia ] --- " << endl;
    std::cout << " En muchas ciudades del mundo, los problemas de trafico, " << endl;
    std::cout << " la falta de informacion precisa sobre rutas y horarios de transporte, " << endl;
    std::cout << " y la ineficiencia en la gestion de los recursos de transporte publico son desafios recurrentes" << endl; 
    std::cout << " WhatJourney proporciona una herramienta eficiente y facil de usar para los usuarios del transporte publico" << endl;
    std::cout << " ayudándoles a planificar sus viajes de manera optima. " << endl;
}

int showMenu() {
    Console::ForegroundColor = ConsoleColor::Yellow; 
    std::cout << "          _    _ _           _     ___" << std::endl;
    std::cout << "         | |  | | |         | |   |_  |" << std::endl;
    std::cout << "         | |  | | |__   __ _| |_    | | ___  _   _ _ __ _ __   ___ _   _" << std::endl;
    std::cout << "         | |\\/| | '_ \\ / _` | __|   | |/ _ \\| | | | '__| '_ \\ / _ \\ | | |" << std::endl;
    std::cout << "         \\  /\\  / | | | (_| | |_/\\__/ / (_) | |_| | |  | | | |  __/ |_| |" << std::endl;
    std::cout << "          \\/  \\/|_| |_|\\__,_|\\__|\\____/\\___/ \\__,_|_|  |_| |_|\\___|\\__, |" << std::endl;

    std::cout << "  |'''''||'''''||'''''||'''''||'''''||'''''||'''''||'''''||'''''||'__/  |'''''|| '''''| " << endl;
    std::cout << "  '-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-|___/ -0-0-''`-0-0-'" << endl;

    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|                                                                           |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|   1   |           Registrar usuario                                       |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|   2   |           Iniciar sesion                                          |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|   3   |           Mostrar usuarios                                        |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|   4   |           Generar usuarios empleados (conductores)                |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|   5   |           Generar usuarios (Personas/Companias)                   |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|   6   |           Mostrar grafo de conductores generados                  |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|   7   |           Extras                                                  |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;
    std::cout << "|   8   |           Salir                                                   |" << endl;
    std::cout << " ---------------------------------------------------------------------------" << endl;

    int opcion;
    do {
       cin >> opcion;
       if (opcion < 1 || opcion > 8)
        std::cout << "Ingrese una opcion valida... ";
    } while (opcion < 1 || opcion> 8);

    return opcion;
}