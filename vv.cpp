#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

int song_count = 0;
struct node
{
    char song[100];
    struct node *next;
    struct node *prev;
} *top, *temp, *top1;

void tofile(char a[])
{
    fstream f1;
    f1.open("playlist.txt", ios::out | ios::app);
    f1 << a << endl;
    f1.close();
}

void add_node(struct node *first)
{
    char a[100];
    while (first->next != NULL)
    {
        first = first->next;
    }
    first->next = (struct node *)malloc(sizeof(struct node));
    first->next->prev = first;
    first = first->next;
    cout << "\nEnter Song name: ";
    scanf("%s", a);
    strcpy(first->song, a);
    tofile(a);
    first->next = NULL;
    cout << "Song added successfully!" << endl;
}

void add_node_file(struct node *first, string a)
{
    while (first->next != NULL)
    {
        first = first->next;
    }
    first->next = (struct node *)malloc(sizeof(struct node));
    first->next->prev = first;
    first = first->next;
    strcpy(first->song, a.c_str());
    first->next = NULL;
}

void delete_file(char a[])
{
    fstream f1, f2;
    string line;
    int x = 0;
    f1.open("playlist.txt", ios::in | ios::out);
    f2.open("temp.txt", ios::out);
    while (getline(f1, line))
    {
        if (strcmp(a, line.c_str()) != 0)
            f2 << line << endl;
        else if (strcmp(a, line.c_str()) == 0)
            x = 1;
    }
    f1.close();
    f2.close();
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    if (x == 0)
    {
        cout << "There is no song with the name you entered." << endl;
    }
    else
    {
        cout << "Song has been deleted." << endl;
    }
}

void del_node(struct node *first)
{
    while ((first->next)->next != NULL)
    {
        first = first->next;
    }
    struct node *temp;
    temp = first->next;
    first->next = NULL;
    free(temp);
    cout << "Deleted" << endl;
}

void printlist(struct node *start)
{
    if (start == NULL)
    {
        cout << "The playlist is empty." << endl;
        return;
    }

    // Display the playlist name
    cout << "Playlist name is: " << start->song << endl;

    struct node *temp = start->next; // Skip the first node as it contains the playlist name
    while (temp != NULL)
    {
        cout << temp->song << endl;
        temp = temp->next;
    }
}

void count_nodes(struct node *first)
{
    int i = 0;
    while (first->next != NULL)
    {
        first = first->next;
        i++;
    }
    i++;
    cout << "\nTotal songs: " << i - 1 << endl;
}

struct node *del_pos(struct node *pointer, int pos)
{
    if (pos == 1)
    {
        cout << "Cannot delete the playlist name." << endl;
        return pointer;
    }

    struct node *current = pointer; // Start from the playlist name node
    struct node *prev = nullptr; // Previous node pointer
    int i = 1; // Position counter

    while (current != NULL && i < pos)
    {
        prev = current;
        current = current->next;
        i++;
    }

    if (current == NULL)
    {
        cout << "Position out of range." << endl;
        return pointer;
    }

    struct node *temp = current;
    delete_file(temp->song);

    if (current->next != NULL)
    {
        current->next->prev = prev;
    }
    if (prev != NULL)
    {
        prev->next = current->next;
    }

    free(temp);
    cout << "\nThe list is updated\nUse the display function to check\n";

    return pointer;
}
void search1(struct node *first)
{
    char song[100];
    cout << "\nEnter song to be searched: ";
    scanf("%s", song);
    int flag = 0;

    while (first != NULL)
    {
        if (strcmp(first->song, song) == 0)
        {
            cout << "\n#Song Found" << endl;
            flag++;
            break;
        }
        else
        {
            first = first->next;
        }
    }
    if (flag == 0)
    {
        cout << "\n#Song Not found" << endl;
    }
}

void create()
{
    top = NULL;
}

void push(char data[])
{
    if (top == NULL)
    {
        top = (struct node *)malloc(sizeof(struct node));
        top->next = NULL;
        strcpy(top->song, data);
    }
    else if (strcmp(top->song, data) != 0)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        temp->next = top;
        strcpy(temp->song, data);
        top = temp;
    }
}

void display()
{
    top1 = top;
    if (top1 == NULL)
    {
        printf("\n=> NO recently played tracks.\n");
        return;
    }
    printf("\n# Recently played tracks:\n");
    while (top1 != NULL)
    {
        printf("%s", top1->song);
        printf("\n");
        top1 = top1->next;
    }
}

struct node *current_song = NULL; // Global variable to store the current song node

