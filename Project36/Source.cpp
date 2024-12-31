#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#define size 50
#define V 11
#define V1 6
using namespace std;

// Structure to represent a user
struct user {
    string name;        // Name of the user
    string product;     // Product purchased by the user
    int quantity;       // Quantity of the product
    double bill;        // Total bill amount

    // Default constructor
    user() {
        this->name = " ";
        this->product = " ";
        this->quantity = 0;
        this->bill = 0.0;
    }

    // Parameterized constructor
    user(string name, string product, int quantity, double bill) {
        this->name = name;
        this->product = product;
        this->quantity = quantity;
        this->bill = bill;
    }
};

// Structure to represent a delivery user
struct deliveryUser {
    user nUser;             // User information
    string address;         // Delivery address
    double deliveryCharges; // Delivery charges
    int distanceDelivery;   // Distance for delivery
    deliveryUser* next = NULL; // Pointer to the next delivery user

    // Constructor for initializing a delivery user
    deliveryUser(string name, string product, int quantity, double bill, string address, double deliveryCharges, int distanceDelivery) {
        this->nUser = user(name, product, quantity, bill);
        this->address = address;
        this->deliveryCharges = deliveryCharges;
        this->distanceDelivery = distanceDelivery;
    }
};

// Structure to represent a shop
struct Shop {
    string name;            // Shop name
    string* product;        // List of products
    int* price;             // List of prices
    string address;         // Shop address
    deliveryUser* nextdeliveryUser; // Pointer to the list of delivery users
};

// Global variables
Shop* shop = NULL;
string addressF;
int dist[V];
int distanceP[V1];
int optionDelivery = -999;
int optionDelivery1 = -999;
deliveryUser* currentdeliveryUser = NULL;

// Structure to represent a take-away order in the AVL tree
struct takeAway {
    string name;        // Name of the customer
    string product;     // Product purchased
    int quantity;       // Quantity of the product
    double bill;        // Total bill amount
    int orderId;        // Unique order ID
    takeAway* left;     // Pointer to the left child
    takeAway* right;    // Pointer to the right child

    // Constructor for initializing a take-away order
    takeAway(string name, string product, int quantity, double bill, int orderId) {
        this->name = name;
        this->product = product;
        this->quantity = quantity;
        this->bill = bill;
        this->orderId = orderId;
        this->left = NULL;
        this->right = NULL;
    }
};

takeAway* root = NULL; // Root of the AVL tree

// Function to display a single take-away order
void display(takeAway* root) {
    cout << "\n----------------------------------" << endl;
    cout << "Name :" << root->name << endl;
    cout << "Product :" << root->product << endl;
    cout << "Quantity : " << root->quantity << endl;
    cout << "Bill : " << root->bill << endl;
    cout << "Order ID: " << root->orderId << endl;
    cout << "-----------------------------------\n" << endl;
}

// Function to display all take-away orders in sorted order
// (in-order traversal of the AVL tree)
takeAway* displayTakeAway(takeAway* root) {
    if (root) {
        displayTakeAway(root->left);
        display(root);
        displayTakeAway(root->right);
    }
    return root;
}

// Function to check if the AVL tree is empty
int isEmpty(takeAway* root) {
    return root == NULL;
}

// Function to calculate the height of the AVL tree
int height(takeAway* root) {
    if (root == NULL)
        return -1;
    else {
        int leftH = height(root->left);
        int rightH = height(root->right);
        return (1 + max(leftH, rightH));
    }
}

// Function to calculate the balance factor of a node in the AVL tree
int balanceFactor(takeAway* root) {
    if (!root)
        return 0;
    return height(root->left) - height(root->right);
}

// Helper function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to search for a specific order by orderId in the AVL tree
takeAway* search(takeAway* root, int id) {
    if (root == NULL) {
        return NULL; // Order not found
    }
    else if (root->orderId == id) {
        return root; // Order found
    }
    else if (root->orderId < id) {
        return search(root->right, id); // Search in the right subtree
    }
    else {
        return search(root->left, id); // Search in the left subtree
    }
}

