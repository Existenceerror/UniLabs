#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char author[20];
	int tom;
}dop_info;

typedef struct 
{
	char* title;
	int page;
	dop_info uk;
}books;

int main_choise();
void delete(books* uka, int* n, int* in);
void add_item(int a, int* arr);
int* search(books* uka, int n);
int choise();

books enter();

int main()
{
	int n = 0;
	books* uka = NULL;
	uka = (books*)malloc(sizeof(books));
	if (uka == NULL)
	{
		printf("Error\n");
		exit(1);
	}
	printf("Enter:\n0 to end programm\n1 to add a new element\n2 to delete movies books by parametr\n3 to delete books with number of pages higher than need\n4 to find a book\n");
	while (1)
	{
		printf("\nIn the list %d books\nEnter command: ", n);
		switch (main_choise())
		{
		case 0:
		{
			free(uka);
			return 0;
		}
		case 1:
		{
			uka = (books*)realloc(uka, (n + 1) * sizeof(books));
			uka[n++] = enter();
			break;
		}
		case 2:
		{
			int* in;
			in = search(uka, n);
			if (in[0] != 0)
				delete(uka, &n, in);
			else
				printf("Nothing to delete\n");
			free(in);
			break;
		}
		case 3:
		{
			int* in, num;
			in = (int*)malloc(1);
			in[0] = 0;
			scanf_s("%d", &num);

			for (int i = 0; i < n; i++) if (uka[i].page > num) 
				enter(i, in);

			if (in[0] != 0)
				delete(uka, &n, in);
			else
				printf("Nechego udalyat\n");

			free(in);
			break;
		}
		case 4:
		{
			int* in;
			in = search(uka, n);
			printf("Books found: ");
			for (int i = 1; i != in[0]; i++) 
				printf("%d. %s\n", i, uka[in[i]].title);
			free(in);
		}
		}
	}
}

int main_choise()
{
	int k;
	while (scanf_s("%d", &k) == 0 || k < 0 || k > 4)
	{
		printf("Incorrect enter.\n");
		fflush(stdin);
	}
	getchar();
	return k;
}

books enter()
{
	books uka;

	printf("Enter number of pages ");
	scanf_s("%d", &uka.page);
	uka.title = (char*)calloc(100, sizeof(char));

	printf("Enter the title of the book ");
	fgets(uka.title, 100, stdin);
	uka.title = (char*)realloc(uka.title, strlen(uka.title) * sizeof(char*));

	printf("Enter the name of the author "); 
	fgets(uka.uk.author, 20, stdin);

	printf("Enter count of toms "); 
	scanf_s("%d", &uka.uk.tom);

	return uka;
}

void delete(books* uka, int* n, int* in)
{
	if (in[0] > 1)
	{
		int i = in[1], j = i + 1, t = 2;
        while (t <= in[0] && j < *n)
			if (j++ != in[t])
				uka[i++] = uka[j];
			else
				t++;

		*n = i;
	}
	else
	{
		*n = *n - 1;
		for (int i = in[1]; i < *n; i++) 
			uka[i] = uka[i + 1];
	}
	uka = (books*)realloc(uka, *n * sizeof(books));
}

void add_item(int a, int* arr)
{
	arr = (int*)realloc(arr, ++arr[0] * sizeof(int));
	arr[arr[0]] = a;
}

int* search(books* uka, int n)
{
	int* in;
	in = (int*)malloc(1);
	in[0] = 0;

	switch (choise())
	{
	case 1:
	{
		printf("Enter number of pages ");
		int num;
		scanf_s("%d", &num);
		for (int i = 0; i < n; i++) if (uka[i].page == num) 
			add_item(i, in);
		return in;
	}
	case 2:
	{
		printf("Enter title ");
		char* num = (char*)calloc(100, sizeof(char));
		fgets(num, 100, stdin);
		num[strlen(num) - 1] = 0;
		num = (char*)realloc(num, strlen(num) * sizeof(char));
		for (int i = 0; i < n; i++) if (strcmp(uka[i].title, num) == 0) 
			add_item(i, in);
		free(num);
		return in;
	}
	case 3:
	{
		printf("Enter author ");
		char num[20];
		fgets(num, 20, stdin);
		num[strlen(num) - 1] = 0;
		for (int i = 0; i < n; i++) if (strcmp(uka[i].uk.author, num) == 0) 
			add_item(i, in);
		return in;
	}
	case 4:
	{
		printf("Enter number of toms ");
		int num;
		scanf_s("%d", &num);
		for (int i = 0; i < n; i++) if (uka[i].uk.tom == num) add_item(i, in);
		return in;
	}
	}
}

int choise()
{
	printf("Enter: 1 to search by page\n2 to search by title\n3 to search by author\n4 to search by tom ");
	int k;
	while (scanf_s("%d", &k) == 0 || k < 1 || k > 4)
	{
		printf("Incorrect enter.\n");
		fflush(stdin);
	}
	getchar();
	return k;
}