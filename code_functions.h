void help(){    //Total: O(1)
    cout << endl;
    cout << "-h or --help       :   to acces ussage parameters or comments." << endl;                                                       //O(1)
    cout << "-f or --file       :   for setting the route and name of the file." << endl;                                                   //O(1)
    cout << "                       example:    main.exe -f route/documentName.txt" << endl;                                                //O(1)
    cout << "-d or --directions :   command to get the most breached directions. Input number of directions to be retrieved." << endl;      //O(1)
    cout << "                       example:    main.exe -f [...] -d 5   (returns five directions)." << endl;                               //O(1)
    cout << "--frequency        :   returns the frequency of each message." << endl;                                                        //O(1)
    cout << "                       example:    main.exe -f [...] --frequency" << endl;                                                     //O(1)
    cout << "-a or --attacked   :   returns number of attacked ports." << endl;                                                             //O(1)
    cout << "                       example:    main.exe -f [...] -a" << endl;                                                              //O(1)
    cout << "--dates            :   returns days wiht more breaches per week." << endl;                                                     //O(1)
    cout << "                       example:    main.exe -f [...] --dates" << endl;                                                         //O(1)
    cout << "\nYou can actually set various commands at the same run, for example:" << endl;                                                //O(1)
    cout << "main.exe -f route/fileName.txt -d 5 --frequency -a -d" << endl;                                                                //O(1)
};



// split function //Total: O(n)
void split(string line, string & month, string & day, string & hour, string & ip, string & reason){
  stringstream ss(line);// object to stream the variable                                                                                    //O(1)
  string word;          // variable to store each word in large string                                                                      //O(1)

  string reason_str;    // string to concatenate reason                                                                                     //O(1)

  int counter = 1;      // to check position of word                                                                                        //O(1)
  while(ss>>word){                                                                                                                          //O(n)
    
    switch(counter){
      case 1:
        month = word;   // modify month variable                                                                                           //O(1)
        break;
      case 2:
        day = word;     // modify day variable                                                                                              //O(1)
        break;
      case 3:
        hour = word;    // modify hour variable                                                                                             //O(1)
        break;
      case 4:
        ip = word;      // modify ip variable                                                                                               //O(1)
        break;
    }
    if(counter >= 5) reason_str += " " + word; // concatenating reason                                                                      //O(1)
    counter ++;                                                                                                                             //O(1)
  }
  reason = reason_str;                                                                                                                      //O(1)
}
// function to read each line of txt // Total: O(n)
void read_file(string fileName, LinkedList<Server> & auxiliar_ll){
  fstream txt_file;                                // creating an SStream object                                                            //O(1)
  txt_file.open(fileName, ios::in);          // opening bitacora file in input mode                                                         //O(n)


  // server atributes definition
  string month, day, hour, ip, reason;                                                                                                     //O(1)

  if(txt_file.is_open()){                          // checking wether the file is open or not                                              //O(1)
    string line;                                   // variable to store the line                                                           //O(1)
    while(getline(txt_file, line)){                                                                                                        //O(n)
      split(line, month, day, hour, ip, reason);  // splitting each line of txt and adding to                                              //O(n)
                                                  // corresponding variable.
      auxiliar_ll.addLast(Server(month, stoi(day), hour, ip, reason));                                                                     //O(1)
    }
    txt_file.close();                             // closing connection to bitacora file                                                    //O(1)
  }

};


