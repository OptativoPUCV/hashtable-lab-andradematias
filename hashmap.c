#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  Pair *dato = createPair(key, value);
  int i;
  i = hash(key, map->capacity);
  while (map->buckets[i] != NULL)
  {
    if (map->buckets[i]->key == NULL) break;
    if (i == map->capacity-1) i = 0;
    i++;
  }
  map->buckets[i] = dato;
  map->size++;
  map->current = i;  
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *M = (HashMap *) malloc (sizeof(HashMap));
    M->buckets = (Pair **) malloc (capacity*sizeof(Pair *));
    M->capacity = capacity;
    M->size = 0;
    M->current = -1;
    int i;
    for (i = 0;i<capacity;i++)
    {
      M->buckets[i] = NULL;
    }
    return M;
}

void eraseMap(HashMap * map,  char * key) {    


}

void * searchMap(HashMap * map,  char * key) {   

    int i = hash(key, map->capacity);

    if (map->buckets[i]->key == key)
    {
      map->current = i;
      return map->buckets[i]->value;   
    }
    else
    {
      while (map->buckets[i] != NULL)
      {
        if (map->buckets[i]->key == key)
        {
          map->current = i;
          return map->buckets[i]->value;
        }
        if (i == map->capacity-1) i = 0;
        i++;
      }
    }    
    map->current = i;    
    return NULL;
}

void * firstMap(HashMap * map) {

    return NULL;
}

void * nextMap(HashMap * map) {

    return NULL;
}
