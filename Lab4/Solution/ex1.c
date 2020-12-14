#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
int wordCount=0;
typedef struct trieNode     // stucter of trienode 
{
    struct trieNode *children[26];    // there can be 26 children for the node 
    char character;          // data for node 
    bool endOfWord;    // tag for this is end of word or not 
}trieNode;

int getChildNum(char letter) ;  // geting character poisition to chilren node 
trieNode* makeNode() ;  // makeing a new node 
void insertWord(trieNode *root,char *word);   /// to insert a new word into tree giving arguements as root and word
trieNode* searchNodes(trieNode* root,char* word);    // geting the and node for a word 
void printSuggetions(trieNode* suggestedNode,char wordBuffer[],int bufferSize); // this will print suggestion words  
trieNode* fileReader(char* fileName);    // its doing the file reading part and insert the data to nodes 

int main(int argc,char* argv[]){
    char text[100];
    int i = 0;
    if(argc==1){
        printf("Usage: Input type: ProgramName <FileName>\n");
        }
    if(argc>2){
        printf("Too many arguments \n Input type: ProgramName <FileName>\n");
        }

    trieNode* root = fileReader(argv[1]);    // filereading happing here 
    printf("Memory: %lu Bytes\n\n",sizeof(*(root))*wordCount);

    while(1)
    {
        printf("Enter keyword: ");
        scanf("%s",&text[i]); // takeing user input 
        char str[100];
        strcpy(str,text);
        trieNode* suggestedNode = searchNodes(root,str);
        printf("\n");
        if(suggestedNode != NULL){
           clock_t begin = clock();
           printSuggetions(suggestedNode,str,strlen(str));
           clock_t end = clock();
           double elapsed_time = (double)(end-begin)/CLOCKS_PER_SEC;
           printf("\nElapsed time: %f s\n",elapsed_time);
           printf("\n");
        }else{
           printf("No Matching Suggestions\n\n");
        }
  
    }
    return 0;
}


int getChildNum(char letter)   // geting character poisition to chilren node 
{ 
   if((int)letter >= 65 && (int)letter <= 90){       // if the letter is capital 
     return tolower(letter      )-'a';  
   }else if( (int)letter>= 97 && (int)letter <= 122){ // if the letter is small 
     return letter-'a';
   }else
     return -1;     // if the letter is not a alph character then 
}

trieNode* makeNode()   // makeing a new node 
{
    trieNode* newtrieNode = (trieNode*)malloc(sizeof(trieNode));  // allocating space for the new node 
    newtrieNode->character=' ';  // initialy make that as space 
    newtrieNode->endOfWord = false;    // not end of word 
    int i;
    for (i = 0; i<26; i++)      // keep all chlidren as null 
    {
    	newtrieNode->children[i] = NULL;
    }
    return newtrieNode;
}

void insertWord(trieNode *root,char *word)   /// to insert a new word into tree giving arguements as root and word
{
    int i,childNum;
    trieNode* newNode = root;
    for(i=0;i<strlen(word)-1;i++)    // though the for loop adding all character of word 
    {
        childNum = getChildNum(word[i]);
        if(childNum >= 0){    // if its aplh char only 
        if(newNode->children[childNum] == NULL)  // if alreay there not in that lettr only insert 
        {
            newNode->children[childNum] = makeNode();  // making the node and assing 
            newNode->children[childNum]->character = word[i];

        }
            newNode = newNode->children[childNum]; // if the letter allrady in then go to the next node 
        }
    } // end of insetion make that last node as end of word and count the word 
    newNode->endOfWord = true;
    wordCount = wordCount+1;
}

trieNode* searchNodes(trieNode* root,char* word)    // geting the and node for a word 
{
    int i,childNum;
    trieNode* currentNode = root;
    for(i=0;i<strlen(word);i++)
    {
        childNum = getChildNum(word[i]);// geting child number for that letter 
        if(currentNode != NULL)
          currentNode =currentNode->children[childNum];
    }
    return currentNode;    // returing end of node 
}

void printSuggetions(trieNode* suggestedNode,char wordBuffer[],int bufferSize) // this will print suggestion words  
{
    int i,getChildNum;
    if(suggestedNode->endOfWord)  // the given node is end of only its going to suggeest 
    {
        for(i=0;i<bufferSize;i++)  // // this will print the suggested  word first 
        {
            printf("%c",wordBuffer[i]);
        }
        printf("\n");
    }
    for(i=0;i<26;i++)
    {
        if(suggestedNode->children[i]!=NULL) // its going to check given node chilrens for suggestion until null children come 
        {
            wordBuffer[bufferSize] = suggestedNode->children[i]->character;
            printSuggetions(suggestedNode->children[i],wordBuffer,bufferSize+1);  // recursivly its called
        }
    }
}

trieNode* fileReader(char* fileName)    // its doing the file reading part and insert the data to nodes 
{
    char word[100];
    FILE *fp = fopen(fileName,"r");      // reading the file 
    if (fp == NULL)
    {
        printf("Unable to open the file\n");
        exit(1);
    }
    trieNode* root = makeNode(); // making the node 
    root->character = '/';    // just assing a character 
    clock_t begin = clock();   // taking the time of this point 
    while(1)
    {
        fgets(word,100,fp);
        insertWord(root,word);
        if(feof(fp))    // untile file strem going to end 
            break;
    }
    clock_t end = clock();  // takeing time of after creat the tree 
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;  /// tree creation time 
    printf("Insertion Time: %.8lf s\n",time_spent);    
    fclose(fp);
    return root;
}

