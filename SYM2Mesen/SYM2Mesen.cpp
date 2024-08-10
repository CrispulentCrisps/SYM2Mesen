//
// Copyright 2024 Crisps
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
// associated documentation files(the “Software”), to deal in the Software without restriction, including without 
// limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the 
// Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of 
// the Software. //THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT 
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
// IN THE SOFTWARE.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
	string argument = argv[1];
	fstream File;
	ofstream Output;
	File.open(argument, ios_base::in);
	Output.open(argv[2], ios_base::out);
	string CurrentLine;
	bool InLabels = false;
	while (getline(File, CurrentLine))
	{
		if (CurrentLine.size() == 0)
		{
			continue;
		}
		if (CurrentLine[0] == ';')
		{
			continue;
		}
		if (CurrentLine[0] == '[')
		{
			if (CurrentLine == "[labels]")
			{
				InLabels = true;
			}
			else if (InLabels)
			{
				break;
			}
		}

		if (InLabels)
		{
			if (CurrentLine.rfind("00:", 0) == 0)
			{
				string ProcessedName = CurrentLine.substr(8);
				replace(ProcessedName.begin(), ProcessedName.end(), ':', '_');
				replace(ProcessedName.begin(), ProcessedName.end(), '.', '_');
				if (ProcessedName.rfind("DSP_", 0) == 0 || ProcessedName.rfind("HW_", 0) == 0)
				{
					continue;
				}
				Output << "SpcRam:00" << CurrentLine.substr(3, 4) << ":" << ProcessedName << "\n";
			}
		}
	}

	Output.close();
	File.close();
}