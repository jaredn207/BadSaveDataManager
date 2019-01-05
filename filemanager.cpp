#include "filemanager.h"

//Jared Newman

//Working
vector<Note> FileManager::readNotes(string title)
{
	//Opening notes.dat to be read from
	fin.open("notes.dat");
	//Basic things needed
	int i(0);
	long charPos;
	string notes;
	string line;
	stringstream titless, charPosss, notess;
	//Array of Notes to return
	vector<Note> returnNotes;
	//If fail, no notes found, returns an empty array
	if(fin.fail())
	{
		cout << "No notes found." << endl;
		fin.close();
		return returnNotes;
	}
	//Loops through each line
	while((getline(fin,line)) && (line.compare("")!=0))
	{
		//Loops until it hits a semicolon, saving the title in the process
		while(line.at(i)!=':')
		{
			titless << line.at(i);
			i++;
		}
		//Skip one so 'i' isnt on a semicolon
		i++;
		//If the title equals the target, loop until it hits a semicolon
		//saving the charPos in the process
		while((title.compare(titless.str()) == 0) && (line.at(i)!=':'))
		{
			charPosss << line.at(i);
			i++;
		}
		//If the title is equal, convert the charPos string stream to a
		//actual long
		if(title.compare(titless.str()) == 0)
		{
			istringstream convert(charPosss.str());
			convert >> charPos;
		}
		//Skip one so 'i', isn't on a long
		i++;
		//Loop until it hits a semicolon, saving the note in the process
		while((title.compare(titless.str()) == 0) && (line.at(i)!=':'))
		{
			notess << line.at(i);
			i++;
		}
		//If the title equals the target, create a new Note, adding it to the
		//array
		if(title.compare(titless.str())==0)
		{
			returnNotes.push_back(Note(notess.str(),charPos)); //May change
		}
		//Reseting everything for the next line
		titless.str("");
		titless.clear();
		charPosss.str("");
		charPosss.clear();
		notess.str("");
		notess.clear();
		i=0;
	}
	//Closing notes.dat, then returning the array, even if it's empty.
	fin.close();
	return returnNotes;
}

//Working
vector<Bookmark> FileManager::readBMs(string title)
{
	//Opening bookmarks.dat to read from
	fin.open("bookmarks.dat");
	//Basic stuff
	int i(0);
	long savedPos;
	string line;
	stringstream titless, charPosss;
	//Array of bookmarks to return
	vector<Bookmark> returnbms;
	//If fail, no bookmarks found, return an empty array
	if(fin.fail())
	{
		cout << "No bookmarks found." << endl;
		fin.close();
		return returnbms;
	}
	//Loops through each line of bookmarks.dat
	while((getline(fin,line)) && (line.compare("")!=0))
	{
		//Loops until it hits a semicolon, saving the title in the process
		while(line.at(i)!=':')
		{
			titless << line.at(i);
			i++;
		}
		//Skip one so 'i' isn't on a semicolon
		i++;
		//If the title is equal to the target, loop until it hits a semicolon
		//saving the charPos in the process
		while((title.compare(titless.str()) == 0) && (line.at(i)!=':'))
		{
			charPosss << line.at(i);
			i++;
		}
		//If the title is equal to the target, convert the charPos to a long
		//and create a new bookmark, adding it to the array.
		if(title.compare(titless.str()) == 0)
		{
			istringstream convert(charPosss.str());
			convert >> savedPos;
			returnbms.push_back(Bookmark(savedPos));//may change
		}
		//Reseting everything for the next line
		titless.str("");
		titless.clear();
		charPosss.str("");
		charPosss.clear();
		i=0;
	}
	//Closing bookmarks.dat, then returning the array, even if it's empty
	fin.close();
	return returnbms;
}

