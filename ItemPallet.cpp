#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "ItemPallet.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int sku)
{
  return (sku / 100000 % 10);
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int sku)
{
  return (sku / 10000 % 10);
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int sku)
{
  return (sku / 1000 % 10);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int sku)
{
  return (sku / 100 % 10);
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int sku)
{
  return (sku / 10 % 10);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int sku)
{
  return (sku / 1 % 10);
}

// Constructor for struct Item
Item::Item(string itemName, unsigned int sku) : itemName_(itemName), sku_(sku){};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void ItemPallet::readTextfile(string filename)
{
  ifstream myfile(filename);

  if (myfile.is_open())
  {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    unsigned int sku;
    while (myfile >> itemName >> sku)
    {
      if (itemName.size() > 0)
        addItem(itemName, sku);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void ItemPallet::addItem(string itemName, unsigned int sku)
{
  Item item(itemName, sku);
  hT1.insert(std::make_pair(sku, item));
  hT2.insert(std::make_pair(sku, item));
  hT3.insert(std::make_pair(sku, item));
  hT4.insert(std::make_pair(sku, item));
  hT5.insert(std::make_pair(sku, item));
  hT6.insert(std::make_pair(sku, item));
}

bool ItemPallet::removeItem(unsigned int sku)
{
  // TODO: implement this function, then delete the return statement below

  // function that removes the pair of glasses specified by the sku from the display
  // if pair is found, then it is removed and the function returns true
  // else returns false
  auto it = hT1.find(sku);
  if (hT1.find(sku) != hT1.end())
  {
    hT1.erase(sku);
    hT2.erase(sku);
    hT3.erase(sku);
    hT4.erase(sku);
    hT5.erase(sku);
    hT6.erase(sku);
  }
  return true;
}

unsigned int ItemPallet::calc_balance(CustomHashTable h)
{
  unsigned int max = h.bucket_size(0);
  unsigned int min = h.bucket_size(0);
  unsigned int balance = 0;
  for (unsigned int i = 0; i < 10; ++i)
  {
    if (min > h.bucket_size(i))
      min = h.bucket_size(i);
    if (max < h.bucket_size(i))
      max = h.bucket_size(i);
  }
  return (max - min);
}

unsigned int ItemPallet::bestHashing()
{
  // function that decides the best hash function, i.e. the ones among
  // fct1-fct6 that creates the most balanced hash table for the current
  // ItemPallet data member allItems
  unsigned int best = 0;
  unsigned int h[]{
      calc_balance(hT1), calc_balance(hT2), calc_balance(hT3),
      calc_balance(hT4), calc_balance(hT5), calc_balance(hT6)};
  // Hints:
  // Calculate the balance of each hashtable, one by one.
  for (unsigned int i = 1; i < 6; i++)
  {
    if (h[best] > h[i])
      best = i;
  }
  // Then, calculate the lowest balance
  return best + 1;
}

// ALREADY COMPLETED
size_t ItemPallet::size()
{
  if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size()) || (hT1.size() != hT6.size()))
    throw std::length_error("Hash table sizes are not the same");

  return hT1.size();
}
