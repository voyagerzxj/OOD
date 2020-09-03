///////////////////////////////////////////////////////////////////////
// FindDuplicates.cpp - Find duplicate files                         //
//                      store each path and each filename only once  //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2014         //
///////////////////////////////////////////////////////////////////////
/*
 * Things to make this code more useful:
 * - use collection of path specifications with wild cards
 * - Error handling for inaccessible directories
 *
 * Required Files:
 * ---------------
 * FindDuplicates.cpp
 * FileSystem.h, FileSystem.cpp
 *
 * Maintenace History:
 * ver1.1 : 17 Apr 2019
 * - find using a collection of patterns like *.h, *.cpp, taken from command line
 * - checking to see if specified path exists, first argument on command line
 * - sort file names independent of case
 * Ver 1.0 : 04 Aug 2018
 * - First release
 */
#include "FileSystem.h"
#include <set>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>

using namespace FileSystem;

class Duplicates
{
public:
  using FilePath = std::string;
  using FilePaths = std::set<FilePath>;
  using PathCollection = std::list<FilePaths::iterator>;
  using FileName = std::string;
  using Files = std::vector<FileName>;
  using DuplicateFiles = std::map<FileName, PathCollection>;
  using Pattern = std::string;
  using Patterns = std::vector<Pattern>;

  DuplicateFiles findDuplicates(const FilePath& start);
  FilePaths& filePaths() { return paths; }
  void addPattern(const Pattern& pattern);
private:
  DuplicateFiles duplicates;
  DuplicateFiles::iterator hintDuplicatesIter;
  Files files;
  FilePaths paths;
  Patterns patterns;
  FilePaths::iterator hintPathsIter = begin(paths);
  DuplicateFiles find(const FilePath& start);  // find all files
};
//----< display current processing path >------------------------------

void showPath(const std::string& pathSpec)
{
  static size_t numDirs = 1;
  static std::string prevPath = " ";
  std::string showPath = pathSpec.substr(0, 70);
  std::cout << "\r" << std::string(prevPath.size() + 26, ' ');
  std::cout << "\r  " << numDirs++ << " directories: " << showPath.c_str();
  prevPath = showPath;
}
//----< convert string to lower case >---------------------------------

std::string toLower(const std::string& src)
{
  std::string temp = src;
  std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  return temp;
}
//----< add file pattern >---------------------------------------------

void Duplicates::addPattern(const Pattern& pattern)
{
  patterns.push_back(pattern);
}
//----< concatenate two File vectors >---------------------------------

Duplicates::Files operator+=(Duplicates::Files& f1, Duplicates::Files& f2)
{
  for (auto file : f2)
    f1.push_back(file);
  return f1;
}
//----< find all files on pathSpec >-----------------------------------

Duplicates::DuplicateFiles Duplicates::find(const FilePath& pathSpec)
{
  showPath(pathSpec);
  FilePath path = FileSystem::Path::getFullFileSpec(pathSpec);

  std::vector<FileName> localFiles;
  for (Pattern patt : patterns)
  {
    localFiles += Directory::getFiles(path, patt);
  }
  files += localFiles;

  // add path to paths

  FilePaths::iterator iter = paths.insert(hintPathsIter, path);
  hintPathsIter = iter;

  // add file and iterator to its path to duplicates

  for (auto file : localFiles)
  {
    std::string lowerCaseKey = toLower(file);
    if (duplicates.find(lowerCaseKey) != end(duplicates))
    {
      duplicates[lowerCaseKey].push_back(iter);
    }
    else
    {
      PathCollection paths;
      paths.push_back(iter);
      duplicates[lowerCaseKey] = paths;
    }
  }
  std::vector<FilePath> dirs = Directory::getDirectories(path, "*.*");
  for (auto dir : dirs)
  {
    if (dir != "." && dir != "..")
    {
      dir = path + "/" + dir;
      find(FileSystem::Path::getFullFileSpec(dir));
    }
  }
  return duplicates;
}
//----< find duplicate files on startSpec >----------------------------

Duplicates::DuplicateFiles Duplicates::findDuplicates(const FilePath& startSpec)
{
  FilePath start = FileSystem::Path::getFullFileSpec(startSpec);
  find(start);

  // find non-duplicates

  Files files;
  for (auto fileSpec : duplicates)
  {
    if (fileSpec.second.size() < 2)
      files.push_back(fileSpec.first);
  }
  // remove non-duplicates

  for (auto file : files)
    duplicates.erase(file);

  return duplicates;
}
//----< Demonstration >------------------------------------------------

void displayTitle(const std::string& title)
{
  std::string underline = std::string(title.size() + 2, '=');
  std::cout << "\n  " << title;
  std::cout << "\n " << underline << "\n";
}
//----< show user how to construct command line >----------------------

void showUsage()
{
  std::cout << "\n  FindDuplicates expects a path as first argument on command line";
  std::cout << "\n    You may supply a list of file patterns, e.g., \"*.h\" \"*.cpp\", ...";
  std::cout << "\n    If no patterns are supplied, FindDuplicates will use \"*.*\"";
}
//----< validate command line >----------------------------------------

bool processCommandLine(int argc, char* argv[])
{
  if (argc < 2)
  {
    showUsage();
    return false;
  }
  return true;
}
//----< begin processing >---------------------------------------------

int main(int argc, char* argv[])
{
  Duplicates dups;

  if (processCommandLine(argc, argv))
  {
    if (argc == 2)
    {
      dups.addPattern("*.*");
    }
    else
    {
      for (int i = 2; i < argc; ++i)
      {
        dups.addPattern(argv[i]);
      }
    }
  }
  else
  {
    return 1;
  }

  std::string pathSpec = FileSystem::Path::getFullFileSpec(argv[1]);
  std::string title = "Finding Duplicate Files on Path \"" + pathSpec + "\"";
  displayTitle(title);

  std::string startPath = argv[1];

  Duplicates::DuplicateFiles dupFiles = dups.findDuplicates(startPath);

  if (dupFiles.size() == 0)
  {
    std::cout << "\n  there are no duplicate files in directory rooted at";
    std::cout << "\n    " << FileSystem::Path::getFullFileSpec(startPath);
    return 0;
  }
  for (auto fileSpec : dupFiles)
  {
    std::cout << "\n  " << fileSpec.first;
    for (auto pathIter : fileSpec.second)
    {
      Duplicates::FilePath path = *pathIter;
      std::cout << "\n    " << path;
    }
  }
  std::cout << std::endl;
  std::cout << "\n  Total number of duplicate files = " << dupFiles.size();
  std::cout << "\n  Total number of paths = " << dups.filePaths().size();
  std::cout << "\n\n";
}