//Working
string FileManager::readBook(string fileName)
{
	//Opening the file targeted by the user
	fin.open(fileName.c_str());
	//If fail, the file doesnt exist
	if(fin.fail())
	{
		fin.close();
		return "";
	}
	//Get the length of the file in char's
	fin.seekg (0, fin.end);
	int length = fin.tellg();
	fin.seekg (0, fin.beg);
	//New buffer for the file to read into
	char * buffer = new char [length];
	fin.read (buffer,length);
	//string stream to convert the buffer into a string
	stringstream ss;
	ss << buffer;
	string bookContent = ss.str();	
	//Clean-up and close the file
	fin.close();
	delete[] buffer;
	//Returns the entire content of the file in a string
	return bookContent;
}

//Working
long FileManager::readBookSS(string title)
{
	//Opening savestates.dat to read from
	fin.open("savestates.dat");
	//Basic things needed
	int i(0);
	long savedPos(0);
	string line;
	//Multiple stringstreams for each field
	stringstream titless, charPosss;
	//If failing to open the file, return 0;
	if(fin.fail())
	{
		cout << "No save states found." << endl;
		fin.close();
		return savedPos;
	}
	//Loops through each line of savestates.dat
	while((getline(fin,line)) && (line.compare("")!=0))
	{
		//Loops until hitting a semicolon, saving the title in the process
		while(line.at(i)!=':')
		{
			titless << line.at(i);
			i++;
		}
		//Skip one so 'i' isn't on a semicolon
		i++;
		//If the title is equal to the target, loop until it hits a semicolon
		//saving the charPos in the process
		while((title.compare(titless.str()) == 0) && (line.at(i)!=':'))
		{
			charPosss << line.at(i);
			i++;
		}
		//If the title is true, convert the charPos string stream into an
		//actual long, and return it, closing the file and ending the function.
		if(title.compare(titless.str()) == 0)
		{
			istringstream convert(charPosss.str());
			convert >> savedPos;
			fin.close();
			return savedPos;
		}
		//Reseting everything for the next loop
		titless.str("");
		titless.clear();
		charPosss.str("");
		charPosss.clear();
		i=0;
	}
	//Closing the file, in this case, the target wasnt found,
	//so the method would return 0, meaning the book was never opened/is new
	fin.close();
	return savedPos;
}

//Working
void FileManager::writeNotes(Book b,vector<Note> n)
{
	clearNotes(b);
	//Opening the notes storage file to be written to.
	fout.open("notes.dat",std::ios::app);
	stringstream ss;
	//Getting the length of the array, dividing the bit size of the
	//array by the type.
	int length = n.size();
	//Running through the entire array, writing to notes.dat
	for(int i=0; i<length;i++)
	{
		ss.str("");
		ss.clear();
		ss << b.getTitle() << ":" << n[i].getCharPos() << ":" << n[i].getNote() << ":";
		fout << ss.str() << endl;
	}
	//Closing the file interface
	fout.close();
}

//Working
void FileManager::writeBMs(Book b, vector<Bookmark> bm)
{
	clearBMs(b);
	//Opening the bookmarks storage file to be written to.
	fout.open("bookmarks.dat",std::ios::app);
	stringstream ss;
	//Getting the length of the array, dividing the bit size of the
	//array by the type.
	int length = bm.size();
	//Runing through the entire array, writing to bookmarks.dat
	for(int i=0; i<length;i++)
	{
		ss.str("");
		ss.clear();
		ss << b.getTitle() << ":" << bm[i].getCharPos() << ":";
		fout << ss.str() << endl;
	}
	//Closing the file interface
	fout.close();
}

//Working
void FileManager::writeBookSS(Book b)
{
	delBookSS(b);
	//Opening the savestates storage file to be written to.
	fout.open("savestates.dat",std::ios::app);
	//Using a string stream to create a full line
	stringstream ss;
	ss << b.getTitle() << ":" << b.getCurrentPageFirstCharPos() << ":";
	//Writing to the file
	fout << ss.str() << endl;
	//Closing the file interface
	fout.close();
}

