#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct treenode {
    char word[30];
    int occurence;
    struct treenode *left;
    struct treenode *right;
};

struct sum{
    char lname[30];
    char fname[30];
    char title[30];
    struct treenode * node;
    struct sum * next;
};


struct sum* sumadd(struct treenode *myroot, struct sum *current_list); //adds the binary tree to the info for the file
struct treenode* insert(struct treenode *root, struct treenode *temp); //inserts the new word into the tree
struct treenode* create_node(char val[30]);//creates the node that will be inserted
void preorder(struct treenode * current_ptr);//prints the preorder traversal of the binary tree
int find(struct treenode *current_ptr, char val[]);//finds the word that is being searched for and returns its occurence
void clear(struct treenode * myroot);
int hight(struct treenode *root);//finds the height of the binary tree

int main(void){
    int action=0, entries=0, words=0, score=0, tmpscore=0, height = 0;
    int j=0, str = 0, x=0, m=0,i=0;
    char over[30] = {'D','O','C','U','M','E','N','T','_','O','V','E','R'};
    char **query, filename[30], word[30], fname[30], lname[30], title[30];
    FILE *fp;
    struct treenode *temp= NULL, *root = NULL;
    struct sum * current_list, * temp_list;
    current_list = (struct sum *)malloc(sizeof(struct sum));


    printf("Which action would you like to perfrom?\n"
        " 1) Loading file into the database.\n"
        " 2) searching the database.\n"
        " 3) Quit the program.\n");

    scanf("%d", &action);
    while(action <= 3){
        if(action == 1){
            printf("\nEnter the name of your file: ");
            scanf("%s", filename);
            fp = fopen(filename, "r");

            if(fp == NULL){
                printf("\n\nSorry, that is an invalid file\n");
                return 0;
            }
            fscanf(fp, "%d", &entries);
            while(x < entries) {
            words = 0;
                fscanf(fp,"%s%s%s", current_list->fname, current_list->lname, current_list->title);
                do {
                        fscanf(fp, "%s", word);
                        if(strcmp(word,"DOCUMENT_OVER") !=0){
                                i=0;
                        str = strlen(word);
                        while(i < str){
                            word[i] = tolower(word[i]);
                            i++;
                        }
                        words++;
                                            temp = create_node(word);
                                root = insert(root, temp);
                                          }
                }
                while(strcmp(word, "DOCUMENT_OVER") != 0);
                current_list = sumadd(root, current_list);
                     printf("Title is:  %s\n", current_list->title);
                     printf("Number of words: %d\n", words);
                     printf("Height of the tree is: %d\n", hight(current_list->node));
                     preorder(current_list->node);
                     printf("\n\n\n");
                     free(root);
                x++;
        }
        }
        if(action ==2){
            printf("\nHow many words are in your query?\n");
            scanf("%d", &words);
            printf("\nWhich words would you like to search for?\n");
            query = (char **)malloc(words * sizeof(char *)+1);
            for(i=0; i < words; i++){
                j=0;
                query[i] = (char *)malloc(sizeof(char));
                printf("%d). ", i+1);
                scanf("%s", query[i]);
                str = strlen(query[i]);
                while(j< str){
                    query[i][j] = tolower(query[i][j]);
                    j++;
                }
                }
            i=0;
            temp_list = current_list;
            while(i < words){
            //while the list isn't empty
            while(temp_list != NULL){
            //print the required info
                printf("Title is: %s\n", temp_list->title);
                printf("Last Name is: %s\n", temp_list->lname);
                printf("Fist Name is: %s\n", temp_list->fname);
                score = find(temp_list->node, query[i]);
                if(score == 0){
                    printf("Sorry no matching word was found.\n\n");
                }
                else{
                    printf("Score = %d\n\n", score);
                    }
                i++;
                temp_list = temp_list->next;
                }
        }
        }
        if (action ==3){//program terminates
            printf("GOOD BYE\n\n");
            free(root);
            return 0;
        }
        printf("Which action would you like to perfrom?\n"
            " 1) Loading a file into the database.\n"
            " 2) searching the database.\n"
            " 3) Quit the program.\n");
        scanf("%d", &action);
    }
    return 0;
}

