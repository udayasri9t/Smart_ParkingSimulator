#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SLOTS 10

typedef struct {
    int slot_number;
    char vehicle_number[20];
    int occupied;
} ParkingSlot;

ParkingSlot parking[MAX_SLOTS];

void initialize_slots() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        parking[i].slot_number = i + 1;
        strcpy(parking[i].vehicle_number, "None");
        parking[i].occupied = 0;
    }
}

void update_dashboard() {
    FILE *file = fopen("dashboard.html", "w");
    fprintf(file,
        "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
        "<meta http-equiv='refresh' content='5'>"
        "<title>Smart Parking Dashboard</title>"
        "<style>"
        "body { font-family: 'Segoe UI', sans-serif; background: #f8f9fa; color: #333; padding: 20px; }"
        "h2 { text-align: center; color: #1b2a49; }"
        "table { border-collapse: collapse; width: 90%%; margin: 30px auto; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }"
        "th, td { padding: 14px; text-align: center; font-size: 16px; }"
        "th { background-color: #1b2a49; color: #f0c330; letter-spacing: 1px; }"
        "tr:nth-child(even) { background-color: #f2f2f2; }"
        ".occupied { background-color: #ffe0e0; color: #b30000; font-weight: bold; }"
        ".available { background-color: #e0ffe0; color: #007e33; font-weight: bold; }"
        "td { border-bottom: 1px solid #ddd; }"
        "</style></head><body>"
        "<h2>🚗 Smart Parking Slot Dashboard 🚗</h2><table>"
        "<tr><th>Slot Number</th><th>Vehicle Number</th><th>Status</th></tr>");

    for (int i = 0; i < MAX_SLOTS; i++) {
        fprintf(file,
            "<tr class='%s'><td>%d</td><td>%s</td><td>%s</td></tr>",
            parking[i].occupied ? "occupied" : "available",
            parking[i].slot_number,
            parking[i].vehicle_number,
            parking[i].occupied ? "Occupied" : "Available");
    }

    fprintf(file, "</table></body></html>");
    fclose(file);

    system("start dashboard.html");  // Windows only; use "xdg-open" for Linux
}

void park_vehicle(const char *vehicle_number) {
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (!parking[i].occupied) {
            parking[i].occupied = 1;
            strcpy(parking[i].vehicle_number, vehicle_number);
            break;
        }
    }
    update_dashboard();
}

void remove_vehicle(const char *vehicle_number) {
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (parking[i].occupied && strcmp(parking[i].vehicle_number, vehicle_number) == 0) {
            parking[i].occupied = 0;
            strcpy(parking[i].vehicle_number, "None");
            break;
        }
    }
    update_dashboard();
}

void run_menu() {
    int choice;
    char vehicle_number[20];

    do {
        printf("\n======= Smart Parking Simulator =======\n");
        printf("1. Park a Vehicle\n");
        printf("2. Remove a Vehicle\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter vehicle number: ");
                scanf("%s", vehicle_number);
                park_vehicle(vehicle_number);
                break;
            case 2:
                printf("Enter vehicle number to remove: ");
                scanf("%s", vehicle_number);
                remove_vehicle(vehicle_number);
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);
}

int main() {
    initialize_slots();
    update_dashboard(); // show initial empty dashboard
    run_menu();
    return 0;
}

