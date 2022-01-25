#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <stdexcept>
#include <chrono>
#include <vector>

#include "puzzle.hpp"

using namespace std::chrono;

void help()
{
  std::cout << "Usage: wordpuzzle [filename]\n"
            << "If file is not provided, reads stdin.\n";
}

int main(int argc, char *argv[])
{
  std::ifstream fin;

  try
  {
    // 1: Process argument

    if (argc == 2)
    {
      if (argv[1] == std::string("-h") || argv[1] == std::string("--help"))
      {
        help();
        return 0;
      }
      else
      {
        fin.open(argv[1]);
        if (fin.fail())
        {
          throw std::runtime_error(std::string("Failed to open file."));
        }
      }
    }

    // 2: Read input

    std::istream *in = &std::cin;

    if (fin.is_open())
    {
      in = &fin;
    }

    WordPuzzle puzzle(*in);

    std::vector<std::string> words;
    for (std::string word; std::getline(*in, word);)
    {
      if (!word.empty())
      {
        words.push_back(word);
      }
    }

    // 3: Find puzzle solution

    std::vector<WordPuzzleSolution> solutions;

    auto t1 = high_resolution_clock::now();

    for (const std::string &word : words)
    {
      solutions.push_back(puzzle.findWord(word));
    }

    auto t2 = high_resolution_clock::now();
    auto duration = t2 - t1;

    // 4: Print output

    puzzle.print();

    long long comps = 0;
    long long found = 0;
    for (const WordPuzzleSolution &solution : solutions)
    {
      comps += solution.compCount;
      solution.print();

      if (solution.type != SolutionType::None)
      {
        found++;
      }
    }

    if (fin.is_open())
    {
      fin.close();
    }

    std::cout << "Total words       : " << words.size()
              << " (found: " << found
              << ", not found: " << words.size() - found << ")\n"
              << "Total comparisons : " << comps << "\n"
              << "Total time taken  : "
              << duration_cast<nanoseconds>(duration).count()
              << " nanoseconds\n";
  }
  catch (std::exception &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "An unknown error occured.\n";
  }

  return 0;
}
