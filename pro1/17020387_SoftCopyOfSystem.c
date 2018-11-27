#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//implement a linked list
struct node{
	struct node *previous,*next;
	char word[200],synonyms[400];
};

struct node *start=NULL;

//creating array node using doubly linked list
struct node* createNode(char *word,char *synonyms){
	struct node *new_node;
	new_node=(struct node*)malloc(sizeof(struct node));//memory allocated by using malloc
	strcpy(new_node->word,word);
	strcpy(new_node->synonyms,synonyms);
	new_node->previous=new_node->next=NULL;
	return new_node;
}

//insert a word and it's meaning to doubly linked list at once a time to the dictionary
void add(char *word,char *synonyms){
	struct node *main=NULL,*current=NULL,*new_node=NULL;
	int x=0;
	if(!start){
		start=createNode(word,synonyms);
		return;
	}
	for(current=start;current!=NULL;current=(x>0)?current->next :current->previous){
		x=strcasecmp(word,current->word);
		if(x == 0){
			printf("\nThe word is not exit!");
			return;
		}
		main=current;
	}
	new_node=createNode(word,synonyms);
	(x>0 )?(main->next=new_node):(main->previous=new_node);
	return;
}


//delete the word.if it is not necessary to the dictionary
void delete(char *word) {
        struct node *main = NULL, *current = NULL, *temp = NULL;
        int flag = 0, x = 0;
        if (!start) {
                printf("Word is not found\n");
                return;
        }
        current = start;
        while (1) {
                x = strcasecmp(current->word,word);
                if (x == 0)
                        break;
                flag = x;
                main = current;
                current = (x > 0) ? current->previous: current->next;
                if (current == NULL)
                	 return;
        }
       
        if (current->next == NULL) {
                if (current == start && current->previous== NULL) {
                        free(current);
                        start = NULL;
                        return;
                } else if (current == start) {
                        start = current->previous;
                        free (current);
                       	return;
                }

                flag > 0 ? (main->previous= current->previous) :(main->next = current->previous);
        } else {
                
                temp = current->next;
                if (!temp->previous) {
                        temp->previous= current->previous;
                        if (current == start) {
                                start = temp;
                                free(current);
                                return;
                        }
                        flag > 0 ? (main->previous= temp) :(main->next = temp);
                } else {
                        
                        struct node *right = NULL;
                        while (1) {
                                right= temp->previous;
                                if (!right->previous)
                                        break;
                                temp = right;
                        }
                        temp->previous= right->next;
                        right->previous= current->next;
                        right->next = current->next;
                        if (current == start) {
                                start = right;
                                free(current);
                                return;
                        }
                        (flag > 0) ? (main->previous= right): (main->next = right);
                }
        }
        free (current);
        return;
  }
  
//find out whether the word is found or not in the dictionary
void check(char *word){
	struct node *temp=NULL;
	int flag=0,x=0;
	if(start==NULL){
		printf("\nNot found");
		return;
	}
	temp=start;
	while(temp){
		if((x=strcasecmp(temp->word,word))==0){
			
			printf("\nThe word is found");
			flag=1;
			break;
		}
		temp=(x>0)?temp->previous:temp->next;
	}
	if(!flag)
		printf("\nNot found");
		return;	
}


//find the meaning to the given word
void suggest(char *word){
	struct node *temp=NULL;
	int flag=0,x=0;
	if(start==NULL){
		printf("\nNot found");
		return;
	}
	temp=start;
	while(temp){
		if((x=strcasecmp(temp->word,word))==0){
			printf("\nWord: %s",word);
			printf("\nSynonyms: %s",temp->synonyms);
			flag=1;
			break;
		}
		temp=(x>0)?temp->previous:temp->next;
	}
	if(!flag)
		printf("\nNot found");
		return;	
}

//delete all the words in the dictionary
void reset(){
	while(start){
		struct node *p=start;
		start=start->next;
		free(p);
	}
}

//Main function
int main(){
	char word[200],synonyms[400];
	int option;
	do{
		printf("\n\n ****MAIN MENU OF DICTIONARY****");
		printf("\n1.Add words");
		printf("\n2.Delete words");
		printf("\n3.Check words");
		printf("\n4.Suggest synonyms");
		printf("\n5.Reset");
		printf("\n6.Quit");
		printf("\n Enter your option:");
		scanf("%d",&option);
		getchar();
		switch(option)
		{
			case 1:
				printf("\n Enter a word:");
				gets(word);
				printf("\n Synonyms:");
				gets(synonyms);
				add(word,synonyms);
				break;
			case 2:
				printf("\nEnter the word that should be deleted:");
				gets(word);
				delete(word);
				break;
			case 3:
				printf("Check word:");
				gets(word);
				check(word);
				break;
			case 4:
				printf("Suggest synonyms:");
				gets(word);
				suggest(word);
				break;
			case 5:
				reset();
			 	break;
			case 6:
				exit(0)	;
		}
		
	}while(option!=7);
	getch();
	return 0;
}




