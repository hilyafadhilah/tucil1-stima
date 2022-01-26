#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#define PUZZLE_MAX_SIZE 999

class WordPuzzleSolution;

class WordPuzzle
{
public:
  int colsize, rowsize;
  char table[PUZZLE_MAX_SIZE][PUZZLE_MAX_SIZE];
  WordPuzzle(std::istream &in);
  WordPuzzleSolution findWord(std::string word) const;
  void print() const;
};

enum class SolutionType
{
  Left,
  Right,
  Top,
  Bottom,
  TopLeft,
  TopRight,
  BottomLeft,
  BottomRight,
  None
};

class WordPuzzleSolution
{
  const WordPuzzle &puzzle;
  std::string word;

public:
  SolutionType type = SolutionType::None;
  int i, j;
  long long compCount = 0;

  WordPuzzleSolution(const WordPuzzle &p, std::string w)
      : puzzle(p)
  {
    this->word = w;
  }

  void set(SolutionType t, int i, int j)
  {
    this->type = t;
    this->i = i;
    this->j = j;
  }

  void print() const;
};

#endif
