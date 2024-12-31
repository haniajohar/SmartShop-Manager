# Warehouse Ordering System

## Overview
This C++ program simulates an ordering system for a warehouse that offers products with options for both **Take-Away** and **Home Delivery** services. Customers can place orders, view products, and manage their orders by interacting with the system.

## Features
- **Product Listing**: Display a list of products available for sale along with their prices.
- **Take-Away Orders**: Customers can place Take-Away orders and retrieve them from the warehouse.
- **Home Delivery Orders**: Customers can place Home Delivery orders, with the system calculating delivery charges based on the distance.
- **Order Management**: Ability to retrieve Take-Away orders, view all Home Delivery orders, and display all Take-Away orders.
- **Dynamic Data Structure**: Orders are stored using a linked list for Take-Away orders and other data structures for Home Delivery orders.

## Requirements
- C++ Compiler (C++11 or later recommended)
- No external libraries required

## Program Flow
1. **Menu Options**:
    - Display products and their prices.
    - Place a Take-Away order.
    - Place a Home Delivery order.
    - Get a Take-Away order from the warehouse.
    - Display all Home Delivery orders.
    - Display all Take-Away orders.
    - Exit the program.

2. **Take-Away Orders**: 
    - Customer enters their name, product number, quantity, and order ID.
    - The order is placed in the linked list, and the customer can collect it from the warehouse.

3. **Home Delivery Orders**:
    - Customer enters their name, product number, quantity, and delivery address.
    - Delivery charges are calculated based on distance from the warehouse.
    - The order is stored and displayed in the list of Home Delivery orders.

4. **Order Retrieval**:
    - Customers can retrieve Take-Away orders using the order ID.

## Data Structures
- **Linked List**: Used to store and manage Take-Away orders, allowing efficient addition, retrieval, and deletion of orders.
- **Graph**: Used for calculating distances for Home Delivery orders using Dijkstra's algorithm.
- **Arrays**: Used to store product details such as names and prices.

## How to Use
1. **Run the Program**:
   - Compile and run the program using a C++ compiler:
     ```bash
     g++ -o warehouse_system warehouse_system.cpp
     ./warehouse_system
     ```

2. **Menu Interaction**:
   - The program will display a menu with various options.
   - Enter your choice to view products, place an order, or manage orders.

3. **Placing an Order**:
   - For **Take-Away** orders, enter your details and choose a product.
   - For **Home Delivery** orders, select a delivery city and enter your address. The system will calculate the delivery charges.

4. **Managing Orders**:
   - Retrieve Take-Away orders using the order ID.
   - View all Home Delivery or Take-Away orders as needed.

## Example Usage
### Menu:
************************ WareHouse ************************ 
Location: Bahria University (E-8 ISLAMABAD)
************************ Operations ************************

Display the product and prices
Place order for Take-Away from Warehouse
Place order for Home Delivery
Get Order from Warehouse
Display all Delivery Orders
Display all Take-Away Orders
EXIT Enter your choice:

### Example Order Flow:
1. **Display Products**: Choose option `1` to see the available products and their prices.
2. **Place Take-Away Order**: Choose option `2`, enter your details, and the order will be placed.
3. **Place Home Delivery Order**: Choose option `3`, enter your details, and the delivery charges will be calculated.
4. **Retrieve Take-Away Order**: Choose option `4`, enter the order ID to pick up your order.
5. **View Orders**: Choose options `5` or `6` to view all Home Delivery or Take-Away orders.

## Code Explanation
- **`main()`**: The main function that runs the menu loop and handles user inputs for different operations.
- **`insertion()`**: Function to insert a Take-Away order into the linked list.
- **`search()`**: Function to search for a Take-Away order by its order ID.
- **`deleteNode()`**: Function to delete a Take-Away order from the linked list when retrieved.
- **`placeOrderHomeDeliveryCustomer()`**: Function to place a Home Delivery order and calculate the total bill including delivery charges.
- **`dijkstra()`**: Implements Dijkstra's algorithm to calculate the shortest delivery distance.
- **`displayTakeAway()`**: Function to display all Take-Away orders.

## Contributing
Feel free to fork the repository, submit issues, and create pull requests. Contributions are welcome!

## Author
[Hania Johar] - [haniajohar]([https://github.com/yourusername])
