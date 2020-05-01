#include <curl/curl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>


using namespace std;

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}

void Test(CURL *c, string url, bool Flag);


int main(int argc, char const *argv[] )
{
  CURL *curl = curl_easy_init();

  ifstream http(argv[1]);
  string line;
  
  while (getline(http, line)){
      thread t1(Test,curl, line, true);
      thread t2(Test, curl, line, false);
      t1.join();
      t2.join();

  }


  curl_easy_cleanup(curl);
  return 0;
}

void Test(CURL *curl, string line,  bool Flag){
    
    
    CURLcode res;
    if (curl) {

      line = Flag ?  "https://" + line : "http://"+ line;
      curl_easy_setopt(curl, CURLOPT_URL, const_cast<char*>(line.c_str()));
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
      res = curl_easy_perform(curl);
      if (res == CURLE_OK || res == 2) cout << line << endl;

  }

}


