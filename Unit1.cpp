//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
using namespace std;
void ScanFile(vector<UnicodeString>, map<int, vector<UnicodeString>>&);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{
	// Prompts user to open either a .cpp or .h file to scan
	OpenCodeFile->Filter = "CPP Code Files|*.cpp;*.h";
	if(OpenCodeFile->Execute())
	{
		// Clears any previous code placed in the boxes
		CodeBox->Lines->Clear();
		ErrorBox->Lines->Clear();

		// Creates a file reader to read each line from file
		TStreamReader* reader;
		reader = new TStreamReader(OpenCodeFile->FileName);

		// Vector holds code, and map holds error lines
		vector<UnicodeString> codeLines;
		map<int, vector<UnicodeString>> errorLines;

		// Holds line number
		UnicodeString count = 1;

		// Reads each line from file and adds it to code box and array
		for(int x = 1; !reader->EndOfStream; x++)
		{
			UnicodeString num = x;
			UnicodeString line = reader->ReadLine();
			CodeBox->Lines->Add(num + "    " + line);
			codeLines.push_back(line);
		}

		// File is scanned for errors
		ScanFile(codeLines, errorLines);

		// If no errors exist, tell the user. Otherwise, print all errors in map
		if (errorLines.empty())
			ErrorBox->Lines->Add(L"No errors have been found.");
		else
		{
			map<int, vector<UnicodeString>>::iterator idx;
			for(idx = errorLines.begin(); idx != errorLines.end(); ++idx)
			{
				UnicodeString num = idx->first;
				ErrorBox->Lines->Add(L"ERROR: Line " + num + " :");
				for (auto msg: idx->second)
					ErrorBox->Lines->Add(msg);
				ErrorBox->Lines->Add(" ");
            }
        }

	}

}
//---------------------------------------------------------------------------
void ScanFile(vector<UnicodeString> codeLines,
	 map<int, vector<UnicodeString>>& errorLines)
{
	// Stacks are used to find pairs for each symbol
	stack<int> paren;
	stack<int> curly;
	stack<int> singleQ;
	stack<int> doubleQ;
	stack<int> bracket;

	// Holds index of each line
	int idx = 1;

	// Used to check whether a single quote contains one char
	int checkSingle = 0;

	for (auto line: codeLines)
	{
		for (auto c: line)
		{
		   checkSingle++;   // Increments single value
			switch(c)
			{
				// Pushes index of error line and adds error if in parenthesis
				// If quotes are found, ignore
				case '{':
					if (singleQ.size() == 0 && doubleQ.size() == 0)
					{
						if (bracket.size() != 0)
							errorLines[idx].push_back("\"{\" found within \"[\"");
						if (paren.size() != 0)
							errorLines[idx].push_back("\"{\" found inside parenthesis");
						curly.push(idx);
					}
					break;

				// Pops index if pair found and adds error if in parenthesis
				// If quotes are found, ignore
				case '}':
					if (singleQ.size() == 0 && doubleQ.size() == 0)
					{
						if (bracket.size() != 0)
							errorLines[idx].push_back("\"}\" found within \"[\"");
						if (paren.size() != 0)
							errorLines[idx].push_back("\"}\" found inside parenthesis");
						if (curly.size() == 0)
							errorLines[idx].push_back("\"}\" has no match");
						curly.pop();
					}
					break;

				// Pushes index of error to stack
				// If quotes are found, ignore
				case '(':
					if (singleQ.size() == 0 && doubleQ.size() == 0)
						paren.push(idx);
					break;

				// Pops index if pair found and adds error if no pair is found
				// If quotes are found, ignore
				case ')':
					if (singleQ.size() == 0 && doubleQ.size() == 0)
					{
						if (paren.size() == 0)
							errorLines[idx].push_back("\")\" has no match");
						else
							paren.pop();
					}
					break;

				// Pushes index of error to stack
				// If quotes are found, ignore
				case '[':
					if (singleQ.size() == 0 && doubleQ.size() == 0)
						bracket.push(idx);
					break;

				// Pops index if pair found and adds error if no pair is found
				// If quotes are found, ignore
				case ']':
					if (singleQ.size() == 0 && doubleQ.size() == 0)
					{
						if (bracket.size() == 0)
							errorLines[idx].push_back("\"]\" has no match");
						else
							bracket.pop();
					}
					break;


				// Checks for single pair quotes and if more than one char is in quotes
				// If bracket is found, add error
				case '\'':
					if (bracket.size() != 0)
						errorLines[idx].push_back("' found within \"[\"");
					if (singleQ.size() == 0)
					{
						singleQ.push(idx);
						checkSingle = -2;
					}
					else
					{
						singleQ.pop();
						if (checkSingle > 0)
							errorLines[idx].push_back("' pair contains more than one char");
					}
					break;

				// Checks for double pair quotes
				// If bracket is found, add error
				case '"':
					if (bracket.size() != 0)
						errorLines[idx].push_back("\" found within \"[\"");
					if (doubleQ.size() == 0)
						doubleQ.push(idx);
					else
						doubleQ.pop();
					break;

			}
		}
		// If no other pair is found for ' symbol, add error
		if (singleQ.size() != 0)
			for (int x = 0; x < singleQ.size(); x++)
			{
				errorLines[singleQ.top()].push_back("' has no match");
				singleQ.pop();
			}

		// If no other pair is found for " symbol, add error
		if (doubleQ.size() != 0)
			for (int x = 0; x < doubleQ.size(); x++)
			{
				errorLines[doubleQ.top()].push_back("\" has no match");
				doubleQ.pop();
			}

		checkSingle = 0; // Resets single quote counter
		idx++;  // Increments line counter
	}

	// If no other pair is found for '(' symbol, add error
	if (paren.size() != 0)
		for (int x = 0; x < paren.size(); x++)
		{
			errorLines[paren.top()].push_back("\"(\" has no match");
			paren.pop();
		}

	// If no other pair is found for '{' symbol, add error
	if (curly.size() != 0)
		for (int x = 0; x < curly.size(); x++)
		{
			errorLines[curly.top()].push_back("\"{\" has no match");
			curly.pop();
		}

	// If no other pair is found for '[' symbol, add error
	if (bracket.size() != 0)
		for (int x = 0; x < bracket.size(); x++)
		{
			errorLines[bracket.top()].push_back("\"[\" has no match");
			bracket.pop();
		}
}

