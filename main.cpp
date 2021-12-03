#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

#include <time.h>   // for calculating and formating to week number
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
using namespace std;

// home-made libraries
#include "server.h"
#include "linkedlist.h"
#include "hashTable.h"
#include "code_functions.h"

// CString sDir = COleDateTime::GetCurrentTime().Format( "\\%Y\\%W" );


// argc == argument count. Count is set automatically.
// argv == argument vector(string of characters). literally arr of string, which can be indexed.
int main(int argc, char* argv[]){

    if(argc <= 1) exit(0);      // O(1)
    if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){help();exit(0);}   // O(1)

    LinkedList<char*> commands = LinkedList<char*>();      // queue creation  O(1)
    string route="abc";int number_breached_directions = 5; // variables to store input  O(1)
    LinkedList<Server>  auxiliar_ll;                        // O(1)
    int auxiliar_ll_size;                                   // O(1)
    for(int i = 1; i < argc; i++){                          // O(n)
        commands.queue(argv[i]);                            // O(n)
        if(strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0){route = argv[i+1];i++;}        // O(1)
        if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--directions") == 0){number_breached_directions = atoi(argv[i+1]);i++;}       // O(1)
    }
    string command = commands.dequeue();                    // O(1)
    read_file(route, auxiliar_ll);                          // O(n)
    auxiliar_ll_size = auxiliar_ll.length();                // O(n)
    Hashtable<string, int> attacked_ports(pow(auxiliar_ll_size,2.3));       // O(1)
    Hashtable<string, int> directions(pow(auxiliar_ll_size,2.3));           // O(1)
    Hashtable<string, int> sms_frequency(pow(auxiliar_ll_size,2.3));        // O(1)
    Hashtable<int, int> weeks(pow(auxiliar_ll_size,2.3));                   // O(1)


    while(!commands.is_empty()){ // O(n)
        command = commands.dequeue();   // O(1)
        if(command == "-a" || command == "--attacked"){ // O(1)
            cout << "========= BREACHED PORTS ==========" << endl;  // O(1)
            count_briched_ports(auxiliar_ll, attacked_ports, auxiliar_ll_size); // O(n)
        }
        if(command == "-d" ||command == "--directions"){            // O(1)
            cout << "========= MOST BREACHED IPs =========" << endl;    // O(1)
            most_breached_ips(auxiliar_ll, directions, auxiliar_ll_size, 5);    // O(n^2)
        }
        if(command == "--frequency"){   // O(1)
            cout << "========= FREQUENCY OF EACH MESSAGE =======" << endl;  // O(1)
            message_frequency(auxiliar_ll, sms_frequency, auxiliar_ll_size);    // O(n)
        }
        if(command == "--dates"){           // O(1)
            cout << "======== MOST VULNERABLE WEEK OF THE YEAR =====" << endl;  // O(1)
            most_vulnerable_week(auxiliar_ll, weeks, auxiliar_ll_size);         // O(n)
        }

    }
    
    return 0;
};