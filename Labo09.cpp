#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

struct node{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root){
    if (root != NULL){
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

void preorder(struct node *root){
    if (root != NULL){
        printf("%d \n", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void subDelete(struct node* root, int key, int flag){
    if(flag == 1){
        if(root->left->left != NULL){
            free(root->left);
            if(root->left->right != NULL) root->left->left->right = root->left->right;
            root->left = root->left->left;
        }
        else{
            free(root->left);
            if(root->left->right != NULL and root->left->right->key < root->key) root->left = root->left->right;
        }
    }
    else{
        if(root->right->left != NULL){
            free(root->right);
            root->right = root->right->left;
        }
        else{
            free(root->right);
            if(root->right->right != NULL and root->right->right->key < root->key) root->right = root->right->right;
        }
    }
}


void deleteNodo(struct node* root, int key){
    if(root != NULL){
        if(root->left != NULL){
            if(root->left->key != key)
                deleteNodo(root->left, key);
            else subDelete(root, key, 1);
        }
        if(root->right != NULL){
            if(root->right->key != key)
                deleteNodo(root->right, key);
            else subDelete(root, key, 2);
        }
    }
}

struct node* insert(struct node* node, int key){
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}


bool ancestroComun(struct node *node, int a, int b){
    if(node != NULL){
        if(node->key == a || node->key == b) return true;
        else{
            bool f1 = ancestroComun(node->right, a, b); 
            bool f2 = ancestroComun(node->left, a, b);
            if(f1 && f2) cout << node->key << endl;
            else if(f1 || f2 ) return true;
        }
    }
}

int numeroSaltos(struct node *node, int a, int b){
    if(node != NULL){
        if(node->key == a || node->key == b) return 1;
        else{
            int f1 = 0, f2 = 0;
            if(node->right != NULL) f1 = numeroSaltos(node->right, a, b); 
            if(node->left != NULL) f2 = numeroSaltos(node->left, a, b);
            int r = f1+f2;
            if(f1 != 0 && f2 != 0) cout << r << endl;
            else if(f1 != 0 || f2 != 0){
                return 1+f1+f2;
            }
            else if(f1 == 0 && f2 == 0) return 0;
        }
    }
}

int main(){
    struct node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    //preorder(root);
    /*deleteNodo(root, 30);
    preorder(root);*/
    ancestroComun(root, 80, 20);
    numeroSaltos(root, 70, 20);
    return 0;
}

