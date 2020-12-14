#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

int nodeCount=0;

typedef struct linkedString
{
	char letter;
	struct linkedString *next;
}linkedString;

typedef struct trieNode
{
    struct trieNode* children[26];
    linkedString* linkedString;
    bool endOfWord;
}trieNode;

int getCharIndex(char c);
int stringToChar(linkedString* begin,char* str,int initial);
linkedString* createString(char newLetter);
trieNode* createNode();
linkedString* linkedStringAppend(char* str,int inital,int end);
trieNode* linkedStringBreak(trieNode* previousNode,trieNode* node,linkedString* breakPoint);
void insertNode(trieNode* root,char* word);
trieNode* searchNodes(trieNode* root,char* word);
void printSuggetions(trieNode* suggestedNode,char wordBuffer[],int bufferSize);
trieNode* fileReader(char* fileName);

int main(int argc,char* argv[]){
    char text[100];
    int i = 0;
    if(argc==1){
        printf("Usage: Input type: ProgramName <FileName>\n");
        }
    if(argc>2){
        printf("Too many arguments \n Input type: ProgramName <FileName>\n");
        }
    //int i = 0;
    trieNode* root = fileReader(argv[1]);    // filereading happing here 
    printf("Memory: %lu Bytes\n\n",sizeof(*(root))*nodeCount);

    while(1)
    {
        printf("Enter keyword: ");
        scanf("%s",&text[i]);
        char str[100];
        strcpy(str,text);
        clock_t begin = clock();
        trieNode* suggestedNode = searchNodes(root,str);
        printf("\n");
        if(suggestedNode != NULL){
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


int getCharIndex(char c)
{ 
   if((int)c >= 65 && (int)c <= 90){
     return tolower(c)-'a';  
   }else if( (int)c >= 97 && (int)c <= 122){
     return c-'a';
   }else
     return -1;
}

int stringToChar(linkedString* begin,char* str,int initial)
{
    int newSize = initial;
    linkedString* currentLetter = begin;

    while (currentLetter != NULL)
    {
        str[newSize] = currentLetter->letter;
        newSize++;
        currentLetter = currentLetter->next;
    }
    str[newSize] = '\0';
    return newSize-1;
}

linkedString* createString(char newLetter)
{
    linkedString* newString = (linkedString*) malloc(sizeof(linkedString));
    newString -> letter = newLetter;
    newString -> next = NULL;
    return newString;
}

trieNode* createNode()
{
    trieNode* newtrieNode = (trieNode*)malloc(sizeof(trieNode));
    newtrieNode->linkedString = NULL;
    newtrieNode->endOfWord = false;
    int i;
    for (i=0;i<26;i++)
    {
    	newtrieNode->children[i] = NULL;
    }
    return newtrieNode;
}

linkedString* linkedStringAppend(char* str,int inital,int end)
{
    int i;
    linkedString* current = createString(str[inital]);
    linkedString* newString = NULL;
    linkedString* string = current;

    for(i=inital+1;i<end;i++)
    {
        newString = createString(str[i]);
        current->next = newString;
        current = current->next;
    }
    current = NULL;
    return string;
}

trieNode* linkedStringBreak(trieNode* previousNode,trieNode* node,linkedString* breakPoint)
{
    trieNode* newNode = createNode();
    linkedString* newString = breakPoint->next;
    breakPoint->next = NULL;
    int index1 = getCharIndex(newString->letter);

    newNode->linkedString = node->linkedString;
    node->linkedString = newString;
    newNode->children[index1] = node;

    int index2 = getCharIndex(newNode->linkedString->letter);
    previousNode->children[index2] = newNode;

    return newNode;
}

void insertNode(trieNode* root,char* word)
{
    int lastLetterIndex = strlen(word)-1;
    int i=0,charIndex;

    trieNode* currentNode = root, *previousNode = NULL;
    trieNode* newNode = NULL;
    linkedString* currentLetter, *previousLetter = NULL;
    currentLetter = currentNode->linkedString;
    while(i<=lastLetterIndex)
    {
    	charIndex = getCharIndex(word[i]);
        if(charIndex >= 0){
    	    if(currentLetter == NULL)
            {
    		if(currentNode->children[charIndex] == NULL)
    		{
    			newNode = createNode();
    			newNode->linkedString = linkedStringAppend(word,i,lastLetterIndex);
                        newNode->endOfWord = true;
    			currentNode->children[charIndex] = newNode;
    			nodeCount = nodeCount+1;
    			break;
    		}else
                {
                        previousNode = currentNode;
                        currentNode = currentNode->children[charIndex];
                        previousLetter = currentNode->linkedString;
    			currentLetter = currentNode->linkedString->next;
    		}
    	    }else
            {
    		if (currentLetter->letter != word[i])
    		{
    			currentNode = linkedStringBreak(previousNode,currentNode,previousLetter);
    			newNode = createNode();
    			newNode->linkedString = linkedStringAppend(word,i,lastLetterIndex);
                        newNode->endOfWord = true;
    			currentNode->children[charIndex] = newNode;
    			break;
    		}else
                {
                        previousLetter = currentLetter;
    			currentLetter = currentLetter->next;
    		}
    	    }
        }
    	i++;
    }
}

trieNode* searchNodes(trieNode* root,char* word)
{
    int lastIndex = strlen(word);
    int i=0,charIndex,x=1;
    trieNode* currentNode = root;
    linkedString* currentLetter = currentNode->linkedString;

    while(i<lastIndex)
    {
    	charIndex = getCharIndex(word[i]);
    	if(currentLetter == NULL && x)
        {
            currentNode = currentNode->children[charIndex];
            if(currentNode != NULL){
    	       currentLetter = currentNode->linkedString->next;
            }
            else{
               x=0;
            }
    	}
        else if(x && currentLetter != NULL)
        {    
    	    currentLetter = currentLetter->next;
    	}
        i++;
    }

    while(currentLetter != NULL)
    {
    	word[lastIndex] = currentLetter->letter;
    	currentLetter = currentLetter->next;
    	lastIndex++;
    }
    word[lastIndex] = '\0';

    return currentNode;
}

trieNode* fileReader(char* fileName)
{
    char word[60];
    FILE *fp = fopen(fileName,"r");
    if (fp == NULL)
    {
        printf("Unable to open the file\n");
        exit(1);
    }
    trieNode* root = createNode();
    clock_t begin = clock();
    while(1)
    {
        fgets(word,60,fp);
        insertNode(root,word);
        if(feof(fp))
            break;
    }
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Insertion Time: %.8lf s\n",time_spent);
    fclose(fp);
    return root;
}

void printSuggetions(trieNode* suggestedNode,char wordBuffer[],int bufferSize)
{
    trieNode* currentNode = suggestedNode;
    int i,j,newSize;

    if(currentNode->endOfWord)
    {
        for (j=0;j<bufferSize;j++)
        {
            printf("%c",wordBuffer[j]);
        }
        printf("\n");
    }

    for (i=0;i<26;i++)
    {
        if(currentNode->children[i]!=NULL)
        {
            newSize = stringToChar(currentNode->children[i]->linkedString,wordBuffer,bufferSize);
            printSuggetions(currentNode->children[i],wordBuffer,newSize+1);
        }
    }
}

