#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <omp.h>

using std::cout; using std::string; using std::endl;

string readFile(const string& path) {
    struct stat sb{};
    string res;

    FILE* file = fopen(path.c_str(), "r");
 
    stat(path.c_str(), &sb);
    res.resize(sb.st_size);
    fread(const_cast<char*>(res.data()), sb.st_size, 1, file);
    fclose(file);

    return res;
}

int main() {
    string filename("arquivos/Homo.txt");
    string content = readFile(filename);
  
	int n = content.length();
    
	char fita[n];
   	
	strcpy(fita,content.c_str());
    
    int TAM = n * 0.10;

    int inicio = 0; 

	#pragma omp parallel num_threads((n / TAM))
	{				
		#pragma omp critical 
		{
			for (int i = inicio; i < (inicio + TAM); i++) {			
		        switch (toupper(fita[i])) {
		            case 'A':
		                fita[i] = 'T';
		                break;
		            case 'C':
		                fita[i] = 'G';
		                break;
		            case 'T':
		                fita[i] = 'A';
		                break;
		            case 'G':
		                fita[i] = 'C';
		                break;
		        }
			}
		}					
		inicio += TAM;	
	}

}