//Working
void FileManager::delBM(Book b, Bookmark bm)
{
	//Reading from bookmarks.dat, temp.dat will have everything but the targeted
	//book's bookmark written to it.
	fin.open("bookmarks.dat");
	if(fin.fail())
	{
		fin.close();
		cout << "No BookMarks to delete" << endl;
		return;
	}
	fout.open("temp.dat");
	//Basic needed stuff
	int i=0;
	string line;
	long charPos;
	//Multiple stringstreams needed for each field
	stringstream titless,charPosss;
	//Loops through each of notes.dat's lines
	while((getline(fin,line)) && (line.compare("")!=0))
	{
		//Runs until it hits a semicolon, saving the title in the process
		//to a string stream.
		while(line.at(i)!=':')
		{
			titless << line.at(i);
			i++;
		}
		//Skip one so 'i' isn't on a semicolon
		i++;
		//Runs until it hits a semicolon, saving the charPos in the process
		//to a string stream
		while(line.at(i)!=':')
		{
			charPosss << line.at(i);
			i++;
		}
		//Converts the charPos string stream to an actual long field
		istringstream convert(charPosss.str());
		convert >> charPos;
		//Compares all the elements, if all the elements DON'T match with the
		//target, then the line is written to temp.dat
		if((b.getTitle().compare(titless.str()) != 0) && (bm.getCharPos() != charPos))
		{
			fout << line << endl;
		}
		//Reseting everything for the next line
		titless.str("");
		titless.clear();
		charPosss.str("");
		charPosss.clear();
		convert.str("");
		convert.clear();
		charPos=0;
		i=0;
	}
	//Closing all the file interfaces
	fin.close();
	fout.close();
	//temp.dat becomes the new bookmarks.dat, removing all the targeted notes
	//in the process.
	remove("bookmarks.dat");
	rename("temp.dat","bookmarks.dat");
}

//Working
void FileManager::delNote(Book b,Note n)
{
	//Reading from notes.dat, temp.dat will have everything but the targeted
	//book's note written to it.
	fin.open("notes.dat");
	if(fin.fail())
	{
		fin.close();
		cout << "No Notes to delete" << endl;
		return;
	}
	fout.open("temp.dat");
	//Basic needed stuff
	int i=0;
	string line;
	long charPos;
	//Multiple stringstreams needed for each field
	stringstream titless,notess,charPosss;
	//Loops through each of notes.dat's lines
	while((getline(fin,line)) && (line.compare("")!=0))
	{
		//Runs until it hits a semicolon, saving the title in the process
		//to a string stream.
		while(line.at(i)!=':')
		{
			titless << line.at(i);
			i++;
		}
		//Skip one so 'i' isn't on a semicolon
		i++;
		//Runs until it hits a semicolon, saving the charPos in the process
		//to a string stream
		while(line.at(i)!=':')
		{
			charPosss << line.at(i);
			i++;
		}
		//Converts the charPos string stream to an actual long field
		istringstream convert(charPosss.str());
		convert >> charPos;
		//Skip one so 'i' isn't on a semicolon
		i++;
		//Runs until it hits a semicolon, saving the note in the process
		//to a string stream
		while(line.at(i)!=':')
		{
			notess << line.at(i);
			i++;
		}
		//Compares all the elements, if all the elements DON'T match with the
		//target, write the line to temp.dat
		if((b.getTitle().compare(titless.str()) != 0) && (n.getNote().compare(notess.str()) != 0) && (n.getCharPos() != charPos))
		{
			fout << line << endl;
		}
		//Reseting everything for the next line
		notess.str("");
		notess.clear();
		titless.str("");
		titless.clear();
		charPosss.str("");
		charPosss.clear();
		convert.str("");
		convert.clear();
		charPos=0;
		i=0;
	}
	//Closing all the file interfaces
	fin.close();
	fout.close();
	//temp.dat becomes the new notes.dat, removing all the targeted notes
	//in the process.
	remove("notes.dat");
	rename("temp.dat","notes.dat");
}

