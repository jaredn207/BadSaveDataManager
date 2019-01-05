#ifndef filemanager_h
#define filemanager_h
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Book.h"
#include "Bookmark.h"
#include "Note.h"

using namespace std;

//Jared Newman

class FileManager
{
public:
	vector<Note> readNotes(string);
	vector<Bookmark> readBMs(string);
	string readBook(string);
	long readBookSS(string);
	void writeNotes(Book,vector<Note>);
	void writeBMs(Book,vector<Bookmark>);
	void writeBookSS(Book);
	void delBM(Book,Bookmark);
	void delNote(Book,Note);
private:
	ifstream fin;
	ofstream fout;
	void delBookSS(Book);
	void clearNotes(Book);
	void clearBMs(Book);
};
#endif
