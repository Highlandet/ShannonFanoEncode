#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

class Node
{
public:
	vector<pair<char, int>> Letters;
	string code;
    Node()
    {
        vector<pair<char, int>> VoidVector;
        this->Letters = VoidVector;
        this->code = "";
    }
    Node(vector<pair<char, int>> Letters, string code)
    {
        this->Letters = Letters;
        this->code = code;
    }
private:
};

string Creating()
{
	string str;
	getline(cin, str);
	return str;
}

map<char, int> Writing(string str)
{
    map<char, int> Dictio; //Table of symbols and their probabilities
    for (auto& sym : str)
        if (sym != ' ')
        {
            if (Dictio.count(sym) != 0) //If symbol has been already added into the table
                Dictio[sym]++;
            else Dictio.insert(make_pair(sym, 1)); //If symbol isn't added into the table
        }
    return Dictio;
}

Node MakingRoot(map<char, int> Dictio)
{
    vector<pair<char, int>> LettersList;
    for (auto& it : Dictio)
    {
        pair<char, int> tmp;
        tmp.first = it.first;
        tmp.second = it.second;
        LettersList.push_back(tmp);
    }
    sort(LettersList.begin(), LettersList.end(),
        [](const pair<char, int> a, const pair<char, int> b) -> bool { return a.second > b.second; });
    for (auto& it : LettersList)
    {
        cout << "[" << it.first << ", " << it.second << "]" << endl;
    }
    return Node(LettersList, "");
}

map<char, string> ShannonFanoTree(Node Initial)
{
    cout << endl;
    int DequeSize = Initial.Letters.size();
    deque<Node> Deque;
    vector<Node> Result;
    Deque.push_back(Initial);
    int counter = 0;
    while (Deque.size() != 0)
    {
        cout << "STEP #" << counter << endl << endl;
        if (Deque.front().Letters.size() == 1)
        {
            Result.push_back(Deque.front());
            Deque.pop_front();
        }
        else if (Deque.front().Letters.size() == 2)
        {
            string CodeBase = Deque.front().code;
            Node Left, Right;
            Left.code = CodeBase + "0";
            Right.code = CodeBase + "1";
            Left.Letters.push_back(Deque.front().Letters[0]);
            Right.Letters.push_back(Deque.front().Letters[1]);
            Result.push_back(Left);
            Result.push_back(Right);
            Deque.pop_front();
        }
        else
        {
            int lcs = 0, rcs = 0;
            Node Left, Right;

            for (auto& letter : Deque.front().Letters)
            {
                if (lcs >= rcs)
                {
                    Right.Letters.push_back(letter);
                    rcs += letter.second;
                }
                else
                {
                    Left.Letters.push_back(letter);
                    lcs += letter.second;
                }
            }
            string CodeBase = Deque.front().code;
            Left.code = CodeBase + "0";
            Right.code = CodeBase + "1";
            Deque.push_back(Left);
            Deque.push_back(Right);
            Deque.pop_front();
        }
        cout << "Deque: " << endl;
        for (auto& element : Deque)
        {
            for (auto& inner : element.Letters)
                cout << "{" << inner.first << ", " << inner.second << "}; ";
            cout << element.code << endl;
        }
        cout << endl << "Result: " << endl;
        for (auto& element : Result)
        {
            for (auto& inner : element.Letters)
                cout << "{" << inner.first << ", " << inner.second << "}; ";
            cout << element.code << endl;
        }
        cout << endl;
        counter++;
    }
    map<char, string> Dictio;
    for (auto& node : Result)
        Dictio.insert(make_pair(node.Letters[0].first, node.code));
    return Dictio;
}

string Encode(string Initial, map<char, string> CodeTable)
{
    string Ready = "";
    for (auto& letter : Initial)
    {
        if (letter != ' ')
            Ready += CodeTable[letter];
        else Ready += " ";
    }
    return Ready;
}

int32_t main(const int32_t argc, const int32_t* const argv[])
{
    string Getter = Creating();
    map<char, int> Dictio = Writing(Getter);
    
    cout << "Output string: " << Encode(Getter, ShannonFanoTree(MakingRoot(Dictio))) << endl;
}

