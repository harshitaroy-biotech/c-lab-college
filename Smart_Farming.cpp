#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <memory>

using namespace std;

class Advisory {
public:
    virtual void giveAdvice() const = 0; // Pure virtual function
    virtual ~Advisory() {}
};

class Crop {
protected:
    string name;
    double area;          
    string season;
    double yieldPerAcre;  

    static int cropCount; 

public:
    
    Crop() : name("Unknown"), area(0.0), season("N/A"), yieldPerAcre(0.0) {
        cropCount++;
    }

    Crop(string n, double a, string s, double y) : name(n), season(s) {
        if (a <= 0 || y < 0) {
            throw invalid_argument("Area must be greater than zero and yield cannot be negative!"); // Requirement 9: Exception handling
        }
        area = a;
        yieldPerAcre = y;
        cropCount++;
    }

    
    virtual ~Crop() {
        cropCount--;
    }

    string getName() const { return name; }
    double getArea() const { return area; }
    string getSeason() const { return season; }
    double getYieldPerAcre() const { return yieldPerAcre; }


    virtual double calculateTotalYield() const = 0;
    virtual void displayDetails() const = 0;
    virtual void saveToFile(ofstream &outFile) const = 0;

    bool operator>(const Crop &other) const {
        return this->calculateTotalYield() > other.calculateTotalYield();
    }

    static int getCropCount() {
        return cropCount;
    }
};

int Crop::cropCount = 0;

class CerealCrop : public Crop, public Advisory {
private:
    string fertilizerType;

public:
    CerealCrop() : Crop(), fertilizerType("Standard NPK") {}

    CerealCrop(string n, double a, string s, double y, string fert)
        : Crop(n, a, s, y), fertilizerType(fert) {}

    double calculateTotalYield() const override {
        return area * yieldPerAcre;
    }

    void displayDetails() const override {
        cout << left << setw(15) << "Cereal Crop"
             << setw(12) << name
             << setw(10) << area
             << setw(10) << season
             << setw(15) << yieldPerAcre
             << setw(15) << calculateTotalYield()
             << setw(20) << fertilizerType << "\n";
    }

    void giveAdvice() const override {
        cout << "[Advice for " << name << "]: Ensure proper nitrogen soil enrichment and monitor for fungal rust.\n";
    }

    void saveToFile(ofstream &outFile) const override {
        outFile << "Cereal," << name << "," << area << "," << season << "," << yieldPerAcre << "," << fertilizerType << "\n";
    }
};

class VegetableCrop : public Crop, public Advisory {
private:
    int irrigationFrequency; 

public:
    
    VegetableCrop() : Crop(), irrigationFrequency(3) {}

    VegetableCrop(string n, double a, string s, double y, int irriFreq)
        : Crop(n, a, s, y) {
        if (irriFreq < 0) {
            throw invalid_argument("Irrigation frequency cannot be negative!");
        }
        irrigationFrequency = irriFreq;
    }

    
    double calculateTotalYield() const override {
        return area * yieldPerAcre;
    }

    void displayDetails() const override {
        cout << left << setw(15) << "Vegetable Crop"
             << setw(12) << name
             << setw(10) << area
             << setw(10) << season
             << setw(15) << yieldPerAcre
             << setw(15) << calculateTotalYield()
             << setw(20) << (to_string(irrigationFrequency) + " times/week") << "\n";
    }

    void giveAdvice() const override {
        cout << "[Advice for " << name << "]: Requires consistent soil moisture. Watch out for insect infestation.\n";
    }

    void saveToFile(ofstream &outFile) const override {
        outFile << "Vegetable," << name << "," << area << "," << season << "," << yieldPerAcre << "," << irrigationFrequency << "\n";
    }
};

void saveCropsToFile(const vector<shared_ptr<Crop>> &crops, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing!\n";
        return;
    }
    for (const auto &crop : crops) {
        crop->saveToFile(outFile);
    }
    outFile.close();
    cout << "\n[System] All crop records saved successfully to " << filename << "\n";
}

void loadCropsFromFile(vector<shared_ptr<Crop>> &crops, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "[System] No previous record file found (" << filename << "). Starting fresh.\n";
        return;
    }

    string type, name, season, fert;
    double area, yield;
    int irriFreq;
    string line;

    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        
        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, token, ','); area = stod(token);
        getline(ss, season, ',');
        getline(ss, token, ','); yield = stod(token);

        if (type == "Cereal") {
            getline(ss, fert, ',');
            crops.push_back(make_shared<CerealCrop>(name, area, season, yield, fert));
        } else if (type == "Vegetable") {
            getline(ss, token, ','); irriFreq = stoi(token);
            crops.push_back(make_shared<VegetableCrop>(name, area, season, yield, irriFreq));
        }
    }
    inFile.close();
    cout << "[System] Previous crop data loaded successfully.\n";
}

