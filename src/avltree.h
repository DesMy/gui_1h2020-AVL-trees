#ifndef AVLTREE_H
#define AVLTREE_H
#include <QString>
#include <algorithm>
#include <QFile>
#include <cctype>
#include <QDebug>

struct AvlTree
{
    QString *key;
    AvlTree *left;
    AvlTree *right;
    unsigned char height;
    AvlTree(QString const &new_key);
};

unsigned char height(AvlTree *root);
int bfactor(AvlTree *root);
void fixheight(AvlTree *root);
AvlTree *rotate_right(AvlTree *root);
AvlTree *rotate_left(AvlTree *root);
AvlTree *balance(AvlTree *root);
void insert(AvlTree **root, QString const &new_key);
void print_tree(AvlTree *root, QString &str, int level, bool right);
void create_tree_by_file(AvlTree **root, QString const &filename);
AvlTree *find_min(AvlTree *root);
AvlTree *remove_min(AvlTree *root);
void remove_key(AvlTree **root, QString &key);
#endif // AVLTREE_H
