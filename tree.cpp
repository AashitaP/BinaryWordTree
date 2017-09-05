#include <iostream>
#include <string>
#include <cassert>
using namespace std;

typedef string ItemType;

struct WordNode {
    ItemType m_data;
    WordNode *m_left;
    WordNode *m_right;
    int count;// You may add additional data members and member functions in WordNode
    WordNode(ItemType data)
    {
        m_data = data;
        m_left = nullptr;
        m_right = nullptr;
        count = 1;
    }
};

class WordTree {
    
private:
    WordNode *root;
    void copyWordTree(WordNode* &thisroot, WordNode* rhsroot)
    {
        if (rhsroot == nullptr)
        {
            thisroot = nullptr;
            return;
        }
        
        thisroot = new WordNode(rhsroot -> m_data);
        thisroot -> count = rhsroot->count;
        copyWordTree(thisroot -> m_left, rhsroot -> m_left);
        copyWordTree(thisroot->m_right, rhsroot -> m_right);
    }
    
    int countDistinct(WordNode* n) const
    {
        if(n==nullptr)
            return 0;
        
        
        else
        {
            return countDistinct(n -> m_left) + countDistinct(n->m_right) + 1;
        }
    }
    
    void deleteSubTree(WordNode* n)
    {
        if(n== nullptr)
            return;
        deleteSubTree(n->m_left);
        deleteSubTree(n->m_right);
        delete n;
    }
    
    void printTree(ostream& out, WordNode* n) const
    {
        if(n== nullptr)
            return;
        else {
            printTree(out, n->m_left);
            out << n->m_data << " " << n->count << endl;
            printTree(out, n->m_right);
        }
    }
    
    int countTotal(WordNode* n) const
    {
        if(n== nullptr)
            return 0;
        else
            return countTotal(n->m_left) + countTotal(n->m_right) + n->count;
    }
    
public:
    
    // default constructor
    WordTree() : root(nullptr) { };
    
    // copy constructor
    WordTree(const WordTree& rhs)
    {
        if(rhs.root == nullptr)
        {
            root = nullptr;
            return;
        }
        
        else
            copyWordTree(root, rhs.root);
    }
    
    
    // assignment operator
    const WordTree& operator=(const WordTree& rhs)
    {
        if (this == &rhs)
            return *this;
        WordTree temp = rhs;
        WordNode* tempnode = root;
        root = temp.root;
        temp.root = tempnode;
        
        return *this;
    }
    
    // Inserts v into the WordTree
    void add(ItemType v)
    {
        if(root == nullptr)
        {
            root = new WordNode(v);
            return;
        }
        
        WordNode* cur = root;
        for(;;)
        {
            if (cur -> m_data == v)
            {
                cur -> count += 1;
                return;
            }
            
            else if(v < cur->m_data)
            {
                if(cur->m_left == nullptr)
                {
                    cur -> m_left = new WordNode(v);
                    return;
                }
                
                else
                {
                    cur = cur->m_left;
                }
            }
            
            else if(v > cur -> m_data)
            {
                if(cur->m_right == nullptr)
                {
                    cur -> m_right = new WordNode(v);
                    return;
                }
                
                else
                {
                    cur = cur->m_right;
                }
            }
        }
            
    }
    
    // Returns the number of distince words / nodes
    int distinctWords() const
    {
        return countDistinct(root);
    }
    
    // Returns the total number of words inserted, including duplicate
    // values
    int totalWords() const
    {
        return countTotal(root);
    }
    
    
    // Prints the LinkedList
    
    
   friend ostream& operator<<(ostream &out, const WordTree& rhs)
    {
        rhs.printTree(out, rhs.root);
        return out;
    }

   
    // Destroys all the dynamically allocated memory
    // in the tree.
    ~WordTree()
    {
        if(root == nullptr)
            return;
        deleteSubTree(root);
        
    }

};

int main()
{
    WordTree t;
    
    //checking add
    
    t.add("Skyler");
    t.add("Walter");
    t.add("Walter");
    t.add("Walter");
    
    //checking distinct & total
    
    assert(t.distinctWords() == 2);
    assert(t.totalWords() == 4);
    
    //checking copy constructor
    WordTree n(t);
    
    assert(n.distinctWords() == 2);
    assert(n.totalWords() == 4);
    
    //checking with empty
    WordTree k;
    WordTree l(k);
    
    assert(l.distinctWords() == 0);
    assert(l.totalWords() == 0);
    
    //checking assignment operator
    WordTree z;
    assert(z.distinctWords() == 0);
    assert(z.totalWords() == 0);
    
    z = t;
    
    assert(z.distinctWords() == 2);
    assert(z.totalWords() == 4);
    
    z.add("Water");
    assert(z.distinctWords() == 3);
    assert(z.totalWords() == 5);
    
    
    //checking print tree
    WordTree d;
    
    d.add("Skyler");
    d.add("Walter");
    d.add("Walter");
    d.add("Hank");
    d.add("Gus");
    d.add("Walter");
    d.add("Gus");
    
    cout << d << endl;
    
    cout << n << endl;
    cout << k << endl;
    cout << l << endl;
    cout << z << endl;
    
    //checking with empty
    
    z = k;
    assert(z.distinctWords() == 0);
    assert(z.totalWords() == 0);
    
}
