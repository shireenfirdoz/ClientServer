
class Order
{
private:             // Access specifier
    int customer_id;        // Attribute (int variable)
    int order_number;
    int laptop_type;

public:
    Order(int customerId, int orderNumber, int laptopType) {     // Constructor
        customer_id = customerId;
        order_number = orderNumber;
        laptop_type = laptopType;
    }
    // Getter
    int getCustomerId() {
        return customer_id;
    }
    int getOrderNumber() {
        return order_number;
    }
    int getLaptopType() {
        return laptop_type;
    }

    //copy operator..copy through pointer

};
