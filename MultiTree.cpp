/*
grandpa
.mom
..my brother
..me
...my daughter
...my son
..my sister
...my nephew
.my uncle
..uncle son
*/

struct TreeNode
{
    TreeNode *parent;
    std::vector<TreeNode*> childs;
    std::string name;
    
    TreeNode(const std::string &str, TreeNode *p = nullptr) : name(str), parent(p) {}
};

TreeNode* initTree()
{
    std::istringstream input;
    input.str("grandpa\n.mom\n..my brother\n..me\n...my daughter\n...my son\n..my sister\n...my nephew\n.my uncle\n..uncle son\n");
    
    std::string line;
    std::getline(input, line);
    
    auto root = new TreeNode(line);
    int prevLevel = 0;
    for (auto currNode = root; std::getline(input, line);)
    {
        auto pos = line.find_first_not_of(".");
        
        int currLevel = 0;
        if (pos != std::string::npos)
        {
            for (int i = 0; i < (int)pos; ++i)
            {
                if (line[i] == '.')
                    ++currLevel;
            }
        }
        
        TreeNode *node;
        if (currLevel > prevLevel)
        {
            if (currLevel - prevLevel > 1) // ignore this scenario
                continue;
            
            node = new TreeNode(line, currNode);
            currNode->childs.emplace_back(node);
        }
        else if (currLevel == prevLevel)
        {
            node = new TreeNode(line, currNode->parent);
            currNode->parent->childs.emplace_back(node);
        }
        else // currLevel < prevLevel
        {
            for (int i = 0, iEnd = prevLevel - currLevel; i < iEnd; ++i)
            {
                currNode = currNode->parent;
            }
            node = new TreeNode(line, currNode->parent);
            currNode->parent->childs.emplace_back(node);
        }
        
        currNode = node;
        prevLevel = currLevel;
    }
    
    return root;
}

std::vector<std::vector<TreeNode*>> BFS(TreeNode *root)
{
    if (root == nullptr) return {};
    
    std::vector<std::vector<TreeNode*>> result;
    std::vector<TreeNode*> level;
    
    std::queue<TreeNode*> Q;
    Q.push(root);
    Q.push(nullptr);
    
    while (!Q.empty())
    {
        auto node = Q.front();
        Q.pop();
        
        if (node == nullptr)
        {
            result.emplace_back(level);
            if (!Q.empty())
            {
                level.clear();
                Q.push(nullptr);
            }
        }
        else
        {
            level.emplace_back(node);
            if (!node->childs.empty())
            {
                for (auto && p : node->childs)
                {
                    Q.push(p);
                }
            }
        }
    }
    
    return result;
}

std::vector<TreeNode*> DFS(TreeNode *root)
{
    if (root == nullptr) return {};
    
    std::vector<TreeNode*> result;
    
    std::stack<TreeNode*> S;
    S.push(root);
    
    while (!S.empty())
    {
        auto node = S.top();
        S.pop();
    
        result.emplace_back(node);
        
        for (auto it = node->childs.crbegin(); it != node->childs.crend(); ++it)
        {
            S.push(*it);
        }
    }
    
    return result;
}

std::vector<TreeNode*> DFSSorted(TreeNode *root)
{
    if (root == nullptr) return {};
    
    std::vector<TreeNode*> result;
    
    std::stack<TreeNode*> S;
    S.push(root);
    
    while (!S.empty())
    {
        auto node = S.top();
        S.pop();
        
        result.emplace_back(node);
        
        if (!node->childs.empty())
        {
            std::sort(node->childs.begin(), node->childs.end(),
                      [](TreeNode* &a, TreeNode* &b){ return a->name < b->name; });

            for (auto it = node->childs.crbegin(); it != node->childs.crend(); ++it)
            {
                S.push(*it);
            }
        }
    }
    
    return result;
}


int main()
{
    auto root = initTree();

    std::cout << "\nBFS result: \n";
    auto bfsResult = BFS(root);
    for (auto && level : bfsResult)
    {
        for (auto && x : level)
        {
            std::cout << x->name << "; ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nDFS result: \n";
    auto dfsResult = DFS(root);
    for (auto && x : dfsResult)
    {
        std::cout << x->name << "\n";
    }
    
    std::cout << "\nDFS in sorted result: \n";
    auto dfsSortedResult = DFSSorted(root);
    for (auto && x : dfsSortedResult)
    {
        std::cout << x->name << "\n";
    }

    return 0;
}

/*
BFS result: 
grandpa; 
.mom; .my uncle; 
..my brother; ..me; ..my sister; ..uncle son; 
...my daughter; ...my son; ...my nephew; 

DFS result: 
grandpa
.mom
..my brother
..me
...my daughter
...my son
..my sister
...my nephew
.my uncle
..uncle son

DFS in sorted result: 
grandpa
.mom
..me
...my daughter
...my son
..my brother
..my sister
...my nephew
.my uncle
..uncle son
*/
