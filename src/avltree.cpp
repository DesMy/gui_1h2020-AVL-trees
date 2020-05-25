#include "avltree.h"

AvlTree::AvlTree(QString const &new_key)
{
    left = right = NULL;
    key = new QString(new_key);
    height = 1;
}

unsigned char height(AvlTree *root)
{
    return root?root->height:0;
}

int bfactor(AvlTree *root)
{
    return height(root->right) - height(root->left);
}

void fixheight(AvlTree *root)
{
    unsigned char left_h = height(root->left);
    unsigned char right_h = height(root->right);
    root->height = std::max(left_h, right_h) + 1;
}

void print_tree(AvlTree *root, QString &str, int level, bool right)
{
    if(root)
    {
        if(!right)
        {
            if(level!= 0)
                str += "\t";
            str += root->key;
        }
        else
        {
            str += "\n";
            for(int i = 0; i < level; ++i)
                str += "\t";
            str += root->key;
        }
        print_tree(root->left, str, level + 1, false);
        print_tree(root->right, str, level + 1, true);
    }
}

AvlTree *rotate_right(AvlTree *root)
{
    AvlTree *left = root->left;
    root->left = left->right;
    left->right = root;
    fixheight(root);
    fixheight(left);
    return left;
}

AvlTree *rotate_left(AvlTree *root)
{

    AvlTree *right = root->right;
    root->right = right->left;
    right->left = root;
    fixheight(root);
    fixheight(right);
    return right;
}

AvlTree *balance(AvlTree *root)
{
    fixheight(root);
    //Правое поддерево больше, чем левое
    if(bfactor(root) == 2)
    {
        if(bfactor(root->right) < 0)
            root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    //Левое поддерево больше, чем правое
    if(bfactor(root) == -2)
    {
        if(bfactor(root->left) > 0)
            root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    return root;
}

void insert(AvlTree **root, QString const &new_key)
{
    if(!*root)
        *root = new AvlTree(new_key);
    if(new_key < *(*root)->key)
        insert(&(*root)->left, new_key);
    else if(new_key > *(*root)->key)
        insert(&(*root)->right, new_key);
    *root = balance(*root);
}

AvlTree *find_min(AvlTree *root)
{
    if(!root->left)
        return root;
    else
        return find_min(root->left);
}

AvlTree *remove_min(AvlTree *root)
{
    if(root->left == NULL)
        return root->right;
    root->left = remove_min(root->left);
    return balance(root);
}

void remove_key(AvlTree **root, QString &key)
{
    if(!*root)
        return;
    if(key < *(*root)->key)
        remove_key(&(*root)->left, key);
    else if(key > *(*root)->key)
        remove_key(&(*root)->right, key);
    //key == (*root)->key
    else
    {
        AvlTree *left = (*root)->left;
        AvlTree *right = (*root)->right;
        delete *root;
        if(!right)
        {
            *root = left;
            return;
        }
        AvlTree *min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        *root = balance(min);
    }
    *root = balance(*root);
}

void create_tree_by_file(AvlTree **root, QString const &filename)
{
    QFile f(filename);
    if(f.exists() && f.open(QIODevice::ReadOnly))
    {
        char c;
        QString new_key;
        while(!f.atEnd())
        {
            f.read(&c, 1);
            if(isalpha(c) || isdigit(c))
                new_key += c;
            if(c == ' ')
            {
                while(c == ' ' && !f.atEnd())
                   f.read(&c, 1);
                insert(root, new_key);
                new_key = c;
            }
            if(f.atEnd() && new_key!= "")
                insert(root, new_key);
        }
    }
}
