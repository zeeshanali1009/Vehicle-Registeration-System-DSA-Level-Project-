#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

struct Vehicle
{
    string registrationNumber;
    string make;
    string model;
    int year;
    Vehicle* next;
};

void exchangeValues(Vehicle& a, Vehicle& b)
{
    Vehicle temp = a;
    a = b;
    b = temp;
}

void bubbleSortAscending(Vehicle* arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j].registrationNumber > arr[j + 1].registrationNumber)
            {
                exchangeValues(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubbleSortDescending(Vehicle* arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j].registrationNumber < arr[j + 1].registrationNumber)
            {
                exchangeValues(arr[j], arr[j + 1]);
            }
        }
    }
}

class VehicleRegister
{
private:
    Vehicle* head;
    bool authenticated;

public:
    VehicleRegister() : head(NULL), authenticated(false) {}

    Vehicle* getHead() const
    {
        return head;
    }

    void authenticateUser()
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (username == "admin" && password == "admin123")
        {
            authenticated = true;
            cout << "Authentication successful!\n";
        }
        else
        {
            authenticated = false;
            cout << "Authentication failed. Incorrect username or password.\n";
        }
    }

    void addVehicle(const string& regNumber, const string& make, const string& model, int year) 
	{
        if (!authenticated) 
		{
            cout << "Authentication required. Please authenticate first.\n";
            return;
        }

        if (searchVehicle(regNumber) != NULL) 
		{
            cout << "Registration number already exists. Cannot add the vehicle.\n";
            return;
        }

        Vehicle* newVehicle = new Vehicle;
        newVehicle->registrationNumber = regNumber;
        newVehicle->make = make;
        newVehicle->model = model;
        newVehicle->year = year;
        newVehicle->next = NULL;

        if (head == NULL) 
		{
            head = newVehicle;
        }
        else 
		{
            Vehicle* temp = head;
            while (temp->next != NULL) 
			{
                temp = temp->next;
            }
            temp->next = newVehicle;
        }

        cout << "Vehicle added successfully.\n";
    }


    void displayVehicles()
    {
        if (!authenticated)
        {
            cout << "Authentication required. Please authenticate first.\n";
            return;
        }
        if (head == NULL)
        {
            cout << "No vehicles in the register.\n";
        }
        else
        {
            cout << "Vehicle Register:\n";
            Vehicle* temp = head;
            while (temp != NULL)
            {
                cout << "Registration Number: " << temp->registrationNumber << "\n";
                cout << "Make: " << temp->make << "\n";
                cout << "Model: " << temp->model << "\n";
                cout << "Year: " << temp->year << "\n";
                cout << "------------------------\n";
                temp = temp->next;
            }
        }
    }

    Vehicle* searchVehicle(const string& regNumber)
    {
        if (!authenticated)
        {
            cout << "Authentication required. Please authenticate first.\n";
            return NULL;
        }
        Vehicle* temp = head;
        while (temp != NULL)
        {
            if (temp->registrationNumber == regNumber)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void updateVehicle(const string& regNumber)
    {
        if (!authenticated)
        {
            cout << "Authentication required. Please authenticate first.\n";
            return;
        }
        Vehicle* vehicleToUpdate = searchVehicle(regNumber);
        if (vehicleToUpdate != NULL)
        {
            cout << "Enter new make: ";
            cin >> vehicleToUpdate->make;
            cout << "Enter new model: ";
            cin >> vehicleToUpdate->model;
            cout << "Enter new year: ";
            cin >> vehicleToUpdate->year;
            cout << "Vehicle details updated successfully.\n";
        }
        else
        {
            cout << "Vehicle not found.\n";
        }
    }

    void deleteVehicle(const string& regNumber)
    {
        if (!authenticated)
        {
            cout << "Authentication required. Please authenticate first.\n";
            return;
        }
        Vehicle* current = head;
        Vehicle* previous = NULL;
        while (current != NULL)
        {
            if (current->registrationNumber == regNumber)
            {
                if (previous != NULL)
                {
                    previous->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                delete current;
                cout << "Vehicle deleted successfully.\n";
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Vehicle not found.\n";
    }

    void displayVehicleDetails(const Vehicle* vehicle)
    {
        if (!authenticated)
        {
            cout << "Authentication required. Please authenticate first.\n";
            return;
        }
        if (vehicle != NULL)
        {
            cout << "Vehicle Details:\n";
            cout << "Registration Number: " << vehicle->registrationNumber << "\n";
            cout << "Make: " << vehicle->make << "\n";
            cout << "Model: " << vehicle->model << "\n";
            cout << "Year: " << vehicle->year << "\n";
        }
        else
        {
            cout << "Vehicle not found.\n";
        }
    }

    void searchByMake(const string& makeToSearch)
    {
        if (!authenticated)
        {
            cout << "Authentication required. Please authenticate first.\n";
            return;
        }
        bool found = false;
        Vehicle* temp = head;
        while (temp != NULL)
        {
            if (temp->make == makeToSearch)
            {
                cout << "Vehicle Found:\n";
                cout << "Registration Number: " << temp->registrationNumber << "\n";
                cout << "Make: " << temp->make << "\n";
                cout << "Model: " << temp->model << "\n";
                cout << "Year: " << temp->year << "\n";
                cout << "------------------------\n";
                found = true;
            }
            temp = temp->next;
        }
        if (!found)
        {
            cout << "No vehicles found with the specified make.\n";
        }
    }

    void sortVehiclesByRegistrationNumber(Vehicle* arr, int n, bool ascending)
    {
        if (n <= 1)
        {
            cout << "Not enough vehicles to sort.\n";
            return;
        }
        if (ascending)
        {
            bubbleSortAscending(arr, n);
            cout << "Vehicles sorted by registration number in ascending order.\n";
        }
        else
        {
            bubbleSortDescending(arr, n);
            cout << "Vehicles sorted by registration number in descending order.\n";
        }
    }

    void displayVehiclesFromArray(Vehicle* arr, int n)
    {
        if (head == NULL)
        {
            cout << "No vehicles in the register.\n";
        }
        else
        {
            cout << "Sorted Vehicle Register:\n";
            for (int i = 0; i < n; i++)
            {
                cout << "Registration Number: " << arr[i].registrationNumber << "\n";
                cout << "Make: " << arr[i].make << "\n";
                cout << "Model: " << arr[i].model << "\n";
                cout << "Year: " << arr[i].year << "\n";
                cout << "------------------------\n";
            }
        }
    }

    ~VehicleRegister()
    {
        Vehicle* temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int displayExtendedMenu()
{
    cout << "\n\t\t\t\t*************************";
    cout << "\n\t\t\t\t VEHICLE REGISTRATION SYSTEM";
    cout << "\n\t\t\t\t*************************";
    cout << "\n\n\n\t\t\t1. Authenticate User";
    cout << "\n\t\t\t2. Add a Vehicle";
    cout << "\n\t\t\t3. Display Vehicles";
    cout << "\n\t\t\t4. Search for a Vehicle";
    cout << "\n\t\t\t5. Update and Edit Vehicle";
    cout << "\n\t\t\t6. Delete a Vehicle";
    cout << "\n\t\t\t7. Display Vehicle Details";
    cout << "\n\t\t\t8. Search and Retrieval by Make";
    cout << "\n\t\t\t9. Sort Vehicles by Registration Number";
    cout << "\n\t\t\t10. Exit";
    cout << "\n\t\t\t\t\tCompiled by Our Group";
    cout << "\n\nEnter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main()
{
    cout << "\t\t\t=========================================================" << endl;
    cout << "\t\t\t\tZeeshan Ali, Muhammad Ahmed, Faizan Ghani " << endl;
    cout << "\t\t\t=========================================================" << endl;
    cout << "\t\t\t=========================================================" << endl;
    cout << "\t\t\t\t\tVehicle Registration System " << endl;
    cout << "\t\t\t=========================================================" << endl;
    cout << "Press any key to enter into the project " << endl;
    getch();
    system("cls");

    VehicleRegister registerSystem;

    int choice;
    do
    {
        choice = displayExtendedMenu();

        switch (choice)
        {
        case 1:
            registerSystem.authenticateUser();
            break;
        case 2:
        {
            string regNumber, make, model;
            int year;
            cout << "Enter Registration Number: ";
            cin >> regNumber;
            cout << "Enter Make: ";
            cin >> make;
            cout << "Enter Model: ";
            cin >> model;
            cout << "Enter Year: ";
            cin >> year;
            registerSystem.addVehicle(regNumber, make, model, year);
            break;
        }
        case 3:
            registerSystem.displayVehicles();
            break;
        case 4:
        {
            string regNumber;
            cout << "Enter Registration Number to search: ";
            cin >> regNumber;
            Vehicle* foundVehicle = registerSystem.searchVehicle(regNumber);
            registerSystem.displayVehicleDetails(foundVehicle);
            break;
        }
        case 5:
        {
            string regNumber;
            cout << "Enter Registration Number to update: ";
            cin >> regNumber;
            registerSystem.updateVehicle(regNumber);
            break;
        }
        case 6:
        {
            string regNumber;
            cout << "Enter Registration Number to delete: ";
            cin >> regNumber;
            registerSystem.deleteVehicle(regNumber);
            break;
        }
        case 7:
        {
            string regNumber;
            cout << "Enter Registration Number to display details: ";
            cin >> regNumber;
            Vehicle* foundVehicle = registerSystem.searchVehicle(regNumber);
            registerSystem.displayVehicleDetails(foundVehicle);
            break;
        }
        case 8:
        {
            string makeToSearch;
            cout << "Enter Make to search: ";
            cin >> makeToSearch;
            registerSystem.searchByMake(makeToSearch);
            break;
        }
        case 9:
        {
            cout << "Choose sorting order:\n";
            cout << "1. Ascending\n";
            cout << "2. Descending\n";
            int sortingOrder;
            cin >> sortingOrder;

            int numVehicles = 0;
            Vehicle* temp = registerSystem.getHead();
            while (temp != NULL)
            {
                numVehicles++;
                temp = temp->next;
            }

            Vehicle* vehiclesArray = new Vehicle[numVehicles];

            temp = registerSystem.getHead();
            for (int i = 0; i < numVehicles; i++)
            {
                vehiclesArray[i] = *temp;
                temp = temp->next;
            }

            if (sortingOrder == 1)
            {
                registerSystem.sortVehiclesByRegistrationNumber(vehiclesArray, numVehicles, true);
            }
            else if (sortingOrder == 2)
            {
                registerSystem.sortVehiclesByRegistrationNumber(vehiclesArray, numVehicles, false);
            }

            registerSystem.displayVehiclesFromArray(vehiclesArray, numVehicles);

            delete[] vehiclesArray;

            break;
        }
        case 10:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}

