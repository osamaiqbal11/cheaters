#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if(dirp->d_name[0] != '.')
            files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main() {
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();
    getdir(dir, files);
    for (unsigned int i = 0; i < files.size(); i++) {
        cout << i << files[i] << endl;
    }

    struct hashentry{
        string filename;
        int number;
        hashentry *next;
    };



    //This loop reads from every file
    //-------------------------------------------------------------------------------------------00
    ifstream inFile;
    vector <string> words;
    for(int k = 0; k < files.size(); k++) {
        string doublebackslash = "\\";
        string openme = dir + doublebackslash + files[k];
        inFile.open(openme);
        if (!inFile) {
            cout << "TRAGIC\n";
            exit(-1);
        }


        //This loop reads from a file and pushes every alpha numeric string in doc to words-vector
        //---------------------------------------------------------------------------------------01
        string word;
        vector<char> wordholder;
        while (inFile >> word) {
            wordholder.clear();
            for (int i = 0; i < word.size(); i++) {
                if (isalnum((int) word[i]) != 0) {
                    wordholder.push_back(word[i]);
                }
            }
            word.resize(wordholder.size());
            for (int i = 0; i < wordholder.size(); i++) {
                word[i] = wordholder[i];
            }
            words.push_back(word);
        }
        //--------------------------------------------------------------------------------------01
        //words-vector contains all words in one document
        //(DEBUG) Prints every word in file
        /*
        for (int i = 0; i < words.size(); i++) {
            cout << words[i] << "\n";
        }
        */


        //Initialize hash table here
        //--------------------------------------------------------------------------------------07
        int maxhash = 301149;
        hashentry *hashtable[maxhash];
        for(int i = 0; i<maxhash; i++){
            hashtable[i] = NULL;
        }
        //--------------------------------------------------------------------------------------07


        //chunking code goes here
        //--------------------------------------------------------------------------------------02
        string chunk;
        for(int i = 0; i < words.size(); i++) {

            for(int j = i; j < (i+6); j++){
                chunk = chunk + words[j];
            }

            //A chunk is made
            //Hashing code goes here
            //--------------------------------------------------------------------------------------03


            //--------------------------------------------------------------------------------------03
            chunk = "";
        }
        //--------------------------------------------------------------------------------------02



        inFile.close();
    }
    //-------------------------------------------------------------------------------------------00

    //2-D Array Code goes here
    //-------------------------------------------------------------------------------------------04
    //-------------------------------------------------------------------------------------------04



    return 0;
}
