#ifndef AIRGEAD_BANKING_INVESTMENT_CALCULATOR_H_
#define AIRGEAD_BANKING_INVESTMENT_CALCULATOR_H_

#include <vector>
#include <string>

// Stores the end-of-year results for a report row.
struct YearEndData {
    int year;
    double yearEndBalance;
    double interestEarned;
};

class InvestmentCalculator {
public:
    InvestmentCalculator();

    // Runs the full application loop.
    void run();

private:
    // Member data (m_ prefix used for clarity and consistency).
    double m_initialInvestment;
    double m_monthlyDeposit;
    double m_annualInterestRate;
    int m_numberOfYears;

    // Input and UI helpers.
    void getUserInput();
    void displayInputScreen() const;
    void waitForUser() const;
    double getValidatedDouble(const std::string& t_prompt, double t_minValue) const;
    int getValidatedInt(const std::string& t_prompt, int t_minValue) const;
    void clearInputStream() const;

    // Calculation and reporting helpers.
    std::vector<YearEndData> calculateReport(double t_monthlyDeposit) const;
    void displayReport(const std::vector<YearEndData>& t_report,
                       const std::string& t_title) const;
};

#endif  // AIRGEAD_BANKING_INVESTMENT_CALCULATOR_H_