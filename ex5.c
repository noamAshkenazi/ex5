/******************
Name: Noam Ashkenazi
ID: 213370869
Assignment: ex5
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free();

typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

//help building a linked list of songs
typedef struct SongItem {
    Song* data;
    struct SongItem* next;
} SongItem;

//struct that contains the first and the last on the list of songs
typedef struct SongsList {
    SongItem *head, *last;
} SongsList;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

//help building a linked list of the playlists
typedef struct PlaylistItem {
    Playlist* data;
    struct PlaylistItem* next;
} PlaylistItem;

//struct that contains the first and the last on the list of playlists
typedef struct PlaylistList {
    PlaylistItem *head, *last;
    int playlistNum;
} PlaylistList;

void deleteSong();
void removePlaylist(playlistList* list, Playlist* playlist);
void freeSong(Song* song);
void freePlaylist(P);
void playSong();

void printMainMenu();
void printPlaylistsMenu();
void printPlaylistMenu();
void printPlaylistData()
void sortPlaylist();
void printWatchPlaylistsMenu();
void printSongData();
void printPlaylistSongs();
void printPlaylistMenu();

int main() {
    printf("Goodbye!\n");
}

//creating a new songs list
SongsList* newSongList(){
    SongsList* sl = (SongsList*)malloc(sizeof(SongsList));
    sl->head = NULL;
    sl->last = NULL;
    return sl;
}

//creating a new song
Song* createNewSong(char* title, char* artist, int year, char* lyrics){
  Song* ns = (Song*)malloc(sizeof(Song));
  ns->title = (char*)malloc(strlen(title) + 1);
  strcpy(ns->title, title);
  ns->artist = (char*)malloc(strlen(artist) + 1);
  strcpy(ns->artist, artist);
  ns->year = year;
  ns->lyrics = (char*)malloc(strlen(lyrics) + 1);
  strcpy(ns->lyrics, lyrics);
  ns->streams = 0;
  return ns;
}

//adding a song to a list of songs - to a playlist
void addSong(SongsList* list, Song* newSong){
  SongItem* item = (SongItem*)malloc(sizeof(SongItem));
  item->data = newSong;
  item->next = NULL;
  if(list->head == NULL){
    //ToDo: can i connect this = ; if yes do it on other places as well.
    list->head = list->last = item;
  }
}

void addPlaylist(PlaylistList* playlistList, Playlist* newPlaylist){
    PlaylistItem* item = (PlaylistItem*)malloc(sizeof(PlaylistItem));
    item->data = newPlaylist;
    item->next = NULL;
    //if the list is empty
    if(playlistList->head == NULL){
        playlistList->head = item;
        playlistList->last = item;
    }
    else{
        playlistList->last->next = item;
        playlistList->last = item;
    }
    playlistList->playlistNum++;
}

//creating a new playlists list
PlaylistList* newPlaylistList(){
  PlaylistList* pl = (PlaylistList*)malloc(sizeof(PlaylistList));
  pl->head = NULL;
  pl->last = NULL;
  pl->playlistNum = 0;
  return pl;
}

//creating a new playlist
Playlist* createNewPlaylist(char* name, Song** songs, int songsNum){
  Playlist* pl = (Playlist*)malloc(sizeof(Playlist));
  pl->name = (char*)malloc(strlen(name) + 1);
  strcpy(pl->name, name);
  //ToDo: is it written ok?
  Songs** songs = (Songs**)malloc(sizeof(Songs*));
  pl->songs = songs;
  pl->songsNum = songsNum;
  return pl;
}

//adding a new playlist to the end of the list. Assuming the list exists.
void addPlaylist(PlaylistList* playlistList, Playlist* newPlaylist){
  PlaylistItem* item = (PlaylistItem*)malloc(sizeof(PlaylistItem));
  item->data = newPlaylist;
  item->next = NULL;
  //if the list is empty
  if(playlistList->head == NULL){
    playlistList->head = item;
    playlistList->last = item;
  }
  else{
    playlistList->last->next = item;
    playlistList->last = item;
  }
  playlistList->playlistNum++;
}


//release dynamically allocated memory for song.
void freeSong(Song* s) {
  if(s != NULL){
  //free title
    printf("freeing %s\n", s->title); //debug
    free(s->title);
  //free artist
    printf("freeing %s\n", s->artist); //debug
    free(s->artist);
  //free lyrics
    printf("freeing %s\n", s->lyrics); //debug
    free(s->lyrics);
  //free song
    free(s);
  }
}

//release dynamically allocated memory for song data, next, and itself from a list of songs
freeSongItem(SongItem* item){
  if(item != NULL){
    freeSong(item->data);
    free(item);
  }
}

//release dynamically allocated memory for all the songs in the list.
void freeAllSongs(SongsList* list){
    SongItem* item = list->head;
    if(item != NULL){
        deleteSong(list, item->data);
        freeSongItem(item->next);
        free(item);
    }
}

//release dynamically allocated memory for playlist.
void freePlaylist(Playlist* ps){
  if(ps != NULL){
    freeAllSongs(ps->Songs);
    //free the songs list
    free(ps->Songs);
    printf("freeing %s\n", ps->name); //debug
    free(ps->name);
    free(ps);
  }
}

//free a playlist data, next, and itself from a list of playlists
void freePlaylistItem(PlaylistItem* item){
  if(item != NULL){
    freePlaylist(item->data);
    free(item);
  }
}

//free all playlists in the list, from item to the end. ////place 0????
void freeAllPlaylists(PlaylistItem* item){
    if(item != NULL){
        freePlaylist(item->data);
        freePlaylistItem(item->next);
        free(item);
    }
}

//check if this song is the same song i'm looking for. If it does, returns 1. Otherwise, returns 0.
int equalSong(Song *song1, Song *song2) {
        // Check if both pointers are non-null and compare fields
        if (song1 == NULL || song2 == NULL) {
            // If either is NULL, they are not equal
            return false;
        }
        // Compare title, artist, and year
        //ToDo: check if there is validity about the same names - so i can only check the name of the song
        if (strcmp(song1->title, song2->title) == 0 &&
            strcmp(song1->artist, song2->artist) == 0 &&
            song1->year == song2->year) {
            return true; // Songs are equal if all fields match
            } else{
                return false; // Return false if any field does not match
            }
}

//check if this playlist is the same playlist i'm looking for. If it does, returns 1. Otherwise, returns 0.
int equalPlaylist(Playlist *p1, Playlist *p2) {
    // Check if both pointers are non-null and compare fields
    if (p1 == NULL || p2 == NULL) {
        // If either is NULL, they are not equal
        return false;
    }
    // Compare title, artist, and year
    //ToDo: check if there is validity about the same names - so i can only check the name of the playlist
    if (strcmp(p1->title, p2->title) == 0 &&
        strcmp(p1->artist, p2->artist) == 0 &&
        p1->year == p2->year) {
        return true; // playlists are equal if all fields match
        } else{
            return false; // Return false if any field does not match
        }
}

//delete a song from a songs list
void deleteSong(SongsList* list, Song* s) {
    SongItem* iterator = list->head;
    SongItem* previous;
    if(list->head && equalSong(list->head->data, s) == 1){
        list->head = iterator->next;
        if(list->head == NULL){
            list->last = NULL;
        }
        iterator->next = NULL;
        freeSongItem(iterator);
        return;
    }
    while(iterator != NULL && equalSong(iterator->data, s) == 0){
        previous = iterator;
        iterator = iterator->next;
    }
    if(iterator == NULL) return;
    else if (equalSong(iterator->data, s) == 1){
        previous->next = iterator->next;
        iterator->next = NULL;
        if(iterator = list->last){
            list->last = previous;
        }
        freeSongItem(iterator);
    }
    printf("Song deleted successfully.\n");
}

//remove a playlist from the list of the playlist. Also free what is needd.
void removePlaylist(playlistList* list, Playlist* playlist) {
    PlaylistItem* iterator = list->head;
    PlaylistItem* previous;
    if(list->head && equalPlaylist(list->head->data, playlist) == 1){
      list->head = iterator->next;
      if(list->head == NULL){
        list->last = NULL;
      }
      iterator->next = NULL;
      freePlaylistItem(iterator);
      return;
    }
    while(iterator != NULL && equalPlaylist(iterator->data, playlist) == 0){
          previous = iterator;
          iterator = iterator->next;
    }
    if(iterator == NULL) return;
    else if (equalPlaylist(iterator->data, playlist) == 1){
      previous->next = iterator->next;
      iterator->next = NULL;
      if(iterator = list->last){
        list->last = previous;
      }
      freePlaylistItem(iterator);
    }
}


void playSong() {
}


void printMainMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}


//the second menu. after choosing 1 in the first menu.
void printPlaylistsMenu() {
    printf("Please Choose:\n");
    //using PLAYLIST_AMOUNT
    //playlistnames
    //back to main menu
}

//print the data of a specific song.
void printSongData() {
    printf("data:\n");
    //printf("\tTitle: %s\n\tArtist: %s\n\tReleased: %d\n\tStreams: %d\n", -----)
}

//print the data of all the songs in this playlist.
void printPlaylistSongs() {
    printf("data:\n");
    //printSongData() * SONGS_AMOUNT
    //print each song details + SONG_NUMBER_IN_PLAYLIST
}

//the third menu. After choosing 1 in the secong menu. Actions about a specific playlist.
void printPlaylistMenu() {
    printf("Please Choose:\n");
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
}

void sortPlaylist() {
    printf("sorted\n");
}

