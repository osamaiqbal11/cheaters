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

int findfilenum(string filename, vector<string> files){
    int i = 0;
    while(filename != files[i]){
        i++;
    }
    return (i);
}

int main() {

    //Prompt Code
    //-------------------------------------------------------------------------
    int chunksize = 6;
    //-------------------------------------------------------------------------

    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();
    getdir(dir, files);
    for (unsigned int i = 0; i < files.size(); i++) {
        cout << i << files[i] << endl;
    }

    struct hashentry{
        string filename;
        hashentry *next;
    };

    //Initialize hash table here
    //--------------------------------------------------------------------------------------07
    int maxhash = 63999;
    hashentry *hashtable[maxhash];
    for(int m = 0; m<maxhash; m++){
        hashtable[m] = NULL;
    }
    //--------------------------------------------------------------------------------------07


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




        //chunking code goes here
        //--------------------------------------------------------------------------------------02
        string chunk;
        for(int i = 0; i < (words.size()-(chunksize-1)); i++) {

            for(int j = i; j < (i + chunksize); j++){
                chunk = chunk + words[j];
            }

            //A chunk is made
            //Hashing code goes here
            //--------------------------------------------------------------------------------------03
            int key = 0;
            for(int l = 0; l < (chunk.size()-1); l++){
                int twenthrees = 1;
                int index = 0;
                while(index<l){
                    twenthrees = twenthrees*23;
                    index++;
                }
                key = key + (chunk[chunk.size()-l-1]*twenthrees);
            }
            if(key < 1){
                key = key * -1;
            }
            /*
            int result = 1;
            for(int k = 0; k < chunk.size(); k = k+3){
                if((k%2) == 0){
                    result = (result * chunk[k])%213;
                }
                else if(k%3 == 0){
                    result = result - (chunk[k]%83);
                    if(result < 1){
                        result = result + (chunk[k]%83);
                    }
                }
                else{
                    result = result + chunk[k];
                }
            }
            int threes = 1;
            int hash = 0;
            hash = result%30;
            for(int k = 0; k < 8; k++){
                threes = threes* 3;
            }
            hash = hash * threes;
            hash = hash + (result%577);
            */
            key = key%maxhash;

            hashentry *temp = new hashentry;
            temp->next = NULL;
            temp->filename = files[k];
            if(hashtable[key] == NULL){
                hashtable[key] = temp;
            }
            else{
                hashentry *hold = hashtable[key];
                while( hold->next != NULL){
                    hold = hold->next;
                }
                hold->next = temp;
            }

            //--------------------------------------------------------------------------------------03
            chunk = "";
        }
        //--------------------------------------------------------------------------------------02
        inFile.close();
    }
    //-------------------------------------------------------------------------------------------00

    //2-D Array Code goes here
    //-------------------------------------------------------------------------------------------04
    int collisions[files.size()-1][files.size()];
    vector<string> chunkbros;
    for(int r = 0; r < maxhash; r++){
        if (hashtable[r] != NULL){
            if (hashtable[r]->next != NULL) {
                chunkbros.push_back(hashtable[r]->filename);
                hashentry *holder = hashtable[r]->next;
                while (holder != NULL) {
                    chunkbros.push_back(holder->filename);
                    holder = holder->next;
                }
                int x = 0;
                int y = 0;
                while
            }
        }

    }
    //-------------------------------------------------------------------------------------------04



    return 0;
}
