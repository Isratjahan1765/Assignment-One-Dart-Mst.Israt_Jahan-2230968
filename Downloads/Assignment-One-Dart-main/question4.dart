// Question 4: Inheritance & Polymorphism (Difficulty: 4/5) ⭐⭐⭐⭐
/**
 * EXPECTED OUTPUT:
 * Vehicle Info: 2020 Toyota Camry (4 doors)
 * Starting the car engine...
 * Stopping the car engine...
 * 
 * Vehicle Info: 2021 Honda CBR (Has windshield: true)
 * Starting the motorcycle engine...
 * Stopping the motorcycle engine...
 * 
 * Car age: <Value> years
 * Motorcycle age: <Value> years
 */

// 1. Abstract Class Vehicle:
//    - Properties: String brand, String model, int year
//    - Abstract method: void start()
//    - Abstract method: void stop()
//    - Concrete method: void displayInfo()
abstract class Vehicle {
  String brand;
  String model;
  int year;

  Vehicle(this.brand, this.model, this.year);

  // Abstract methods
  void start();
  void stop();

  // Concrete method
  void displayInfo() {
    print("Vehicle Info: $year $brand $model");
  }

  // Add a method to calculate vehicle age (current year - vehicle year)
  int calculateAge() {
    // TODO: Calculate and return vehicle age
    return DateTime.now().year - year;
  }
}

// 2. Concrete Classes:
//    - Car extends Vehicle
//      - Additional property: int numberOfDoors
//      - Override start() and stop() methods
class Car extends Vehicle {
  int numberOfDoors;

  Car(String brand, String model, int year, this.numberOfDoors)
      : super(brand, model, year);

  @override
  void start() {
    // TODO: Implement car start method
    print("Starting the car engine...");
  }

  @override
  void stop() {
    // TODO: Implement car stop method
    print("Stopping the car engine...");
  }

  @override
  void displayInfo() {
    // TODO: Override to show car-specific info as shown in expected output
    print("Vehicle Info: $year $brand $model ($numberOfDoors doors)");
  }
}

//    - Motorcycle extends Vehicle
//      - Additional property: bool hasWindshield
//      - Override start() and stop() methods
class Motorcycle extends Vehicle {
  bool hasWindshield;

  Motorcycle(String brand, String model, int year, this.hasWindshield)
      : super(brand, model, year);

  @override
  void start() {
    // TODO: Implement motorcycle start method
    print("Starting the motorcycle engine...");
  }

  @override
  void stop() {
    // TODO: Implement motorcycle stop method
    print("Stopping the motorcycle engine...");
  }

  @override
  void displayInfo() {
    // TODO: Override to show motorcycle-specific info as shown in expected output
    print(
        "Vehicle Info: $year $brand $model (Has windshield: $hasWindshield)");
  }
}

void main() {
  // 3. Create a list of vehicles and demonstrate polymorphism by calling start(), stop(), and displayInfo() on each vehicle
  // TODO: Create a list containing one Car and one Motorcycle

  // TODO: Loop through the list and call displayInfo(), start(), and stop()

  // TODO: Print the age of each vehicle using calculateAge()
  List<Vehicle> vehicles = [
    Car("Toyota", "Camry", 2020, 4),
    Motorcycle("Honda", "CBR", 2021, true),
  ];

  for (Vehicle vehicle in vehicles) {
    vehicle.displayInfo();
    vehicle.start();
    vehicle.stop();
    print("");
  }

  print("Car age: ${vehicles[0].calculateAge()} years");
  print("Motorcycle age: ${vehicles[1].calculateAge()} years");
}