void most_breached_ips( LinkedList<Server> s, Hashtable<string, int> & directions,const int & size_ll, int num_directions = 5){ //Total: O(n^2)
    vector<string> the_ips;                                                                                                                 //O(1)
    while(!s.is_empty()){                                                                                                                   //O(n)
        string direction_ip = s.pop().ip;                                                                                                   //O(1)
        string delimiter = ":";                                                                                                             //O(1)
        direction_ip = direction_ip.substr(0, direction_ip.find(delimiter));                                                                //O(1)
        if(!directions.contains_key(direction_ip)) {                                                                                        //O(1)
            directions.put(direction_ip, 1);                                                                                                //O(1)
            the_ips.push_back(direction_ip);                                                                                                //O(1)
        }
        else directions.add_value(direction_ip, 1);                                                                                         //O(1)
    } 

    LinkedList<string> the_stack = LinkedList<string>();                                                                                    //O(1)
    string auxiliar_interator_string = the_ips[0];                                                                                          //O(1)
    int auxiliar_interator_int = 0, auxiliar_index;                                                                                         //O(1)
    while(the_stack.length() != num_directions){                                                                                           //O(n)
        auxiliar_interator_string = the_ips[0];                                                                                            //O(1)
        auxiliar_interator_int = 0;                                                                                                       //O(1)
        for(int i = 0; i < the_ips.size(); i++){                                                                                          //O(n^2)
            if(directions.get(the_ips[i]) > auxiliar_interator_int){                                                                       //O(1)
                auxiliar_interator_int = directions.get(the_ips[i]);                                                                      //O(1)
                auxiliar_interator_string = the_ips[i];                                                                                   //O(1)                                             
                auxiliar_index = i;                                                                                                       //O(1)
            }
        }
        cout << auxiliar_interator_string << " : " << auxiliar_interator_int << endl;                                                     //O(1)
        the_ips.erase(the_ips.begin() + auxiliar_index);                                                                                  //O(1)
        the_stack.queue(auxiliar_interator_string);                                                                                       //O(1)
    }

};


void message_frequency(LinkedList<Server> s, Hashtable<string,int> & sms_frequency,const int size_ll){ //Total: O(n)
  while(!s.is_empty()){                                                                                                                 //O(n)
    string sms = s.pop().reason;                                                                                                        //O(1)
        if(!sms_frequency.contains_key(sms)) {                                                                                          //O(1)
            sms_frequency.put(sms, 1);                                                                                                  //O(1)
        }
        else sms_frequency.add_value(sms, 1);                                                                                           //O(1)
  }
  cout << sms_frequency << endl;                                                                                                        //O(1)
};


string splitter(string to_split,char delimeter){    //Total: O(n)                                                                                    
  string to_return;                                                                                                                     //O(1)
  bool option = false;                                                                                                                  //O(1)
  for(int i = 0; i < to_split.length(); i++){                                                                                           //O(n)
    if(to_split[i] == ':') {option = true;continue;}                                                                                    //O(1)
    if(option == true) to_return += to_split[i];                                                                                        //O(n)
  }
  return to_return;                                                                                                                     //O(1)
}

void count_briched_ports(LinkedList<Server> s, Hashtable<string, int> & attacked_ports,const int size_ll){    //Total:  O(n)                     
  string the_port;                                                                                                                      //O(1)
  string ip_and_port;                                                                                                                   //O(1)
  while(!s.is_empty()){                                                                                                                 //O(n)
    ip_and_port = s.pop().ip;                                                                                                           //O(1)
    the_port = splitter(ip_and_port, ':');                                                                                              //O(n)
    if(!attacked_ports.contains_key(the_port)) attacked_ports.put(the_port, 1);                                                         //O(1)
  }
  cout << "attacket ports: " << attacked_ports.the_size() << "/" << size_ll << endl;                                                    //O(n)
}


void most_vulnerable_week(LinkedList<Server> s, Hashtable<int, int> & weeks,const int size_ll){    //Total: O(n)
  vector <string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};                       //O(1)
  LinkedList<string> the_months = LinkedList<string>();                                                                                //O(1)
  for(int i = 0; i < months.size(); i++){                                                                                              //O(n)
    the_months.addLast(months[i]);                                                                                                     //O(1)
  }
  

  tm date = {};                                                                                                                     //O(1)
  date.tm_year = 2020-1900;                                                                                                         //O(1)
  Server auxiliar_server;                                                                                                           //O(1)
  while(!s.is_empty()){                                                                                                             //O(n)
    auxiliar_server = s.pop();                                                                                                      //O(1)
    date.tm_mon = the_months.indexOf(auxiliar_server.month)-0;                                                                      //O(1)
    // cout << "month>>" << date.tm_mon<< endl;
    date.tm_mday = auxiliar_server.day-0;                                                                                           //O(1)
    mktime(&date);                                                                                                                  //O(1)
    if(!weeks.contains_key(((date.tm_yday-date.tm_wday+7)/7)+1))weeks.put(((date.tm_yday-date.tm_wday+7)/7)+1, 1);                  //O(1)
    else weeks.add_value(((date.tm_yday-date.tm_wday+7)/7)+1, 1);                                                                   //O(1)
  }
  // cout << weeks << endl;
  cout << "weeks of the year with more attacks: " ;weeks.print_highest();cout <<endl;                                               //O(n)

  
};