int main() {
    vector<shared_ptr<Crop>> farmStorage;
    const string filename = "farm_data.txt";

    loadCropsFromFile(farmStorage, filename);

    int choice;
    do {

        cout << "      SMART FARM MANAGEMENT SYSTEM       \n";
        cout << "1. Add Cereal Crop\n";
        cout << "2. Add Vegetable Crop\n";
        cout << "3. Display All Crops & Total Yield\n";
        cout << "4. Compare Two Crops by Yield\n";
        cout << "5. Get Smart Farming Advice\n";
        cout << "6. Save & Exit\n";
        cout << "Total Active Crop Records: " << Crop::getCropCount() << "\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice! Please enter a number.\n";
            continue;
        }

        try { 
            if (choice == 1) {
                string name, season, fert;
                double area, yield;

                cout << "Enter Crop Name: "; cin >> name;
                cout << "Enter Area (in acres): "; cin >> area;
                cout << "Enter Season: "; cin >> season;
                cout << "Enter Yield per Acre: "; cin >> yield;
                cout << "Enter Fertilizer Type: "; cin >> fert;

                farmStorage.push_back(make_shared<CerealCrop>(name, area, season, yield, fert));
                cout << "Cereal crop added successfully!\n";

            } else if (choice == 2) {
                string name, season;
                double area, yield;
                int freq;

                cout << "Enter Crop Name: "; cin >> name;
                cout << "Enter Area (in acres): "; cin >> area;
                cout << "Enter Season: "; cin >> season;
                cout << "Enter Yield per Acre: "; cin >> yield;
                cout << "Enter Irrigation Frequency (times/week): "; cin >> freq;

                farmStorage.push_back(make_shared<VegetableCrop>(name, area, season, yield, freq));
                cout << "Vegetable crop added successfully!\n";

            } else if (choice == 3) {
                if (farmStorage.empty()) {
                    cout << "No crop records available.\n";
                    continue;
                }

                cout << "\n" << string(97, '-') << "\n";
                cout << left << setw(15) << "Type"
                     << setw(12) << "Name"
                     << setw(10) << "Area"
                     << setw(10) << "Season"
                     << setw(15) << "Yield/Acre"
                     << setw(15) << "Total Yield"
                     << setw(20) << "Specific Attribute" << "\n";
                cout << string(97, '-') << "\n";

                
                for (const auto &crop : farmStorage) {
                    crop->displayDetails();
                }
                cout << string(97, '-') << "\n";

            } else if (choice == 4) {
                if (farmStorage.size() < 2) {
                    cout << "Need at least 2 crops registered to perform comparison!\n";
                    continue;
                }

                int idx1, idx2;
                cout << "Available indices (1 to " << farmStorage.size() << "):\n";
                for (size_t i = 0; i < farmStorage.size(); ++i) {
                    cout << i + 1 << ". " << farmStorage[i]->getName() << "\n";
                }
                cout << "Select First Crop Index: "; cin >> idx1;
                cout << "Select Second Crop Index: "; cin >> idx2;

                if (idx1 < 1 || idx1 > farmStorage.size() || idx2 < 1 || idx2 > farmStorage.size()) {
                    throw out_of_range("Selected crop indices are invalid!");
                }

                
                if (*farmStorage[idx1 - 1] > *farmStorage[idx2 - 1]) {
                    cout << "\nResult: " << farmStorage[idx1 - 1]->getName() 
                         << " has a HIGHER yield than " << farmStorage[idx2 - 1]->getName() << ".\n";
                } else {
                    cout << "\nResult: " << farmStorage[idx2 - 1]->getName() 
                         << " has a HIGHER or EQUAL yield compared to " << farmStorage[idx1 - 1]->getName() << ".\n";
                }

            } else if (choice == 5) {
                if (farmStorage.empty()) {
                    cout << "No crops registered for advice.\n";
                    continue;
                }
                cout << "\n--- FARMING ADVISORY ---\n";
                for (const auto &crop : farmStorage) {
                    
                    auto advisory = dynamic_pointer_cast<Advisory>(crop);
                    if (advisory) {
                        advisory->giveAdvice();
                    }
                }
            }
        } catch (const exception &e) {
            cout << "\n[ERROR]: " << e.what() << "\n";
        }

    } while (choice != 6);

    saveCropsToFile(farmStorage, filename);
    cout << "Thank you for using Smart Farm Management System!\n";

    return 0;
}