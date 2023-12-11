// file stapel.cc
#include <iostream>
#include "stapel.h"

using namespace std;

// initializatie static ints zodat ze ge reassigned kunnen worden na 
// declaratie hoogte en breedte in hoofd.cc
int stapel::breedte = 0;
int stapel::hoogte = 0;

void stapel::reset() {
  for (int i = 0; i < 400; i++) {
    arr[i] = 0;
  }
  plek = 0;
  
}//stapel::reset()

void stapel::voegZetToe(int kolom) {
  arr[plek] = kolom;
  plek++;

}//stapel::voegZetToe(int kolom)

void stapel::printArray() {
  for (int i = 0; i < (hoogte*breedte); i++) {
    cout << "[ " << arr[i] << " ]" << " ";
  }
  cout << '\n';

}//stapel::voegZetToe(int kolom)

int stapel::neemZetTerug() {

  if (plek > 0) {
    plek--;
    int vorigeKolom = arr[plek];
    arr[plek] = 0;
  
    return vorigeKolom;
  } else {
    cout << "Bord is leeg! \n";
    return -1;
  }
}//stapel::neemZetTerug()