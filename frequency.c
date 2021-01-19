#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LETTERS 26
typedef enum { false, true } bool;
typedef struct Node
{
    struct Node* children[LETTERS];
    char letter;
	bool is_end_of_word;
    long unsigned int count;
    int tag;
}Node;
char* to_lower_case(char* words);
Node* create_Node(char *letter);
Node* add_root();
void add_node(Node *head, char* str);
void free_mem_TRIE (Node* head);
void print_words(Node* root, char word[], int j);
void print_words_R(Node* root, char word[], int j);

char* to_lower_case(char* words)
{
    int i = 0;
    char *str = strdup(words);

    while (str[i])
    {
        if((str[i] < 65) || (str[i] > 123))
            memmove(&str[i], &str[i+1], strlen(str)-i);
        if ((str[i] >= 65) && (str[i] <= 90))
            str[i] += 32;
        i++;
    }
    return (str);
}


Node* create_Node(char *letter)
{
    Node* new_Node = (Node*)malloc(sizeof(Node));
    int i = 0;
	new_Node->count = 0;
	new_Node->is_end_of_word = false;
	new_Node->tag = 0;
    new_Node->letter = *letter;
    for(i = 0; i < LETTERS; i++)
    {
        new_Node->children[i] = NULL;
    }
    return new_Node;
}
void add_node(Node *head, char* str)
{
    if (!*str)
        return;
    while (*str)
    {
        if (head->children[*str - 'a'] == NULL)
            head->children[*str - 'a'] = create_Node(str);
        head = head->children[*str - 'a'];
        str++;
    }
	head->count++;
    head->is_end_of_word = true;
}
Node* add_root()
{

    Node* n = (Node*)malloc(sizeof(Node));
    n->count = 0;
    n->is_end_of_word = 0;
    for(int i = 0; i < LETTERS; i++)
    {
        n->children[i] = NULL;
    }
    return n;
}

void print_words(Node* root, char word[], int j)
{
       
    if (root -> is_end_of_word)
	{
        word[j] ='\0';
        printf("%s", word);
        printf(" %lu\n", root -> count);
    }
    for(int i = 0; i < LETTERS; i++)
	{
        if (root -> children[i]){
            word[j] = i + 'a';
            print_words((root -> children[i]),word,j + 1);
        }
    }
}

void print_words_R(Node* root, char word[], int j)
{
    if(root == NULL)
        return;
    if(root->is_end_of_word == true)
    {
        word[j]='\0';
        printf("%s %ld\n",word,root->count);
    }
    for(int i=LETTERS-1 ;i>= 0; i--)
    {
        if(root->children[i] != NULL)
        {
            word[j] = i+'a';
            print_words_R((root->children[i]), word, j+1);
        }
    }
}

void free_mem_TRIE (Node* head)
{
    for (int i = 0; i < LETTERS; i++ )
	{
        if(head -> children[i] != NULL)
		{
            free_mem_TRIE(head -> children[i]);
        }
    }
    if (head != NULL){
        free(head);
    }
}

int main(int n, char *args[])
{
    Node* root = add_root();
    int start = 0, i = 0;
    char* word = (char*)malloc(sizeof(char)*2); 
    if (word == NULL)
        printf("Memory Error");
    *word = 0;
    *(word+1) = 0;  
    char letter;
        while ((letter = getc(stdin) )!= EOF)
		{
			if((letter!='\0') && (letter!=',') && (letter!=' ') && (letter!='\n') && (letter!='\t'))
			{
				if(!((letter>='A' && letter<='Z') || (letter>='a' && letter<='z')))
					continue;
				word[start] = letter;
				start++;   
				word = (char*)realloc(word,start + 2);  
				  if (word == NULL)
					printf("Error Memory extention");
				for (int i = start; i < start + 2; i++)
					*(word + i) = 0;      
			}
			else
			{
				add_node(root,word);
				free(word);
				word = (char*)malloc(sizeof(char)*2);
				  if (word == NULL)
					  printf("Error Memory allocation");
				 *word = 0;
				 *(word+ 1) = 0; 
				if (start >= i)
					i = start;
				start = 0;
			} 
      }
	    if (start == 0)
            free(word);
        if (start > 0)
		{
            add_node(root,word);
            free(word);
        }

        char* length = (char*) malloc(sizeof(char) * i);
    if (n == 1)
        print_words(root,length,0);
	else if(n == 2)
	{
         if (strcmp(args[1],"r")==0)
         	print_words_R(root,length,0);
    }
    free(length);
    free_mem_TRIE(root);
    return 0;
}