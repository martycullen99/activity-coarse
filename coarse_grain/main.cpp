#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>

#include "Dictionary.cpp"
#include "MyHashtable.cpp"



//Tokenize a string into individual word, removing punctuation at the
//end of words
std::vector<std::vector<std::string>> tokenizeLyrics(const std::vector<std::string> files) {
  std::vector<std::vector<std::string>> ret;

  for(auto filename : files) {
    //std::cout<<"reading "<<filename<<"\n";
    std::vector<std::string> my_vect;
    std::ifstream in (filename);

    std::string line;

    //For each line
    while (getline(in, line, '\n')) {
      //Skip all like starting with [
      if (line[0] == '[')
        continue;

      std::stringstream ssline (line);
      //For all words
      while (ssline) {
        std::string word;
        ssline >> word;
        if (ssline) {
          //remove punctuation at the end of word
          while (word.length() > 0
                 && std::ispunct(word[word.length() - 1])) {
            word.pop_back();
          }
          my_vect.push_back(word);
        }
      }
    }
    //std::cout<<"read "<<my_vect.size()<<" words\n";
    ret.push_back(my_vect);
  }
  return ret;
}

void pushFile(std::vector<std::string> words, Dictionary<std::string, int>& dict)
{
  dict.set("thing", 1);
}

void x(std::vector<std::string> words, Dictionary& dict)
{
  
}

int main(int argc, char **argv)
{
  if (argc < 4) {
    std::cerr<<"usage: ./main <sources> <testword> <threshold>"<<std::endl;
    return -1;
  }

  // Parse Command Line
  std::string source = argv[1];
  std::string testWord = argv[2];
  int32_t thresholdCount = std::stoi(argv[3]);

  // Obtain List of Files
  std::vector<std::string> files;
  std::ifstream in (source);
  std::string line;
  while (getline(in, line, '\n')) {
    files.push_back(line);
  }

  // Tokenize Lyrics
  auto wordmap = tokenizeLyrics(files);

  MyHashtable<std::string, int> ht;
  Dictionary<std::string, int>& dict = ht;



  // write code here
  std::cout << wordmap.front().front() << "\n";
  std::cout << wordmap.front()[1] << "\n";
  std::cout << wordmap[1][0] << "\n";
  
  std::vector<std::thread> mythreads;
  
  
  for (auto & f : wordmap)
    {
      //std::thread mythread(pushFile, f, dict);
      std::thread mythread(x, f, dict);
      mythreads.push_back(std::move(mythread));
    }

  for(auto & t : mythreads)
    {
      if (t.joinable())
	{
	  t.join();
	}
      else
	{
	  std::cout << "t is not joinable\n";
	}
    }
  






  // Check Hash Table Values 
  /* (you can uncomment, but this must be commented out for tests)
  for (auto it : dict) {
    if (it.second > thresholdCount)
      std::cout << it.first << " " << it.second << std::endl;
  }
  */

  // Do not touch this, need for test cases
  std::cout << ht.get(testWord) << std::endl;

  return 0;
}
