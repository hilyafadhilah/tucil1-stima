#include <iostream>
#include <cctype>
#include <stdexcept>

#include "puzzle.hpp"

static int countDigit(long long n)
{
  int count = 0;
  while (n != 0)
  {
    n = n / 10;
    ++count;
  }
  return count;
}

WordPuzzle::WordPuzzle(std::istream &in)
{
  char c;

  int colsize = -1;

  int i = 0;
  int j = 0;

  bool isEmptyLine = false;

  while (!isEmptyLine &&
         in >> std::noskipws >> c)
  {
    if (c == '\n')
    {
      if (j == 0)
      {
        isEmptyLine = true;
      }
      else
      {
        if (colsize < 0)
        {
          colsize = j;
        }
        else if (j != colsize)
        {
          throw std::runtime_error("Invalid input.");
        }

        j = 0;
        i++;
      }
    }
    else if (!std::isblank(c))
    {
      this->table[i][j] = c;
      j++;
    }
  }

  this->colsize = colsize;
  this->rowsize = i;
}

void WordPuzzle::print() const
{
  int titleLen = 10 + countDigit(this->rowsize) + countDigit(this->colsize);
  int colLen = (this->colsize * 3) - 1;
  if (colLen > titleLen)
  {
    std::cout << std::string((colLen - titleLen) / 2, ' ');
  }

  std::cout << " " << this->rowsize << " x " << this->colsize << " PUZZLE\n";

  for (int i = 0; i < this->rowsize; i++)
  {
    for (int j = 0; j < this->colsize; j++)
    {
      std::cout << ' ' << this->table[i][j] << ' ';
    }
    std::cout << '\n';
  }

  std::cout << std::endl;
}

WordPuzzleSolution WordPuzzle::findWord(std::string word) const
{
  WordPuzzleSolution solution(*this, word);

  if (word.empty())
    return solution;

  auto wordLen = word.size();

  for (int i = 0; i < this->rowsize; i++)
  {
    for (int j = 0; j < this->colsize; j++)
    {
      solution.compCount++;
      if (this->table[i][j] == word[0])
      {
        int k;

        // horizontal left-to-right
        k = 1;
        while (j + k < this->colsize && k < wordLen)
        {
          solution.compCount++;
          if (this->table[i][j + k] != word[k])
            break;

          k++;
        }

        if (k == wordLen)
        {
          solution.set(SolutionType::Left, i, j);
          return solution;
        }

        // horizontal right-to-left
        k = 1;
        while (j - k >= 0 && k < wordLen)
        {
          solution.compCount++;
          if (this->table[i][j - k] != word[k])
            break;

          k++;
        }

        if (k == wordLen)
        {
          solution.set(SolutionType::Right, i, j);
          return solution;
        }

        // vertical top-to-bottom
        k = 1;
        while (i + k < this->rowsize && k < wordLen)
        {
          solution.compCount++;
          if (this->table[i + k][j] != word[k])
            break;

          k++;
        }

        if (k == wordLen)
        {
          solution.set(SolutionType::Top, i, j);
          return solution;
        }

        // vertical bottom-to-top
        k = 1;
        while (i - k >= 0 && k < wordLen)
        {
          solution.compCount++;
          if (this->table[i - k][j] != word[k])
            break;

          k++;
        }

        if (k == wordLen)
        {
          solution.set(SolutionType::Bottom, i, j);
          return solution;
        }

        // diagonal top-left to bottom-right
        k = 1;
        while (i + k < this->rowsize &&
               j + k < this->colsize &&
               k < wordLen)
        {
          solution.compCount++;
          if (this->table[i + k][j + k] != word[k])
            break;

          k++;
        }

        if (k == wordLen)
        {
          solution.set(SolutionType::TopLeft, i, j);
          return solution;
        }

        // diagonal bottom-left to top-right
        k = 1;
        while (i - k >= 0 &&
               j + k < this->colsize &&
               k < wordLen)
        {
          solution.compCount++;
          if (this->table[i - k][j + k] != word[k])
            break;

          k++;
        }

        if (k == wordLen)
        {
          solution.set(SolutionType::BottomLeft, i, j);
          return solution;
        }

        // diagonal top-right to bottom-left
        k = 1;
        while (i + k < this->rowsize &&
               j - k >= 0 &&
               k < wordLen)
        {
          solution.compCount++;
          if (this->table[i + k][j - k] != word[k])
            break;

          k++;
        }

        if (k == wordLen)
        {
          solution.set(SolutionType::TopRight, i, j);
          return solution;
        }

        // diagonal bottom-right to top-left
        k = 1;
        while (i - k >= 0 &&
               j - k >= 0 &&
               k < wordLen)
        {
          solution.compCount++;
          if (this->table[i - k][j - k] != word[k])
            break;

          k++;
        }

        if (k == wordLen)
        {
          solution.set(SolutionType::BottomRight, i, j);
          return solution;
        }
      }
    }
  }

  return solution;
}

