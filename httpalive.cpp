#include <curl/curl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <omp.h>


#define NUM_THREADS 40

using namespace std;

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}


int main(int argc, char const *argv[] )
{
  


	if (argc < 2) cout << "Usage httplive <path to subdomains>" << endl;

	ifstream infile(argv[1]);
	string line;
	omp_set_num_threads(NUM_THREADS/2);
	ofstream out_file;
	out_file.open("out.txt");

	#pragma omp parallel
	{


		for (string line ; getline(infile, line); ) {

			CURL *curl = curl_easy_init();
			line = "http://" + line ;
			curl_easy_setopt(curl, CURLOPT_URL, const_cast<char*>(line.c_str()));
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L); 
			curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, 0L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);     
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
			curl_easy_setopt(curl, CURLOPT_COOKIE, "");
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
			auto res = curl_easy_perform(curl);


		if (res == CURLE_OK ) out_file << line << "\n";

		}
	}

	omp_set_num_threads(NUM_THREADS/2);

	infile.close();
	infile.clear(); 
	
	infile.open(argv[1]);
	
	#pragma omp parallel
	{
	

		for (string line ; getline(infile, line); ) {

			CURL *curl = curl_easy_init();
			line = "https://" + line ;
			curl_easy_setopt(curl, CURLOPT_URL, const_cast<char*>(line.c_str()));
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L); 
			curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, 0L);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);     
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
			curl_easy_setopt(curl, CURLOPT_COOKIE, "");
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
			auto res = curl_easy_perform(curl);
		
		if (res == CURLE_OK ) out_file << line << "\n";

		}
	}

	infile.close();
	infile.clear();

	out_file.close();

	return 0;
}