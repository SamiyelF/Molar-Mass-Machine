#include <string>
#include <vector>
#include <iostream>
#include <map>
using std::string;
using std::vector;
using std::map;



std::map<string, float> Table {
  {"H" ,   1.008},  {"He",   4.002},  {"Li",       7},  {"Be",   9.012},
  {"B" ,   10.81},  {"C" ,  12.011},  {"N" ,  14.007},  {"O" ,  15.999},
  {"F" ,  18.998},  {"Ne",  20.180},  {"Na",  22.989},  {"Mg",  24.305},
  {"Al",  26.981},  {"Si",  28.085},  {"P" ,  30.973},  {"S" ,   32.07},
  {"Cl",   35.45},  {"Ar",    39.9},  {"K" ,  39.098},  {"Ca",   40.08},
  {"Ti",  47.867},  {"V" ,  50.941},  {"Cr",  51.996},  {"Mn",  54.938},
  {"Fe",   55.84},  {"Co",  58.933},  {"Ni",  58.693},  {"Cu",   63.55},
  {"Ga",  69.723},  {"Ge",   72.63},  {"As",  74.921},  {"Se",   78.97},
  {"Kr",   83.80},  {"Rb",  85.468},  {"Sr",   87.62},  {"Y" ,  88.905},
  {"Nb",  92.906},  {"Mo",   95.95},  {"Tc",  96.906},  {"Ru",   101.1},
  {"Rh", 102.905},  {"Pd",  106.42},  {"Ag", 107.868},  {"Cd",  112.41},
  {"In", 114.818},  {"Sn",  118.71},  {"Sb", 121.760},  {"Te",   127.6},
  {"I" , 126.904},  {"Xe",  131.29},  {"Cs", 132.905},  {"Ba",  137.33},
  {"La", 138.905},  {"Ce", 140.116},  {"Pr", 140.907},  {"Nd",  144.24},
  {"Pm", 144.912},  {"Sm",   150.4},  {"Eu", 151.964},  {"Gd",   157.2},
  {"Tb", 158.925},  {"Dy", 162.500},  {"Ho", 164.930},  {"Er",  167.26},
  {"Tm", 168.934},  {"Yb",  173.05},  {"Lu", 174.966},  {"Hf",  178.49},
  {"Ta", 180.947},  {"W" ,  183.84},  {"Re", 186.207},  {"Os",   190.2},
  {"Ir",  192.22},  {"Pt",  195.08},  {"Au", 196.966},  {"Hg",  200.59},
  {"Tl", 204.383},  {"Pb",     207},  {"Bi", 208.980},  {"Po", 208.982},
  {"At", 209.987},  {"Rn", 222.017},  {"Fr", 223.019},  {"Ra", 226.025},
  {"Ac", 227.027},  {"Th", 232.038},  {"Pa", 231.035},  {"U" , 238.028},
  {"Np", 237.048},  {"Pu", 244.064},  {"Am", 243.061},  {"Cm", 247.070},
  {"Bk", 247.070},  {"Cf", 251.079},  {"Es", 252.083},  {"Fm", 257.095},
  {"Md", 258.098},  {"No", 259.101},  {"Lr", 266.120},  {"Rf", 267.122},
  {"Db", 268.126},  {"Sg", 269.128},  {"Bh", 270.133},  {"Hs", 269.133},
  {"Sc",  44.955},  {"Zn",    65.4},  {"Br",   79.90},  {"Zr",   91.22}
};

string fromto(string input, int from, int to) {
  if ( from != 0 ) {
    input.erase(0, from);
  }
  if ( to - from != input.size() ) {
    input.erase(to - from, input.size());
  }
  return input;
}
vector<string> breaker(std::string input) {
  vector<string> blocks;
  string block;
  vector<int> Capitals;

  if ( !isdigit(input[input.size() - 1]) ) {
    input += "1";
  }

  for ( int c = 0; c <= input.size(); c++ ) {
    if ( (65 <= (int) input[c] && (int) input[c] <= 90) ) {
      Capitals.push_back(c);
    }
  }
  Capitals.push_back(input.size());

  for ( int i = 0; i < Capitals.size() - 1; i++ ) {
    block = fromto(input, Capitals[i], Capitals[i + 1]);
    if ( !isdigit(block[block.size() - 1]) ) {
      block += "1";
    }
    blocks.push_back(block);
  }

  return blocks;
}

map<string, int> mapper(vector<string> in) {
  map<string, int> Count;
  for ( string item : in ) {
    for ( int i = 0; i < item.size(); i++ ) {
      if ( 48 <= item[i] && item[i] <= 57 ) {//is a number
        string tempa = item;
        string tempb = item;
        tempa.erase(i, item.size());
        tempb.erase(0, i);
        string Element = tempa;
        int Amount = std::stoi(tempb);
        Count[Element] = Amount;
        break;
      }
    }
  }
  return Count;
}
void TakeCompound(string in) {
  vector<string> blocks = breaker(in);
  bool valid = true;
  float grams = 0;
  int atoms = 0;
  map<string, int> thismap = mapper(blocks);
  if ( in == "A" || in == "a" ) {
    std::cout << "6.022 * 10^23";
    goto end;
  }
  for ( auto item : thismap ) {
    // for each item in the list, add the map value to a total.
    float blocksum = Table[item.first] * item.second;
    if ( blocksum == 0 ) {
      valid = false;
    }
    atoms += item.second;
    grams += blocksum;
  }
  if ( valid ) {
    if ( grams > 0 ) {
      std::cout << "grams per mole: " << grams;

    }
    else {
      std::cout << "INVALID INPUT, ONE OF THESE ELEMENTS DOES NOT EXIST OR IS TYPED INCORRECTLY" << std::endl <<
        "Input should be shown as ''NaCHO3'', not Na C H O3 or any other variant.";
    }
  }
  else {
    std::cout << "INVALID INPUT, ONE OF THESE ELEMENTS DOES NOT EXIST OR IS TYPED INCORRECTLY" << std::endl <<
      "Input should be shown as ''NaCHO3'', not Na C H O3 or any other variant.";
  }

end:
  std::cout << "\n\n\n";
}
int main() {
  std::cout << "Molar Mass Machine" << std::endl << "Type a molecule/element and get its molar mass!" << std::endl << "(c) Samiyel D Frazier, 2024\n\n\n";
  while ( 1 ) {
    string in;
    std::getline(std::cin, in);
    TakeCompound(in);
  }
}