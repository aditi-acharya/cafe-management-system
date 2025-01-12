//admin login creds: 
//usename: admin
//password: abcde


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    char foodname[50];
    float price;
    struct node* next;
};

struct node* headAdmin = NULL;  // Head pointer for admin menu

struct customer {
    char customerName[50];
    struct customer* next;
};

struct node* headc = NULL;
struct customer* front = NULL; // Front of the queue
struct customer* rear = NULL;  // Rear of the queue

void enqueue(const char* customerName) {
    // Function to add a customer to the queue
    struct customer* newNode = (struct customer*)malloc(sizeof(struct customer));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->customerName, customerName);
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue() {
    // Function to remove a customer from the queue
    if (front == NULL) {
        printf("Queue is empty, cannot dequeue.\n");
        return;
    }
    struct customer* temp = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
}

void displayQueue() {
    // Function to display the queue of customers
    struct customer* temp = front;
    if (temp == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue of Customers: ");
    while (temp != NULL) {
        printf("%s -> ", temp->customerName);
        temp = temp->next;
    }
    printf("X\n");
}

struct node* createAdmin(struct node* head, int data, const char* foodname, float price) {
    // Function to create a new node in the admin menu
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    strcpy(temp->foodname, foodname);
    temp->price = price;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        struct node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    return head;
}

void view(struct node* head) {
    // Function to display the items in the menu
    if (head == NULL) {
        printf("Menu is empty.\n");
        return;
    }
    printf("\nID\t\tFood Name\t\tPrice\n");
    while (head != NULL) {
        printf("%d\t%s\t\tRs. %.2f\n", head->data, head->foodname, head->price);
        head = head->next;
    }
}

struct node* createCustomer(struct node* head, int data, const char* foodname, float price) {
    // Function to create a new node in the customer's order
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    strcpy(temp->foodname, foodname);
    temp->price = price;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        struct node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    return head;
}

struct node* deleteCustomer(struct node* head, int data) {
    // Function to delete an item from the customer's order
    if (head == NULL) {
        printf("\nNo items found!\n");
    } else {
        struct node* prev = NULL;
        struct node* curr = head;

        while (curr != NULL && curr->data != data) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != NULL) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("\nItem deleted from order successfully!\n");
        } else {
            printf("Item not found in order!\n");
        }
    }
    return head;
}

void orderMenu(struct node* head) {
    // Function to display the menu for ordering
    printf("\n***** MENU *****\n\n");
    view(head);
    printf("\nEnter food ID to add to order (0 to exit): ");
}

float calculateTotalBill() {
    // Function to calculate the total bill of the customer's order
    struct node* ptr = headc;
    float totalBill = 0.0;

    while (ptr != NULL) {
        totalBill += ptr->price;
        ptr = ptr->next;
    }
    return totalBill;
}

void orderForCustomer() {
    // Function to handle the ordering process for a customer
    char customerName[50];
    printf("\nEnter the customer name: ");
    scanf("%s", customerName);
    enqueue(customerName);

    orderMenu(headAdmin);
    int data;
    while (1) {
        printf("\n***** ORDER FOR CUSTOMER *****\n\n");
        printf("1. Order Menu\n");
        printf("2. View Order\n");
        printf("3. Delete Item from Order\n");
        printf("4. Total Bill\n");
        printf("5. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &data);

        switch (data) {
            case 1: {
                int foodID;
                printf("\n");
                //orderMenu(headAdmin);
                printf("\nEnter food ID to add to order (0 to exit): ");
                scanf("%d", &foodID);

                if (foodID == 0) {
                    break;
                }

                struct node* ptr = headAdmin;
                while (ptr != NULL && ptr->data != foodID) {
                    ptr = ptr->next;
                }

                if (ptr != NULL) {
                    headc = createCustomer(headc, ptr->data, ptr->foodname, ptr->price);
                    printf("\nItem added to order successfully!\n");
                } else {
                    printf("\nItem not found in menu!\n");
                }
                break;
            }
            case 2:
                view(headc);
                break;
            case 3: {
                int foodID;
                printf("\nEnter food ID to delete from order: ");
                scanf("%d", &foodID);
                headc = deleteCustomer(headc, foodID);
                break;
            }
            case 4:
                printf("\nTotal Bill: Rs. %.2f\n", calculateTotalBill());
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                break;
        }
    }
}

struct node* deleteadmin(struct node* head, int data) {
    // Function to delete an item from the admin menu
    if (head == NULL) {
        printf("No items found!\n");
    } else {
        struct node* prev = NULL;
        struct node* curr = head;

        while (curr != NULL && curr->data != data) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != NULL) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("\nItem deleted from menu successfully!\n");
        } else {
            printf("\nItem not found in menu!\n");
        }
    }
    return head;
}

