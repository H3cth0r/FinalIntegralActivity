/*
=====================================================
HashTable library and classes
11/10/2021
=====================================================
Héctor Miranda García-A01658845
Humberto Alejandro Rosas Téllez-A01659823
Isabel Cristina Valdés Luevanos-A01025802
Misael Chavez Ramos-A01659759
=====================================================
*/
/*
Class that creates the rows of the hashtable, with the capability
of inputing key on the left and value on the right.
*/
template<typename K, typename T> /* K key, T value*/
class HashPair{
  public:
    K key;
    T value;
    HashPair(K key, T value ){
      this->key = key;
      this->value  = value;
    }
     HashPair(){}

};
/*
Class for creating a hashtable.
*/
template<typename K, typename T> /* K key, T value*/
class Hashtable{
    private:
        int size;
        HashPair<K, T> * tabla;
        HashPair<K, T> null_hash;
        bool empty = true;                                            //O(1)

        int fh(K key){
            hash<K> khash;
            return khash(key) % size;                                 //O(1)
        }

    public:
    /*
    Builder
    */
      Hashtable(){
        this->size = 0;
      }
      Hashtable(int size){                                       //O(1)
        this->size = size;                                            //O(1)
        tabla = new HashPair<K,T>[size];  // hashpair array creation
        for(int i = 0; i < size; i++) tabla[i] = HashPair<K,T>();     //O(n)
        null_hash = tabla[0];                                         //O(1)
      }
      /*
      Destructor
      */
      ~Hashtable(){
        delete tabla;                                                 //O(1)
        size = 0;                                                     //O(1)
        empty = true;                                                 //O(1)
      }
      /*
      Method for inputting rows to the hastable.
      */
      bool put(K key, T value){
         int posicion = fh(key);                                     //O(1)
         this ->empty = false;                                       //O(1) 
         tabla[posicion] = HashPair<K,T>(key, value);
         return 1;                                                   //O(1)
      }
    /*
    Method for getting a value depending of some Key as parameter.
    */
      T get(K key){
        return tabla[fh(key)].value;                                //O()
      }
    /*
    Method for printing the whole hashtable-
    */
      void print(){
        for(int i = 0; i < size; i++){                                //O(n)
          cout <<"i: " << i << " k: " << tabla[i].key  << " v: " << tabla[i].value;
          cout << endl;
        }
      }
    /*
    Method for deleting all values from the hashtable.
    */
      void clear(){
        for(int i = 0; i < size; i++){                              //O(n)
          tabla[i] = null_hash;
        }
      }
    /*
    Method for checking if there is some key.
    */
      bool contains_key(K k){
        if(tabla[fh(k)].key == k) return true;                      //O(1)               
        return false;                                               //O(1)
      }
      /*
      Method for getting the value depending of key, if it doestn exist
      on hastable, it will return a default value.
      */
      T get_or_default(K k, T def = 0){
        if(contains_key(k)) return tabla[fh(k)].value;             //O(1)
        return def;                                                //O(1)
      }
      /*
      Method for checking whether the hashtable is full or empty.
      */
      bool is_empty(){
        for(int i = 0; i < size; i++) if(tabla[i].value != null_hash.value) return false;    //O(n)
        return true;                                                                         //O(1)
      }
      /*
      Method that takes another hastable of the same type and inputs all the value.
      */
      void put_all(const Hashtable<K,T>& other){
        for(int i = 0; i < size; i++){                                                      //O(n)
          if(other.tabla[i].key != tabla[i].key) tabla[i].key = other.tabla[i].key;         //O(1)
          tabla[i].value = other.tabla[i].value;
        }
      }
      /*
      Method for removing some row  depending of its key 
      */
      bool remove(K key){
        if(contains_key(key))tabla[fh(key)] = null_hash;
        else return false;                                                                //O(1)
        return true;                                                                      //O(1)
      }
      /*
      Method that return the number of not empty rows
      */
      int the_size(){
        int counter = 0;                                                                  //O(1)
        for(int i = 0; i < size; i++)if(tabla[i].value != null_hash.value) counter++;     //O(n)
        return counter;
      }
      /*
      operator overloading for checking whether two hastables are the same or not.
      */ 
      bool operator == (const Hashtable<K, T> & other) const{                             //O(1)
        if(size != other.size) return false;                                              //O(1)
        for(int i = 0; i < size; i++) if(tabla[i].value != other.tabla[i].value && tabla[i].key != other.tabla[i].key) return false; //O(n)
        return true;                                                                      //O(1)
      }

      friend ostream & operator << (ostream& os, const Hashtable<K, T> &ht){
        LinkedList<T> emptyll = LinkedList<T>();
        for(int i = 1; i < ht.size; i++){                                //O(n)
          if(ht.tabla[i].key != ht.null_hash.key){
            os <<"i: " << i << " k: " << ht.tabla[i].key  << " v: " << ht.tabla[i].value;
            os << endl;
          }
        }
        return os;
      }

      // additional methods
      bool add_value(K k, T value){
         tabla[fh(k)].value += 1;
         return true;                                                  //O(1)
      }
      void print_highest(){

        LinkedList<K> semanas = LinkedList<K>();
        int h_index = 0;
        int highest_num = 0;
        for(int i = 0; i < size; i++)if(tabla[i].value != null_hash.value){
          if(tabla[i].value > highest_num){ 
            highest_num = tabla[i].value;
            // semanas.push(tabla[i].key);
            h_index = i;
          }
        }
        for(int i = 0; i < size; i++)if(tabla[i].value != null_hash.value){
          if(tabla[i].value >= highest_num){ 
            highest_num = tabla[i].value;
            semanas.push(tabla[i].key);
            h_index = i;
          }
        }
        while(!semanas.is_empty()){
          cout << semanas.pop()<< " : ";
        }
        cout << endl;
      }
};