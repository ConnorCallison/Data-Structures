#include <iostream>
#include <string>
#include <fstream>
#include <string>

using namespace std;

//This program creates a caeser cypher on an input string and given offset.

//Encodes character based on ASCII value
char encode_character(char character, int offset)
{
    char newchar = character;

    if(character >= 65 && character <= 90 )
    {
        for(int i = 0; i < offset; i++)
        {
            if(newchar == 90)
			{
        		newchar = 65;
			}
			else
            	newchar++;
        }

        return newchar;
    }
    else if(character >= 97 && character <= 122 )
        {
            for(int i = 0; i < offset; i++)
        {
        	if(newchar == 122)
			{
        		newchar = 97;
			}
			else
            	newchar++;
        }
            return newchar;
        }
    else
        return character;
}

string encode(string text, int offset)
{
    string newtext =text;

    for(int i=0; i<text.length(); i++)
    {
        newtext[i] = encode_character(text[i],offset);
    }

    return newtext;

}

int main()
{
    string infile;
    int offset = 0;
    string destname;
    int counter;
    cout << "Enter a file name to encode: " << endl;
    cin >> infile;
    cout << endl << "Enter an offset: " << endl;
    cin >> offset;
    cout << "Enter your destination file: " << endl;
    cin >> destname;

    ifstream input_file{infile};
    ofstream outfile (destname);
    
    if(offset < 0)
	{
    	offset = offset +26;
	}

    while(input_file.good() == true)
    {
        string current_line;
        getline(input_file,current_line);
        counter++;

        string encoded_text = encode(current_line,offset);
        if (outfile.is_open())
		{
			outfile << encoded_text + "\n";
		}
		else cout << "Unable to open file";
    }
     cout << endl << "Wrote" + to_string(counter) +" Lines.";
    return 0;
}
