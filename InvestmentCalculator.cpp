#include "InvestmentCalculator.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;

InvestmentCalculator::InvestmentCalculator()
    : m_initialInvestment(0.0),
      m_monthlyDeposit(0.0),
      m_annualInterestRate(0.0),
      m_numberOfYears(0) {
}

// Runs the program until the user chooses to stop.
void InvestmentCalculator::run() {
    char continueChoice = 'y';

    while (continueChoice == 'y' || continueChoice == 'Y') {
        try {
            getUserInput();
            displayInputScreen();
            waitForUser();

            // Report 1: No additional monthly deposits.
            vector<YearEndData> withoutDepositReport = calculateReport(0.0);

            // Report 2: With monthly deposits entered by the user.
            vector<YearEndData> withDepositReport = calculateReport(m_monthlyDeposit);

            displayReport(withoutDepositReport, "Balance and Interest Without Additional Monthly Deposits");
            displayReport(withDepositReport, "Balance and Interest With Additional Monthly Deposits");

            cout << "\nWould you like to test another scenario? (y/n): ";
            cin >> continueChoice;
            clearInputStream();
        }
        catch (const exception& ex) {
            cout << "\nAn unexpected error occurred: " << ex.what() << endl;
            cout << "The program will return to the main input screen.\n";
        }
    }

    cout << "\nThank you for using the Airgead Banking App.\n";
}

// Collects validated input from the user.
void InvestmentCalculator::getUserInput() {
    cout << "\n============================================================\n";
    cout << "                Airgead Banking Investment App              \n";
    cout << "============================================================\n";

    // Allow 0.00 or greater for money values and interest.
    m_initialInvestment = getValidatedDouble("Initial Investment Amount: $", 0.0);
    m_monthlyDeposit = getValidatedDouble("Monthly Deposit: $", 0.0);
    m_annualInterestRate = getValidatedDouble("Annual Interest (%): ", 0.0);
    m_numberOfYears = getValidatedInt("Number of Years: ", 1);
}

// Displays the current input values before showing the reports.
void InvestmentCalculator::displayInputScreen() const {
    cout << "\n============================================================\n";
    cout << "                         Data Input                         \n";
    cout << "============================================================\n";
    cout << left << setw(30) << "Initial Investment Amount:" << "$"
         << fixed << setprecision(2) << m_initialInvestment << endl;
    cout << left << setw(30) << "Monthly Deposit:" << "$"
         << fixed << setprecision(2) << m_monthlyDeposit << endl;
    cout << left << setw(30) << "Annual Interest:" 
         << fixed << setprecision(2) << m_annualInterestRate << "%" << endl;
    cout << left << setw(30) << "Number of Years:" << m_numberOfYears << endl;
    cout << "============================================================\n";
}

// Pauses until the user presses Enter.
void InvestmentCalculator::waitForUser() const {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads and validates a non-negative double value.
double InvestmentCalculator::getValidatedDouble(const string& t_prompt, double t_minValue) const {
    double value = 0.0;

    while (true) {
        cout << t_prompt;
        cin >> value;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a numeric value.\n";
            clearInputStream();
        }
        else if (value < t_minValue) {
            cout << "Invalid input. Please enter a value of "
                 << fixed << setprecision(2) << t_minValue << " or greater.\n";
            clearInputStream();
        }
        else {
            clearInputStream();
            return value;
        }
    }
}

// Reads and validates an integer value greater than or equal to t_minValue.
int InvestmentCalculator::getValidatedInt(const string& t_prompt, int t_minValue) const {
    int value = 0;

    while (true) {
        cout << t_prompt;
        cin >> value;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a whole number.\n";
            clearInputStream();
        }
        else if (value < t_minValue) {
            cout << "Invalid input. Please enter a value of "
                 << t_minValue << " or greater.\n";
            clearInputStream();
        }
        else {
            clearInputStream();
            return value;
        }
    }
}

// Clears any remaining input from the stream.
void InvestmentCalculator::clearInputStream() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Calculates the yearly report using monthly compounding.
//
// Formula used each month:
// interest = (openingBalance + monthlyDeposit) * ((annualInterestRate / 100) / 12)
// closingBalance = openingBalance + monthlyDeposit + interest
vector<YearEndData> InvestmentCalculator::calculateReport(double t_monthlyDeposit) const {
    vector<YearEndData> report;
    double currentBalance = m_initialInvestment;
    double monthlyRate = (m_annualInterestRate / 100.0) / 12.0;

    for (int year = 1; year <= m_numberOfYears; ++year) {
        double yearlyInterest = 0.0;

        for (int month = 1; month <= 12; ++month) {
            currentBalance += t_monthlyDeposit;

            double monthlyInterest = currentBalance * monthlyRate;
            currentBalance += monthlyInterest;
            yearlyInterest += monthlyInterest;
        }

        YearEndData row;
        row.year = year;
        row.yearEndBalance = currentBalance;
        row.interestEarned = yearlyInterest;

        report.push_back(row);
    }

    return report;
}

// Displays one report table.
void InvestmentCalculator::displayReport(const vector<YearEndData>& t_report,
                                         const string& t_title) const {
    cout << "\n";
    cout << t_title << endl;
    cout << "=====================================================================\n";
    cout << left << setw(10) << "Year"
         << right << setw(25) << "Year End Balance"
         << setw(25) << "Interest Earned" << endl;
    cout << "---------------------------------------------------------------------\n";

    for (const YearEndData& row : t_report) {
        cout << left << setw(10) << row.year
             << right << "$" << setw(24) << fixed << setprecision(2) << row.yearEndBalance
             << "$" << setw(24) << fixed << setprecision(2) << row.interestEarned
             << endl;
    }

    cout << "=====================================================================\n";
}