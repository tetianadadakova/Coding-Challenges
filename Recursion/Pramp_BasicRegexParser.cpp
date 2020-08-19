#include <iostream>
#include <string>

using namespace std;

bool isMatch(const std::string &text, const std::string &pattern);
bool isMatch(const std::string &text, const std::string &pattern, int ind_t, int ind_p) ;
void tests();

int main() {
  
  // Run function with different inputs
  tests();
  
  return 0;
}

bool isMatch(const std::string &text, const std::string &pattern) 
{
  int ind_t = 0;
  int ind_p = 0;
  return isMatch(text, pattern, ind_t, ind_p);
}

bool isMatch(const std::string &text, const std::string &pattern, int ind_t, int ind_p) 
{
  if (ind_t >= text.size() && ind_p >= pattern.size()) {
    // both the indices is outside of the corresponding strings
    return true;
  }
  
  if (ind_t >= text.size()) {
    // ind_t is outside of string: could be that "pattern" has * after, then ind_p will be removed
    if ((ind_p + 1) < (pattern.size()) && pattern[ind_p + 1] == '*') {
      return isMatch(text, pattern, ind_t, ind_p + 2); // skip ind_p and *
    } else {
      return false;
    }
  }

  if ((ind_p + 1) < (pattern.size()) && pattern[ind_p + 1] == '*') {
    if (text[ind_t] == pattern[ind_p] || pattern[ind_p] == '.') {
      return isMatch(text, pattern, ind_t + 1, ind_p);
    } else { // (text[ind_t] != pattern[ind_p]) 
      return isMatch(text, pattern, ind_t, ind_p + 2); // skip ind_p and *
    }
  }
  
  if (text[ind_t] == pattern[ind_p] ||  pattern[ind_p] == '.') {
    return isMatch(text, pattern, ind_t + 1, ind_p + 1);
  }
  
  return false;
  
}

void tests() {
  
  if (isMatch("", "") == false) { 
    std::cout << "isMatch(\"\", \"\") failed" << std::endl;
    return;
  }
  
  if (isMatch("", "a*") == false) {
    std::cout << "isMatch(\"\", \"a*\") failed" << std::endl;
    return;
  }
  
  if (isMatch("aa", ".") == true) {
    std::cout << "isMatch(\"aa\", \".\") failed" << std::endl;
    return;
  }
  
  if (isMatch("aa", ".*") == false) {
    std::cout << "isMatch(\"aa\", \".*\") failed" << std::endl;
    return;
  }
  
  if (isMatch("aab", "aa") == true) {
    std::cout << "isMatch(\"aab\", \"a\") failed" << std::endl;
    return;
  }
  
  if (isMatch("aa", "aa") == false) {
    std::cout << "isMatch(\"aa\", \"aa\") failed" << std::endl;
    return;
  }
  
  if (isMatch("aa", "a") == true) {
    std::cout << "isMatch(\"aa\", \"a\") failed" << std::endl;
    return;
  }
  
  if (isMatch("abc", "a.c") == false) {
    std::cout << "isMatch(\"abc\", \"a.c\") failed" << std::endl;
    return;
  }
  
  if (isMatch("abbb", "ab*") == false) {
    std::cout << "isMatch(\"abbb\", \"ab*\") failed" << std::endl;
    return;
  }
  
  if (isMatch("acd", "ab*c.") == false) {
    std::cout << "isMatch(\"acd\", \"ab*c.\") failed" << std::endl;
    return;
  }
  
  if (isMatch("abbdbb", "ab*d") == true) {
    std::cout << "isMatch(\"abbdbb\", \"ab*d\") failed" << std::endl;
    return;
  }
  
  if (isMatch("abaa", "a.*a*") == false) {
    std::cout << "isMatch(\"abaa\", \"a.*a*\") failed" << std::endl;
    return;
  }
  
  if (isMatch("xaabyc", "xa*b.c") == false) {
    std::cout << "isMatch(\"xaabyc\", \"xa*b.c\") failed" << std::endl;
    return;
  }
  
  if (isMatch("abcdefaa", "a.*a*") == false) {
    std::cout << "isMatch(\"abaa\", \"a.*a*\") failed" << std::endl;
    return;
  }
  
  if (isMatch("abbcccdddd", ".*.*.*.*") == false) {
    std::cout << "isMatch(\"abaa\", \"a.*a*\") failed" << std::endl;
    return;
  }
  
  std::cout << "All tests passed" << std::endl;
}


