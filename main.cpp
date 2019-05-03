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


    ifstream inFile;
    vector <string> words;

        int i = 0;
        inFile.open("sm_doc_set\\abf0704.txt");

        if(!inFile) {
            cout << "TRAGIC\n";
            exit(-1);
        }

        string word;
        vector <char> wordholder;
        while(inFile >> word){
            wordholder.clear();
            for(int i = 0; i< word.size(); i++) {
                if (isalnum((int)word[i]) != 0) {
                    wordholder.push_back(word[i]);
                    cout<<"whileloop\n";
                }
                cout<<"forloop1\n";
            }

            cout<<"wordholder size\n"<<wordholder.size()<<"\n";
            word.resize(wordholder.size());
            for(int i = 0; i<wordholder.size(); i++){
                word[i] = wordholder[i];
                cout<<"forloop2\n";
            }


            words.push_back(word);
        }
        /*
        for(int i = 0; i < words.size(); i++){
            cout<<words[i]<<"\n";
        }
        */

    return 0;
}
