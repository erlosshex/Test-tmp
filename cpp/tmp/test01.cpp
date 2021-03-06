#include <iostream>
#include <string>
#include <vector>


using namespace std;


int translate_char(char c){
  return c-'0';
}

char translate_int(int i){
  return '0'+i;
}

void divide_and_modular(vector<char> &my_v,vector<char> &d,vector<char> &m)
{
  if(my_v.empty())  return;
  int tmp_d=0;
  int tmp_m=0;
  int tmp=0;
  for(vector<char>::iterator i=my_v.begin();i!=my_v.end();++i){
    tmp=tmp_m*10+translate_char(*i);
    tmp_d=tmp/2;
    tmp_m=tmp%2;
    d.push_back(translate_int(tmp_d));
  }
  m.push_back(translate_int(tmp_m));
  while(d.front()=='0')  d.erase(d.begin());
}

void print_vector_char(const vector<char> &my_v)
{
  if(my_v.empty())  return;
  for(vector<char>::const_iterator i=my_v.begin();i!=my_v.end();++i)  cout<<*i;
}

int main(int argc, char **argv)
{
  string my_n;
  cin>>my_n;
  vector<char> my_v(my_n.begin(),my_n.end());

  vector<char> d;
  vector<char> m;

  divide_and_modular(my_v,d,m);

  cout<<"*******"<<endl;
  print_vector_char(my_v);
  cout<<endl;
  print_vector_char(d);
  cout<<"  ";
  print_vector_char(m);
  cout<<endl;
  
  //  cout<<my_n<<endl;
  return 0;
}