void play(struct node *first)
{
    char song[100];
    printlist(first);
    cout << "\nChoose song you wish to play: ";
    scanf("%s", song);
    int flag = 0;

    while (first != NULL)
    {
        if (strcmp(first->song, song) == 0)
        {
            cout << "\n=> Now Playing: " << song << endl;
            flag++;
            push(song);
            current_song = first; // Store the current song node
            break;
        }
        else
        {
            first = first->next;
        }
    }
    if (flag == 0)
    {
        cout << "\n# Song Not found" << endl;
    }
}
void play_next()
{
    if (current_song == NULL || current_song->next == NULL)
    {
        cout << "\n# No next song to play." << endl;
        return;
    }

    current_song = current_song->next; // Move to the next song
    cout << "\n=> Now Playing: " << current_song->song << endl;
    push(current_song->song); // Add the song to the recently played stack
}


void recent()
{
    display();
}

void topelement()
{
    top1 = top;
    if (top1 == NULL)
    {
        printf("\n# NO last played tracks.\n");
        return;
    }
    cout << "\n=> Last Played Song: " << top->song << endl;
}
void split(node *source, node **front, node **back)
{
    node *fast;
    node *slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}
node *sortedMerge(node *a, node *b) {
    node *result = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if (strcmp(a->song, b->song) <= 0) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

void mergeSort(node **headRef) {
    node *head = *headRef;
    node *a;
    node *b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);
        *headRef = sortedMerge(a, b);
}

void sort(node *&pointer) {
    mergeSort(&pointer);
}

void addplaylist(struct node *start)
{
    fstream f1;
    string line;
    f1.open("playlist.txt", ios::in);
    while (getline(f1, line))
    {
        add_node_file(start, line);
        song_count++;
    }
    cout << "Playlist Added" << endl;
    f1.close();
}

void del_search(struct node *&start)
{
    char song[100];
    printlist(start);
    cout << "\nChoose song you wish to delete: ";
    scanf("%s", song);
    int flag = 0;
    struct node *current = start;

    while (current != NULL)
    {
        if (strcmp(current->song, song) == 0)
        {
            cout << "\n# Song Found" << endl;
            struct node *temp = current;

            if (current->prev != NULL)
                current->prev->next = current->next;
            else
                start = current->next; // Update start if the first node is deleted

            if (current->next != NULL)
                current->next->prev = current->prev;

            delete_file(temp->song);
            free(temp);
            flag++;
            break;
        }
        else
        {
            current = current->next;
        }
    }

    if (flag == 0)
    {
        cout << "\n# Song Not found" << endl;
    }
    else
    {
        // Decrement the song count
        song_count--;
        // Print the updated list
        printlist(start);
    }
}

void deletemenu(struct node *&start)
{
    int c;
    cout << "Which type of delete do you want?\n1. By Search\n2. By Position" << endl;
    cin >> c;
    switch (c)
    {
    case 1:
        del_search(start);
        break;
    case 2:
        int pos;
        printf("\nEnter the pos of the song (Consider pos 1 to be the playlist name): ");
        scanf("%d", &pos);
        start = del_pos(start, pos);
        break;
    }
}

int main()
{
    int choice, loc;
    char song[100];
    struct node *start, *hold;
    start = (struct node *)malloc(sizeof(struct node));
    cout << "\t\t\t**WELCOME**" << endl;
    cout << "\n** Please use '_' for space." << endl;
    cout << "\nEnter your playlist name: ";
    cin.getline(start->song, 100);
    start->next = NULL;
    start->prev = NULL;
    hold = start;
    create();

    do
    {
        cout << "\n1. Add New Song\n2. Delete Song\n3. Display Entered Playlist\n4. Total Songs\n5. Search Song\n6. Play Song\n7. Recently Played List\n8. Last Played\n9. Sorted Playlist(Alphabetical Order)\n10. Add From File\n11. Play Next Song\n12. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_node(start);
            break;
        case 2:
            deletemenu(start);
            break;
        case 3:
            printlist(start);
            break;
        case 4:
            count_nodes(hold);
            break;
        case 5:
            search1(start);
            break;
        case 6:
            play(start);
            break;
        case 7:
            recent();
            break;
        case 8:
            topelement();
            break;
        case 9:
            sort(start->next);
            printlist(start);
            break;
        case 10:
            addplaylist(start);
            break;
        case 11:
            play_next();
            break;
        case 12:
            cout << "\nThank you for using the playlist manager. Goodbye!" << endl;
            exit(0);
            default:
            cout << "\nInvalid choice. Please enter a number between 1 and 12." << endl;
            break;
        }
    } while (choice != 12);

    return 0;
}