void employeeMenu() {
    int choice;
    do {
        printf("\n***** EMPLOYEE MENU *****\n\n");
        printf("1. Order for New Customer\n");
        printf("2. Order History\n");
        printf("3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                orderForCustomer();
                break;
            case 2:
                printf("\n***** ORDER HISTORY *****\n\n");
                displayQueue();
                printf("Order processed? (1 for Yes / 0 for No): ");
                int processed;
                scanf("%d", &processed);
                if (processed == 1) {
                    dequeue();
                    printf("Order processed and removed from the queue.\n");
                }
                break;
            case 3:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 3);
}

void adminmenu() {
    // Function to display the admin menu options
    printf("***** ADMIN MENU *****\n\n");
    printf("1. Total Sales\n");
    printf("2. Add Item\n");
    printf("3. Delete Item\n");
    printf("4. View Items\n");
    printf("5. Exit\n\n");
}

int main() {
    // Pre-populated items in the admin menu
    headAdmin = createAdmin(headAdmin, 1, "Cappuccino", 50);
    headAdmin = createAdmin(headAdmin, 2, "Mocha     ", 70);
    headAdmin = createAdmin(headAdmin, 3, "Mango Smoothie", 80);
    headAdmin = createAdmin(headAdmin, 4, "Cinnamon roll", 60);
    headAdmin = createAdmin(headAdmin, 5, "French Toast", 50);
    headAdmin = createAdmin(headAdmin, 6, "Iced Coffee", 70);
    headAdmin = createAdmin(headAdmin, 7, "Espresso", 50);

    while (1) {
        int choice;
        printf("\n***** CAFE MANAGEMENT SYSTEM *****\n\n");
        printf("1. Admin\n");
        printf("2. Employee\n");
        printf("3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char username[20], password[20];

                printf("\nEnter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                if (strcmp(username, "admin") == 0 && strcmp(password, "abcde") == 0) {
                    int choice;

                    while (1) {
                        adminmenu();
                        printf("Enter your choice: ");
                        scanf(" %d", &choice);

                        switch (choice) {
                            case 1:
                                printf("\nTotal Sales: Rs. %.2f\n", calculateTotalBill());
                                break;
                            case 2: {
                                int data;
                                char foodname[50];
                                float price;

                                printf("\nEnter food ID: ");
                                scanf("%d", &data);
                                printf("Enter food name: ");
                                scanf("%s", foodname);
                                printf("Enter price: ");
                                scanf("%f", &price);

                                headAdmin = createAdmin(headAdmin, data, foodname, price);
                                printf("\nItem added to menu successfully!\n");
                                break;
                            }
                            case 3: {
                                int data;

                                printf("\nEnter food ID to delete: ");
                                scanf("%d", &data);

                                headAdmin = deleteadmin(headAdmin, data);
                                break;
                            }
                            case 4:
                                view(headAdmin);
                                break;
                            case 5:
                                return 0;
                            default:
                                printf("\nInvalid choice! Please try again.\n");
                                break;
                        }
                    }
                } else {
                    printf("\nInvalid username or password!\n");
                }
                break;
            }
            case 2:
                employeeMenu();
                break;
            case 3:
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}