void WordPuzzleSolution::print() const
{
  std::cout << "> " << this->word << '\n';

  if (this->type == SolutionType::None)
  {
    std::cout << "Not found.\n";
  }
  else
  {
    std::cout << "Found with " << this->compCount << " comparisons.\n";

    if (this->type == SolutionType::Left)
    {
      int k = 0;
      for (int i = 0; i < this->puzzle.rowsize; i++)
      {
        for (int j = 0; j < this->puzzle.colsize; j++)
        {
          if (i == this->i &&
              j == this->j + k &&
              k < this->word.size())
          {
            std::cout << ' ' << this->word[k] << ' ';
            k++;
          }
          else
          {
            std::cout << " - ";
          }
        }
        std::cout << '\n';
      }
    }
    else if (this->type == SolutionType::Right)
    {
      int k = this->word.size() - 1;
      for (int i = 0; i < this->puzzle.rowsize; i++)
      {
        for (int j = 0; j < this->puzzle.colsize; j++)
        {
          if (i == this->i &&
              j + k == this->j &&
              k >= 0)
          {
            std::cout << ' ' << this->word[k] << ' ';
            k--;
          }
          else
          {
            std::cout << " - ";
          }
        }
        std::cout << '\n';
      }
    }
    else if (this->type == SolutionType::Top)
    {
      int k = 0;
      for (int i = 0; i < this->puzzle.rowsize; i++)
      {
        for (int j = 0; j < this->puzzle.colsize; j++)
        {
          if (i == this->i + k &&
              j == this->j &&
              k < this->word.size())
          {
            std::cout << ' ' << this->word[k] << ' ';
            k++;
          }
          else
          {
            std::cout << " - ";
          }
        }
        std::cout << '\n';
      }
    }
    else if (this->type == SolutionType::Bottom)
    {
      int k = this->word.size() - 1;
      for (int i = 0; i < this->puzzle.rowsize; i++)
      {
        for (int j = 0; j < this->puzzle.colsize; j++)
        {
          if (i + k == this->i &&
              j == this->j &&
              k >= 0)
          {
            std::cout << ' ' << this->word[k] << ' ';
            k--;
          }
          else
          {
            std::cout << " - ";
          }
        }
        std::cout << '\n';
      }
    }
    else if (this->type == SolutionType::TopLeft)
    {
      int k = 0;
      for (int i = 0; i < this->puzzle.rowsize; i++)
      {
        for (int j = 0; j < this->puzzle.colsize; j++)
        {
          if (i == this->i + k &&
              j == this->j + k &&
              k < this->word.size())
          {
            std::cout << ' ' << this->word[k] << ' ';
            k++;
          }
          else
          {
            std::cout << " - ";
          }
        }
        std::cout << '\n';
      }
    }
    else if (this->type == SolutionType::BottomLeft)
    {
      int k = this->word.size() - 1;
      for (int i = 0; i < this->puzzle.rowsize; i++)
      {
        for (int j = 0; j < this->puzzle.colsize; j++)
        {
          if (i == this->i - k &&
              j == this->j + k &&
              k < this->word.size())
          {
            std::cout << ' ' << this->word[k] << ' ';
            k--;
          }
          else
          {
            std::cout << " - ";
          }
        }
        std::cout << '\n';
      }
    }
    else if (this->type == SolutionType::TopRight)
    {
      int k = 0;
      for (int i = 0; i < this->puzzle.rowsize; i++)
      {
        for (int j = 0; j < this->puzzle.colsize; j++)
        {
          if (i == this->i + k &&
              j == this->j - k &&
              k < this->word.size())
          {
            std::cout << ' ' << this->word[k] << ' ';
            k++;
          }
          else
          {
            std::cout << " - ";
          }
        }
        std::cout << '\n';
      }
    }
    else if (this->type == SolutionType::BottomRight)
    {
      int k = this->word.size() - 1;
      for (int i = 0; i < this->puzzle.rowsize; i++)
      {
        for (int j = 0; j < this->puzzle.colsize; j++)
        {
          if (i == this->i - k &&
              j == this->j - k &&
              k < this->word.size())
          {
            std::cout << ' ' << this->word[k] << ' ';
            k--;
          }
          else
          {
            std::cout << " - ";
          }
        }
        std::cout << '\n';
      }
    }
  }

  std::cout << std::endl;
}