// Function to perform a Left-Left (LL) rotation
takeAway* LLRotation(takeAway* root) {
    takeAway* x = root->left;
    takeAway* temp = x->right;

    x->right = root;
    root->left = temp;

    root = x;
    return x;
}

// Function to perform a Right-Right (RR) rotation
takeAway* RRRotation(takeAway* root) {
    takeAway* x = root->right;
    takeAway* temp = x->left;

    x->left = root;
    root->right = temp;

    root = x;
    return x;
}

// Function to perform a Left-Right (LR) rotation
takeAway* LRRotation(takeAway* root) {
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// Function to perform a Right-Left (RL) rotation
takeAway* RLRotation(takeAway* root) {
    root->right = LLRotation(root->right);
    return RRRotation(root);
}

// Function to insert a new order into the AVL tree
takeAway* insertion(string name, int quantity, string product, double bill, int orderId, takeAway* root) {
    takeAway* newNode = new takeAway(name, product, quantity, bill, orderId);

    if (root == NULL) {
        root = newNode; // Insert at the root if the tree is empty
    }
    else if (root->orderId > newNode->orderId) {
        root->left = insertion(name, quantity, product, bill, orderId, root->left); // Insert in the left subtree
    }
    else if (root->orderId < newNode->orderId) {
        root->right = insertion(name, quantity, product, bill, orderId, root->right); // Insert in the right subtree
    }
    else {
        cout << "No duplicate values are allowed." << endl;
        return root; // Duplicate orderId is not allowed
    }

    // Calculate the balance factor to check if the tree is balanced
    int bf = balanceFactor(root);

    // Perform rotations if necessary
    if (bf == 2) {
        // LL case
        if (root->left->orderId > newNode->orderId) {
            return LLRotation(root);
        }
        // LR case
        if (root->left->orderId < newNode->orderId) {
            return LRRotation(root);
        }
    }
    else if (bf == -2) {
        // RR case
        if (root->right->orderId < newNode->orderId) {
            return RRRotation(root);
        }
        // RL case
        if (root->right->orderId > newNode->orderId) {
            return RLRotation(root);
        }
    }

    return root; // Return the root if no rotation is required
}

// Function to find the node with the minimum value in the AVL tree
takeAway* minValue(takeAway* root) {
    takeAway* current = root;
    while (current->left != NULL) {
        current = current->left; // Traverse to the leftmost node
    }
    return current;
}
takeAway* deleteNode(takeAway* root, int orderId)
{
    if (root == NULL)
        return root;
    else if (orderId < root->orderId)
        root->left = deleteNode(root->left, orderId);
    else if (orderId > root->orderId)
        root->right = deleteNode(root->right, orderId);
    else {
        if (root->left == NULL) {
            takeAway* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            takeAway* temp = root->left;
            delete root;
            return temp;
        }

        else {
            takeAway* temp = minValue(root->right);
            root->orderId = temp->orderId;
            root->right = deleteNode(root->right, temp->orderId);
        }
    }

    // getting the balance factor
    int balance = balanceFactor(root);

    // Rotation Cases
    // LEFT LEFT CASE
    if (balance > 1 && orderId < root->left->orderId)
        return LLRotation(root);

    // LEFT RIGHT CASE
    if (balance > 1 && orderId > root->left->orderId)
    {
        root->left = LLRotation(root->left);
        return LRRotation(root);
    }

    // RIHGT RIGHT CASE
    if (balance < -1 && orderId > root->right->orderId)
        return RRRotation(root);

    // RIGHT LEFT CASE
    if (balance < -1 && orderId < root->right->orderId)
    {
        return RLRotation(root);
    }

    return root;
}





//-----------------------------------------------------------------------------------------------------------------------
void placeOrderHomeDeliveryCustomer(string name, string product, int quantity, double bill, string address, int deliveryCharges, int distanceDelivery)
{

    currentdeliveryUser = new deliveryUser(name, product, quantity, bill, address, deliveryCharges, distanceDelivery);

    if (shop->nextdeliveryUser == NULL)
    {
        // if first insert in front
        shop->nextdeliveryUser = currentdeliveryUser;
    }
    else
    {
        // finding the last Node
        deliveryUser* temp = shop->nextdeliveryUser;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentdeliveryUser;
        currentdeliveryUser->next = NULL;
    }

    cout << "\n***************Order Details***************";
    cout << "\n Customer Name : " << name << "\n Order name : " << product << "\n Quantity : " << quantity << "\n Total bill : " << bill;
    cout << "\n Address : " << address << "\n Distance in km : " << distanceDelivery << "\n Delivery charges : " << deliveryCharges << endl;
}


void displayAllOrdersHomeDeliveryCustomers()
{
    if (shop->nextdeliveryUser == NULL)
    {
        cout << "There is no Order for Home Delivery Customer till yet" << endl;
    }
    else
    {
        deliveryUser* traversal = shop->nextdeliveryUser;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Home Delivery Customer : " << traversal->nUser.name << endl;
            cout << "Product Name : " << traversal->nUser.product << endl;
            cout << "Quantity : " << traversal->nUser.quantity << endl;
            cout << "Delivery Distance : " << traversal->deliveryCharges << "KM" << endl;
            cout << "Delivery Charges : " << traversal->distanceDelivery << endl;
            cout << "Bill : " << traversal->nUser.bill << " RS/_" << endl;
            cout << "Delivery Address : " << traversal->address << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }

}





//-----------------------------------------------------------------------------------

int minDistance(int dist[], bool visited[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}



void dijkstra(int graph[V][V], int dist[], int src)
{
    bool visited[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);

        visited[u] = true;

        for (int v = 0; v < V; v++)

            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

//-----------------------------------------------------------------------------------

int minKey(int distanceP[], bool visitedP[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V1; v++)
        if (visitedP[v] == false && distanceP[v] < min)
            min = distanceP[v], min_index = v;

    return min_index;
}

void printMST(int parent[], int graph[V1][V1])
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V1; i++)
        cout << parent[i] << " - " << i << " \t"
        << graph[i][parent[i]] << " \n";
}

void prims(int graph[V1][V1], int distanceP[])
{
    int parent[V1];
    bool visitedP[V1];

    for (int i = 0; i < V1; i++)
        distanceP[i] = INT_MAX, visitedP[i] = false;

    distanceP[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V1 - 1; count++) {

        int u = minKey(distanceP, visitedP);

        visitedP[u] = true;

        for (int v = 0; v < V1; v++)

            if (graph[u][v] && visitedP[v] == false && graph[u][v] < distanceP[v])
                parent[v] = u, distanceP[v] = graph[u][v];
    }

}






//-----------------------------------------------------------------------------------


string CityName[] = { "WareHouse", "Islamabad", "Lahore", "Karachi", "Multan", "Peshawar", "Quetta", "Abbotabad", "Skardu", "Gawadar", "Liaquat Bagh" };

string Abbotabad[] = { "Abbotabad", "Comsats Atd", "PMA", "PC Hotel", "Ayub Medical College", "Fawara Chowk" };

string Islamabad[] = { "Islamabad", "I-8" ,"Askari-14", "F-10", "F-7", "H-12" };

string Lahore[] = { "Lahore", "Johar Town", "Garden Town", "DHA", "Model Town", "Bahria Lahore" };

string Karachi[] = { "karachi", "Bharia Twon", "North Nazimabad", "Defence", "Clifton", "Liyari" };

int graph[V][V] = { {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 3},   //Warehouse
                    {4, 0, 0, 0, 0, 0, 0, 6, 0, 0, 2},	 //Islamabad
                    {0, 0, 0, 0, 9, 4, 0, 0, 0, 0, 11},	 //Lahore
                    {0, 0, 0, 0, 1, 0, 0, 0, 16, 5, 0},	 //Karachi
                    {0, 0, 9, 1, 0, 8, 13, 0, 10, 6, 0}, //Multan	
                    {0, 0, 4, 0, 8, 0, 0, 3, 17, 0, 7},	 //Peshawar
                    {0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 7},	 //Quetta
                    {0, 6, 0, 0, 0, 3, 0, 0, 5, 0, 0},	 //Abbotabad
                    {0, 0, 0, 16, 10, 17, 0, 5, 0, 0, 0},//Skardu
                    {0, 0, 0, 5, 6, 0, 0, 0, 0, 0, 0},	 //Gawadar
                    {3, 2, 11, 0, 0, 7, 7, 0, 0, 0, 0} };//Liaquat Bhag

//----------------------Abbotabad--------------------------------				
int AtdGraph[V1][V1] = { { 0, 4, 4, 0, 0, 0 },
                        { 4, 0, 2, 0, 0, 0 },   //comsats
                        { 4, 2, 0, 3, 2, 4 },	//PMA
                        { 0, 0, 3, 0, 0, 3 },	//PC
                        { 0, 0, 2, 0, 0, 3 },	//Ayub
                        { 0, 0, 4, 3, 3, 0 } };	//Fawara

//---------------------Islamabad------------------------------------
int IsbGraph[V1][V1] = { { 0, 4, 0, 2, 0, 0 },
                        { 4, 0, 3, 1, 0, 6 },	//I-8
                        { 0, 3, 0, 4, 0, 7 },	//Askari
                        { 2, 1, 4, 0, 9, 0 },	//F-10
                        { 0, 0, 0, 9, 0, 5 },	//F-7
                        { 0, 6, 7, 0, 5, 0 } };	//H-12

//-----------------------Lahore---------------------------------------
int LhrGraph[V1][V1] = { { 0, 9, 15, 6, 0, 0 },
                        { 9, 0, 7, 0, 0, 8 },
                        { 15, 7, 0, 8, 9, 5 },
                        { 6, 0, 8, 0, 11, 0 },
                        { 0, 0, 9, 11, 0, 0 },
                        { 0, 8, 5, 0, 0, 0 } };	//Comsats Lahore

//----------------------Karachi----------------------------------------
int KarGraph[V1][V1] = { { 0, 6, 3, 0, 0, 1 },
                        { 6, 0, 0, 2, 0, 5 },	//Bharia Town
                        { 3, 0, 0, 0, 3, 5 },	//North Nazimabad
                        { 0, 2, 0, 0, 6, 4 },	//Defence
                        { 0, 0, 3, 6, 0, 6 },	//Clifton
                        { 1, 5, 5, 4, 6, 0 } };	//Liyari

//----------------------------------------------------------------------------------

int city() {
    int opt;
    cout << "\nThe delivery is available for following Areas : \n" << endl;

    cout << "\n---------------------------------";
    cout << "\n |CITY CODE |        City       |";
    cout << "\n---------------------------------";
    cout << "\n |     1    |    Islamabad      |" << endl;
    cout << "\n |     2    |    Lahore         |" << endl;
    cout << "\n |     3    |    Karachi        |" << endl;
    cout << "\n |     4    |    Multan         |" << endl;
    cout << "\n |     5    |    Peshawar       |" << endl;
    cout << "\n |     6    |    Quetta         |" << endl;
    cout << "\n |     7    |    Abbotabad      |" << endl;
    cout << "\n |     8    |    Skardu         |" << endl;
    cout << "\n |     9    |    Gawadar        |" << endl;
    cout << "\n |    10    |    Liaquat Bhag   |" << endl;
    cout << "---------------------------------\n" << endl;



    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
}




int isb() {
    int opt;
    cout << "\nThe delivery is available for following Areas in Islamabad: " << endl;

    cout << "\n---------------------------------";
    cout << "\n |CITY CODE |        AREA       |";
    cout << "\n---------------------------------";
    cout << "\n |     1    |    I-8            |" << endl;
    cout << "\n |     2    |    Askari-14      |" << endl;
    cout << "\n |     3    |    F-10           |" << endl;
    cout << "\n |     4    |    F-7            |" << endl;
    cout << "\n |     5    |    H-12           |" << endl;
    cout << "---------------------------------\n" << endl;


    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;

}

int Atd() {
    int opt;
    cout << "\nThe delivery is available for following Areas in Abbotabad: " << endl;

    cout << "\n---------------------------------";
    cout << "\n |CITY CODE |        AREA       |";
    cout << "\n---------------------------------";
    cout << "\n |     1    |    Bahria Atd    |" << endl;
    cout << "\n |     2    |    PMA            |" << endl;
    cout << "\n |     3    |    PC-Hotel       |" << endl;
    cout << "\n |     4    |    Ayub Medical   |" << endl;
    cout << "\n |     5    |    Fawara Chowk   |" << endl;
    cout << "---------------------------------\n" << endl;

    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;

}

int Lhr() {
    int opt;
    cout << "\nThe delivery is available for following Areas in Lahore: " << endl;

    cout << "\n---------------------------------";
    cout << "\n |CITY CODE |        AREA       |";
    cout << "\n---------------------------------";
    cout << "\n |     1    |    Johar Town     |" << endl;
    cout << "\n |     2    |    Garden Town    |" << endl;
    cout << "\n |     3    |    DHA            |" << endl;
    cout << "\n |     4    |    Model Town     |" << endl;
    cout << "\n |     5    |    Comsats LHR    |" << endl;
    cout << "---------------------------------\n" << endl;


    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;

}

int Kar() {
    int opt;
    cout << "\nThe delivery is available for following Areas in Karachi: " << endl;

    cout << "\n---------------------------------";
    cout << "\n |CITY CODE |        AREA       |";
    cout << "\n---------------------------------";
    cout << "\n |     1    |    Bharia Town    |" << endl;
    cout << "\n |     2    |    North Nazimabad|" << endl;
    cout << "\n |     3    |    Defence        |" << endl;
    cout << "\n |     4    |    Clifton        |" << endl;
    cout << "\n |     5    |    Liyari         |" << endl;
    cout << "---------------------------------\n" << endl;

    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;

}
// Function to handle further area selection based on city option
int FurthurArea(int option) {
    int opt;
    switch (option) {

    case 1: // Islamabad
    {
        prims(IsbGraph, distanceP); // Perform Prim's algorithm for Islamabad graph
        opt = isb();               // Get the specific area in Islamabad
        addressF = Islamabad[opt]; // Set the address based on the selected area
    }
    break;

    case 2: // Lahore
    {
        prims(LhrGraph, distanceP);
        opt = Lhr();
        addressF = Lahore[opt];
    }
    break;

    case 3: // Karachi
    {
        prims(KarGraph, distanceP);
        opt = Kar();
        addressF = Karachi[opt];
    }
    break;

    case 7: // Abbottabad
    {
        prims(AtdGraph, distanceP);
        opt = Atd();
        addressF = Abbotabad[opt];
    }
    break;
    }

    return opt; // Return the selected area option
}

//---------------------------------------------------------------------------------------------

int main() {
    // Initialize shop details
    shop = new Shop;
    shop->name = "WareHouse";
    shop->address = "Bahria University (E-8 ISLAMABAD)";

    // List of products and their prices
    shop->product = new string[11]{ "","Sony FX30          ", "Sony FR7           ", "Canon EOS 90D      ",
                                 "Nikon D6           ", "Panasonic Lumix G10","Canon EOS 250D     ",
                                  "Sony Alpha 7       ", "Nikon D750         ", "Panasonic Lumix GH5",
                                "Canon EOS 5D Mark " };

    shop->price = new int[11] {0, 45500, 175000, 289000, 155700, 75000, 210000, 199999, 100000, 45000, 500000};

    int choice = -99;

    do {
        // Display shop information and menu options
        cout << endl;
        cout << "************************  " << shop->name << "  ************************" << endl;
        cout << "Location : " << shop->address << endl;
        cout << endl;

        cout << endl;
        cout << "************************  Operations  ************************" << endl;
        cout << endl;

        // Menu options
        cout << "1. Display the product and prices" << endl;
        cout << "2. Place order for Take-Away from Warehouse" << endl;
        cout << "3. Place order for Home Delivery " << endl;
        cout << "4. Get Order from Warehouse" << endl;
        cout << "5. Display all Delivery Orders" << endl;
        cout << "6. Display all Take-Away Orders" << endl;
        cout << "0.  EXIT " << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        // Variables for customer and order details
        string name;
        int quantity;
        int productNumber;
        double bill;
        string address;
        int orderId;
        int distance;

        switch (choice) {

        case 1: // Display products and prices
        {
            cout << "\n---------------------------------------------------------------------";
            cout << "\n | ITEM NO. |             ITEM NAME               | ORIGINAL PRICE  |";
            cout << "\n---------------------------------------------------------------------";
            for (int i = 1; i <= 10; ++i) {
                cout << "\n |    " << i << "     |  " << shop->product[i] << "|       " << shop->price[i] << "     |";
            }
            cout << "\n---------------------------------------------------------------------" << endl;
        }
        break;

        case 2: // Place Take-Away order
        {
            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the product Number: ";
            cin >> productNumber;
            cout << "Enter the quantity of the product: ";
            cin >> quantity;
            cout << "Enter orderID of one or two letters: ";
            cin >> orderId;

            bill = quantity * shop->price[productNumber];
            root = insertion(name, quantity, shop->product[productNumber], bill, orderId, root);
            cout << "\n------------------------------------" << endl;
            cout << "**** Your order has been placed *****" << endl;
            cout << "Total amount : " << bill << endl;
            cout << "Order ID :" << orderId << endl;
            cout << "You can get your order from Warehouse " << endl;
            cout << "-------------------------------------\n" << endl;
        }
        break;

        case 3: // Place Home Delivery order
        {
            dijkstra(graph, dist, 0); // Compute shortest distances from the warehouse

            do {
                optionDelivery = city(); // Select the city
            } while (!(optionDelivery >= 0 && optionDelivery <= 10));

            if (optionDelivery == 1 || optionDelivery == 2 || optionDelivery == 3 || optionDelivery == 7) {
                do {
                    optionDelivery1 = FurthurArea(optionDelivery); // Select specific area in the city
                } while (!(optionDelivery1 >= 0 && optionDelivery1 <= 5));

                address = CityName[optionDelivery] + " " + addressF;
                distance = dist[optionDelivery] + distanceP[optionDelivery1];
            }
            else {
                address = CityName[optionDelivery];
                distance = dist[optionDelivery];
            }

            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the product Number: ";
            cin >> productNumber;
            cout << "Enter the quantity of the product: ";
            cin >> quantity;

            int deliveryChargesPerKM = 20;
            int deliveryCharges = deliveryChargesPerKM * distance;
            bill = quantity * shop->price[productNumber] + deliveryCharges;

            placeOrderHomeDeliveryCustomer(name, shop->product[productNumber], quantity, bill, address, deliveryCharges, distance);
        }
        break;

        case 4: // Get Take-Away order from Warehouse
        {
            cout << "Enter the Order Id: ";
            cin >> orderId;

            takeAway* cust = search(root, orderId); // Search for the order by ID

            if (cust == NULL) {
                cout << "\n----------------------------------" << endl;
                cout << "No such order is in the Warehouse " << endl;
                cout << "-----------------------------------\n" << endl;
            }
            else {
                root = deleteNode(root, orderId); // Remove the order from the list
                cout << "\n----------------------------------" << endl;
                cout << "Your order is ready for collection" << endl;
                cout << "  Please get it from the counter" << endl;
                cout << "-----------------------------------\n" << endl;
            }
        }
        break;

        case 5: // Display all Home Delivery orders
        {
            displayAllOrdersHomeDeliveryCustomers();
        }
        break;

        case 6: // Display all Take-Away orders
        {
            displayTakeAway(root);
        }
        break;

        }

    } while (choice != 0); // Repeat until the user exits

    cout << "Thank you for Using our Services " << endl;

    return 0;
}
