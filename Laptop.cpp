
class Laptop
{
private:             // Access specifier
    int customer_id;        // Attribute (int variable)
    int order_number;
    int laptop_type;
    int engineer_id;
    int expert_id;

public:
    Laptop(int customerId, int orderNumber, int laptopType, int engineerId, int expertId) {     // Constructor
        customer_id = customerId;
        order_number = orderNumber;
        laptop_type = laptopType;
        engineer_id = engineerId;
        expert_id = expertId;

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

    int getEngineerId() {
        return engineer_id;
    }
    int getExpertId() {
        return expert_id;
    }

};