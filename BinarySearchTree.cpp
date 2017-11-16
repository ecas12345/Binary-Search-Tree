#include <iostream>
#include <string>
#include<queue>
#include <algorithm>

using namespace std;

class wordbstnode
{
public:
    string word;
    string explaination;
    wordbstnode * lcp; // leftchild;
    wordbstnode * rcp; // rightchild;

    wordbstnode(string pw, string pe)
    {
        word = pw;
        explaination = pe;
        lcp = rcp = nullptr;
    }

    wordbstnode()
    {
        lcp = rcp = nullptr;
    }
    ~wordbstnode()
    {
        delete lcp;
        delete rcp;
    }
};

class dictionarybst
{

public:
    wordbstnode * root;

    dictionarybst()
    {
        root = nullptr;

    }

    void dftinorder(wordbstnode *r)
    {
        if (r == nullptr) return;
        dftinorder(r->lcp);
        cout << r->word << ": " << r->explaination << endl;
        dftinorder(r->rcp);
    }
    void breadthFirst(wordbstnode * r)
    {
        queue<wordbstnode*> q;

        if (root) {
            q.push(root);
        }
        while (!q.empty())
        {
            const wordbstnode * const newNode = q.front();
            q.pop();
            cout << newNode->word << ": " << newNode->explaination << endl;

            if (newNode->lcp) {
                q.push(newNode->lcp);
            }
            if (newNode->rcp) {
                q.push(newNode->rcp);
            }
        }
    }
    void preorder(wordbstnode* r)
    {
        if (r != NULL)
        {
            cout << r->word << ": " << r->explaination << endl;
            preorder(r->lcp);
            preorder(r->rcp);
        }
        else return;
    }
    void postorder(wordbstnode* r)
    {
        if (r != NULL)
        {
            postorder(r->lcp);
            postorder(r->rcp);
            cout << r->word << ": " << r->explaination << endl;
        }
        else return;
    }
    ~dictionarybst()
    {
        delete root;
    }

    wordbstnode * search(string word)
    {
        transform(word.begin(), word.end(), word.begin(), toupper);
        wordbstnode * agent;
        agent = root;

        while (agent != nullptr)
        {
            if (word == agent->word)
            {
                return agent;
            }
            else
                if (word < agent->word)
                {
                    agent = agent->lcp;
                }

                else
                {
                    agent = agent->rcp;
                }
        }
        
        return nullptr;
    }

    void insert(string pw, string pe)
    {
        transform(pw.begin(), pw.end(), pw.begin(), toupper);
        wordbstnode *newword = new wordbstnode(pw, pe);
        wordbstnode * agent;
        wordbstnode * parent = nullptr;
        char whichbranch = '?'; //true for left, false for right

        if (root == nullptr)
        {
            root = newword;  // special case.
            return;
        }

        agent = root;
        while (agent != nullptr)
        {
            if (pw == agent->word)
                return;
            else
            {
                parent = agent;

                if (pw < agent->word)
                {
                    whichbranch = 'l';
                    agent = agent->lcp;
                }
                else
                {
                    whichbranch = 'r';
                    agent = agent->rcp;
                }
            }
        }

        if (whichbranch == 'l')
            parent->lcp = newword;
        else
            parent->rcp = newword;

    }

};


int main()
{
    

    dictionarybst bst;
    string word;
    string explanation;

    char answer = 'y';
    int choice;

    do
    {
        cout << "Please choose an operation from the following menu." << endl;
        cout << "1. add a new word\n"
            << "2. seach a word\n"
            << "3. breadth first traversal\n"
            << "4. depth first traversal (pre order)\n"
            << "5. depth first traversal (in order)\n"
            << "6. depth first traversal (post order)\n"
            << "7. Exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter a word: ";
            cin.ignore();
            getline(cin, word);
            cout << "Enter a explanation: ";
            cin.ignore();
            getline(cin, explanation);
            wordbstnode * wbst = new wordbstnode(word, explanation);
            bst.insert(word, explanation);
        }
        if (choice == 2)
        {
            cout << "What word are you searching for? :" << endl;
            cin >> word;
            wordbstnode * searchResults;
            searchResults = bst.search(word);
            if (searchResults == NULL)
            {
                cout << "Word isnt in the tree!" << endl;
            }
            else
                cout << searchResults->word << ": " << searchResults->explaination << endl;
        }
        if (choice == 3)
        {
            bst.breadthFirst(bst.root);
        }
        if (choice == 4)
        {
            bst.preorder(bst.root);
        }
        if (choice == 5)
        {
            bst.dftinorder(bst.root);
        }
        if (choice == 6)
        {
            bst.postorder(bst.root);
        }
        if (choice == 7)
        {
            cout << "Program terminated.";
            break;
        }

        cout << "Would you like to do another option? (y for yes, n for no.): " << endl;
        cin >> answer;
    } while (answer == 'y');

    return 0;
}