struct treenode* insert(struct treenode *root, struct treenode *temp){
    // element should be inserted to the right.

    // Inserting into an empty tree.
    if (root == NULL){
        root = (struct treenode*)malloc(sizeof(struct treenode));
        strcpy(root->word, temp->word);
        root->left = NULL;
        root->right = NULL;
        root->occurence = 1;
    }
    else{
        if(strcmp(root->word, temp->word) == 0){
            root->occurence++;
        }

        // There is a right subtree to insert the node.
        else if(strcmp(root->word, temp->word) > 0){
            if (root->right != NULL){
                root->right = insert(root->right, temp);
            }

            // Place the node directly to the right of root.
            else{
                root->right = (struct treenode*)malloc(sizeof(struct treenode));
                strcpy(root->right->word, temp->word);
                root->right->left = NULL;
                root->right->right = NULL;
                root->right->occurence = 1;
            }
        }
        else if(strcmp(root->word, temp->word) < 0){
            // There is a left subtree to insert the node.
            if (root->left != NULL){
                root->left = insert(root->left, temp);
            }
            // Place the node directly to the left of root.
            else{
                root->left = (struct treenode*)malloc(sizeof(struct treenode));
                strcpy(root->left->word, temp->word);
                root->left->left = NULL;
                root->left->right = NULL;
                root->left->occurence = 1;
            }
        }
    }
    return root;
}

int find(struct treenode *current_ptr, char val[]) {
    // Check if there are nodes in the tree.
    if (current_ptr != NULL) {
        // Found the value at the root.
        if (strcmp(current_ptr->word, val) == 0){
            return current_ptr->occurence;
        }
        // Search to the left.
        if (strcmp(current_ptr->word, val) < 0) {
            return find(current_ptr->left, val);
        }
        // Or...search to the right.
        if(strcmp(current_ptr->word, val) > 0) {
            return find(current_ptr->right, val);
        }
    }
//  else
        return 0;
}

struct sum* sumadd(struct treenode *myroot, struct sum * current_list)
{
    int i=0;
    struct sum * pNew;
    //allocate memory for the new document
    pNew = (struct sum *) (malloc(sizeof(struct sum)));
    //store the tree in the document
    pNew->node = myroot;
    pNew->next = NULL;

    //if its the first document
    if(current_list == NULL)
        current_list  =  pNew;
    //add document to the existing list
    else
    {
        pNew->next  =  current_list;
        current_list  =  pNew ;
    }
    return current_list;
}

struct treenode * create_node(char val[30]){
    // Asumocate space for the node, set the fields.
    struct treenode * temp;
    temp = (struct treenode*)malloc(sizeof(struct treenode));
    strcpy(temp->word,val);
    temp->left = NULL;
    temp->right = NULL;
    return temp;    // Return a pointer to the created node.
}


void preorder(struct treenode * current_ptr) {

  // Only traverse the node if it's not nusum.
  if (current_ptr != NULL) {
  printf("%s   \t%d\n", current_ptr->word, current_ptr->occurence);// Print the root.
    preorder(current_ptr->left); // Go Left.
    preorder(current_ptr->right); // Go Right.
  }
}

int hight(struct treenode *root){
        int right, left;
        //if the tree is empty height is zero
        if (root == NULL) {
                return 0;
        }
          //find the height of the tree by adding 1 each time
        left = 1 + hight(root->left);
        right = 1 + hight(root->right);

          //return the largest branch (either left of right)
        if (left > right) {
                return left;

        }
        else {
                return right;
        }
}

void clear(struct treenode * myroot){
//free the memory for the tree
    if (myroot != NULL) {
    clear(myroot->left); // Go Left.
    free(myroot); // free the root.
    clear(myroot->right); // Go Right.
  }
}
