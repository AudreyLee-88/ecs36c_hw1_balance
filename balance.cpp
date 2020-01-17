//
// Created by Audrey on 1/15/2020.
//

#include <iostream>
#include "StackAr.h"
#include <fstream>

int main(int argc, char** argv) {
    char prevBracket;
    char prev = 'a';
    char cur;
    int curLine = 1;
    int bracketRow;
    char unmatchedBrac;
    int unmatchedRow = 0;
    bool comment = false;
    StackAr<char> bracketList(100);
    StackAr<int> bracketLine(100);
    std::ifstream myFile(argv[1]);


    while(myFile >> std::noskipws >> cur){
        if (!comment){
            if (cur == '\n'){
                curLine++;

                // if the left side bracket is read, insert in into stack
            }else if (cur == '{' ||  cur == '[' || cur == '('){
                bracketList.push(cur);
                bracketLine.push(curLine);

                // if the right side bracket is read, check if it match with the recent inserted bracket
            }else if (cur == '}'){
                if (bracketList.isEmpty()){
                    std::cout << "Unmatched } on line #" << curLine << std::endl;
                    return 0;
                }
                prevBracket = bracketList.topAndPop();
                bracketRow = bracketLine.topAndPop();
                while(prevBracket != '{' && !bracketList.isEmpty()){
                    unmatchedBrac = prevBracket;
                    unmatchedRow = bracketRow;
                    if (bracketList.isEmpty()){
                        std::cout << "Unmatched } on line #" << curLine << std::endl;
                        return 0;
                    }
                    prevBracket = bracketList.topAndPop();
                    bracketRow = bracketLine.topAndPop();
                }
            }else if (cur == ']') {
                if (bracketList.isEmpty()){
                    std::cout << "Unmatched ] on line #" << curLine << std::endl;
                    return 0;
                }
                prevBracket = bracketList.topAndPop();
                bracketRow = bracketLine.topAndPop();
                while(prevBracket != '['){
                    unmatchedBrac = prevBracket;
                    unmatchedRow = bracketRow;
                    if (bracketList.isEmpty()){
                        std::cout << "Unmatched ] on line #" << curLine << std::endl;
                        return 0;
                    }
                    prevBracket = bracketList.topAndPop();
                    bracketRow = bracketLine.topAndPop();

                }

            }else if (cur == ')') {
                if (bracketList.isEmpty()){
                    std::cout << "Unmatched ) on line #" << curLine << std::endl;
                    return 0;
                }
                prevBracket = bracketList.topAndPop();
                bracketRow = bracketLine.topAndPop();
                while(prevBracket != '('){
                    unmatchedBrac = prevBracket;
                    unmatchedRow = bracketRow;
                    if (bracketList.isEmpty()){
                        std::cout << "Unmatched ) on line #" << curLine << std::endl;
                        return 0;
                    }
                    prevBracket = bracketList.topAndPop();
                    bracketRow = bracketLine.topAndPop();

                }

            }else if (cur == '*' && prev == '/'){
                bracketLine.push(curLine);
                bracketLine.push(curLine);
                bracketList.push(prev);
                bracketList.push(cur);
                comment = true;
            }
        }
        if (cur == '/' && prev == '*'){
            if (!comment){
                std::cout << "Unmatched */ on line #" << curLine << std::endl;
                return 0;
            }
            prevBracket = bracketList.topAndPop();
            bracketRow = bracketLine.topAndPop();
            if (prevBracket != '*'){
                std::cout << "Unmatched " << prevBracket << " on line #" << bracketRow << std::endl;
            }else{
                prevBracket = bracketList.topAndPop();
                bracketRow = bracketLine.topAndPop();
                if (prevBracket != '/') {
                    std::cout << "Unmatched " << prevBracket << " on line #" << bracketRow << std::endl;
                }
            }
            comment = false;

        }
        prev = cur;
    }


    if (unmatchedRow != 0){
        std::cout << "Unmatched " << unmatchedBrac << " on line #" << unmatchedRow << std::endl;
        return 0;
    }

    if (bracketList.isEmpty()){
        std::cout << "OK" << std::endl;
    }else{
        do{
            unmatchedBrac = bracketList.topAndPop();
            unmatchedRow = bracketLine.topAndPop();
        }while(!bracketList.isEmpty());
        if (unmatchedBrac == '/'){
            std::cout << "Unmatched /* on line #" << curLine << std::endl;
        }else{
            std::cout << "Unmatched " << unmatchedBrac << " on line #" << unmatchedRow << std::endl;
        }
    }

    return 0;
}