//Working
void FileManager::delBookSS(Book b)
{
	//Reading from savestates.dat, temp.dat will have everything but the targeted
	//book's savestate writen to it.
	fin.open("savestates.dat");
	if(fin.fail())
	{
		fin.close();
		cout << "No save states to delete" << endl;
		return;
	}
	fout.open("temp.dat");
	//Basic things needed.
	int i=0;
	string line;
	stringstream ss;
	//Loops through each of savestates.dat's lines.
    while(getline(fin,line) && line.compare("")!=0)	        
	{
		//Runs until it hits a semicolon, saving the title in the process
		//to a string stream.
		while(line.at(i)!=':')
		{
			ss << line.at(i);
			i++;
		}
		//Checks if the previously read title matches the target,
		//if they don't match, the targeted line IS written to temp.dat.
		if(b.getTitle().compare(ss.str()) != 0)
		{
			fout << line << endl;
		}
		//Reseting everything for the next line.
		ss.str("");
		ss.clear();
		i=0;
	}
	//Closing all file interfaces.
	fin.close();
	fout.close();
	//temp.dat becomes the new savestates.dat, removing all the targeted notes
	//in the process.
	remove("savestates.dat");
	rename("temp.dat","savestates.dat");
}

//Working, private method
void FileManager::clearNotes(Book b)
{
	//Reading from notes.dat, temp.dat will have everything but the targeted
	//book's notes writen to it.
	fin.open("notes.dat");
	if(fin.fail())
	{
		fin.close();
		//No notes to clear
		return;
	}
	fout.open("temp.dat");
	//Basic things needed.
	int i=0;
	string line;
	stringstream ss;
	//Loops through each of notes.dat's lines.
	while((getline(fin,line)) && (line.compare("")!=0))
	{
		//Runs until it hits a semicolon, saving the title in the process
		//to a string stream.
		while(line.at(i)!=':')
		{
			ss << line.at(i);
			i++;
		}
		
		//Checks if the previously read title matches the target,
		//if they don't match, the targeted line IS written to temp.dat.
		if(b.getTitle().compare(ss.str()) != 0)
		{
			fout << line << endl;
		}
		//Reseting everything for the next line.
		ss.str("");
		ss.clear();
		i=0;
	}
	//Closing all file interfaces.
	fin.close();
	fout.close();
	//temp.dat becomes the new notes.dat, removing all the targeted notes
	//in the process.
	remove("notes.dat");
	rename("temp.dat","notes.dat");
}

//Working, private method
void FileManager::clearBMs(Book b)
{
	//Reading from bookmarks.dat, temp.dat will have everything but the targeted
	//book's bookmarks writen to it.
	fin.open("bookmarks.dat");
	if(fin.fail())
	{
		fin.close();
		//No bookmarks to clear
		return;
	}
	fout.open("temp.dat");
	//Basic things needed.
	int i=0;
	string line;
	stringstream ss;
	//Loops through each of bookmarks.dat's lines.
	while((getline(fin,line)) && (line.compare("")!=0))
	{
		//Runs until it hits a semicolon, saving the title in the process
		//to a string stream.
		while(line.at(i)!=':')
		{
			ss << line.at(i);
			i++;
		}
		//Checks if the previously read title matches the target,
		//if they don't match, the targeted line IS written to temp.dat.
		if(b.getTitle().compare(ss.str()) != 0)
		{
			fout << line << endl;
		}
		//Reseting everything for the next line.
		ss.str("");
		ss.clear();
		i=0;
	}
	//Closing all file interfaces.
	fin.close();
	fout.close();
	//temp.dat becomes the new bookmarks.dat, removing all the targeted bookmarks
	//in the process.
	remove("bookmarks.dat");
	rename("temp.dat","bookmarks.dat");
}
