
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

class deList;

const int N_PLAYERS=473;
const long long LAST_MARBLE=7090400;

deList* head;

class deList
{
public:
  long long identifier;
  deList* nextP;
  deList* prevP;


    deList(long long n, deList* nextT=nullptr, deList* prevT=nullptr): identifier(n), nextP(nextT), prevP(prevT){};

    void addNext(deList* elem)
    {
      elem->nextP=this->nextP;
      elem->prevP=this;
      this->nextP->prevP=elem;
      this->nextP=elem;

    }
    void removeElem()
    {
      prevP->nextP=nextP;
      nextP->prevP=prevP;
      if (this==head)
        head=nextP;
    }

  deList* advanceN(long long n)
  {
    if (n==0)
      return this;
    else if (n>0 && nextP!=nullptr)
      return nextP->advanceN(n-1);
    else if (n<0)
      return this->retreatN(-n);


  }

  deList* retreatN(long long n)
  {
    if (n==0)
      return this;
    else if (n>0 && prevP!=nullptr)
      return prevP->retreatN(n-1);
    else if (n<0)
      return this->advanceN(-n);

  }

};


void printList(deList* firstMarble, deList* currentMarble, long long n_marbles, long long max_marbles)
{
  if (firstMarble==currentMarble)
    cout << "(" << firstMarble->identifier << ") ";
  else
    cout << firstMarble -> identifier<<" ";

  if (n_marbles<max_marbles)
    printList(firstMarble->nextP, currentMarble, n_marbles+1, max_marbles);
}

int main()
{
  deList* currentMarble=nullptr;

  auto players=vector<long long>(N_PLAYERS,0);


  long long totMarbles=1;
  currentMarble= new deList(0);
  head=currentMarble;
  currentMarble->nextP=currentMarble->prevP=currentMarble;
  for (long long i=1,  p=0; i<=LAST_MARBLE; ++i, p=(p+1)%N_PLAYERS)
    {
      if (i%23) /* Regular case */
        {
          deList* newMarble=new deList(i);
          auto temp=currentMarble->advanceN(1);
          temp->addNext(newMarble);
          currentMarble=newMarble;
          totMarbles++;
        }
      else
        {
          players[p]+=i;
          auto temp=currentMarble->retreatN(7);
          players[p]+=temp->identifier;
          currentMarble=temp->nextP;
          temp->removeElem();
          if (temp==head)
            head=head->nextP;
          free (temp);
          totMarbles--;
        }
      // Uncomment this to print the list at each iteration
      //   printList(head,currentMarble,1, totMarbles);
      //    cout << endl;
    }

  cout << *(std::max_element(players.begin(),players.end()))<<endl;
}
