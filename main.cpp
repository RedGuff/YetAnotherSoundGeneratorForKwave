#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;
// Kwave. // http://kwave.sourceforge.net/doc/en/open_and_save.html#ascii_format
// Un mot de 24 bits peut stocker 2^24 valeurs différentes, soit de -8 388 608 à +8 388 608 valeurs.

int main() {
    srand(time(NULL));       // No need for better init.
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string path = ""; // RAMDrive.
    string name1 = "sound";
    string file = path + name1 + ".ascii";
    int lengh = 88200;
//    https://julie2almeida.wixsite.com/tpe-effetsondesonore/enveloppe
    clog << "lengh: " << lengh << endl;
    int attackLenght = lengh / 10;
    clog << "attackLenght: " << attackLenght << endl;
    int sustain1Lenght =  lengh / 20;
    clog << "sustain1Lenght : " << sustain1Lenght  << endl;
    int decayLenght = lengh / 15;
    clog << "decayLenght : " << decayLenght  << endl;
    int sustain2Lenght = lengh / 2;
    clog << "sustain2Lenght : " << sustain2Lenght  << endl;
    int releaseLenght = lengh - sustain2Lenght - decayLenght - sustain1Lenght - attackLenght;
    clog << "releaseLenght : " << releaseLenght  << endl;
    ofstream outfile(file.c_str(), ios_base::app);
    if(!outfile) {
        cerr << "Error: Impossible to write in the file " << file << "!" << endl;
        return -1;
        }
    else {
        outfile << "## 'rate'=44100" << endl;
        outfile <<  "## 'tracks'=1" << endl;
        outfile <<  "## 'bits'=24" << endl;
        outfile <<  "## 'length'=";
        outfile << lengh << endl;
        outfile << "## 'Date'='";
        outfile << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" <<  ltm->tm_mday << "'" << endl;
        // time?
        outfile << "## 'Software'='Yet Another Sound Generator for Kwave 0.1'" << endl;
        int value = 0;
        for(int sample = 0; sample < lengh; sample++) {
            // "For" for multippes channels.
            // Modif de précédent : valeur absolue diminuée :
            if(value < 0) {
                value = value  + 1;
                }
            else {
                value = value   - 1;
                }
            value = value + rand() % 42 - 21; //
            outfile << value << "\t#\t" << sample << endl;
            }
        outfile << "# EOF";
        outfile.close();
        }
    string cde = "kwave " + path + name1 + ".ascii " + path + name1 + ".wav";
//    system(cde);
    cout << "Ok !" << endl;
    return 0;
    }
