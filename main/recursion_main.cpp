#include <iostream>
#include <string>
#include <regex>
#include <iomanip>

void clear_screen();

// Obtaining data

double get_loan_amount();
int get_term();
double get_interest_rate();

// Meat & potatoes

double calculate_payment(double &, int &, double &);

// Show output

void show_output(int &, double &, int &, double &, double &);
void report_header(double &, int &, double &);
void column_header();
void details(int &, double &, int &, double &, double &);

// Impl

int main()
{
  double loan_amount = get_loan_amount();
  int term = get_term();
  double interest_rate = get_interest_rate();
  double payment = calculate_payment(loan_amount, term, interest_rate);
  int month_count = 1;

  show_output(month_count, loan_amount, term, interest_rate, payment);
}

// Obtaining data definitions

// gh-todo factor out getter logic

void clear_screen()
{
  static std::string os = std::getenv("OS");

  if (os == "mac" || os == "windows")
  {
    if (os == "mac")
      system("clear");
    else
      system("cls");
  }
}

double get_loan_amount()
{
  bool is_valid_number = false;
  bool is_number = false;

  double result = 0.0;

  std::string input = "";

  while (!is_valid_number)
  {
    clear_screen();

    std::cout << "Enter a loan amount from 1 to 1,000,000: ";
    std::cin >> input;

    is_number = regex_match(input, std::regex("[0-9]+"));
    if (is_number)
    {
      result = std::stod(input);

      if (result > 0 && result < 1000001)
      {
        is_valid_number = true;
      }
      else
        std::cout << "Please enter a loan amount in the correct range";
    }
    else
      std::cout << "Please enter a valid number for the loan amount";
  }

  return result;
}

int get_term()
{
  bool is_valid_number = false;
  bool is_number = false;

  int result = 0;

  std::string input = "";

  while (!is_valid_number)
  {
    system("clear");

    std::cout << "Specify whether the loan is over 5, 10, or 15 years: ";
    std::cin >> input;

    is_number = regex_match(input, std::regex("[0-9]+"));
    if (is_number)
    {
      result = std::stoi(input);

      if (result == 5 || result == 10 || result == 15)
      {
        is_valid_number = true;
      }
      else
        std::cout << "Please enter a valid term: 5, 10, or 15 years" << std::endl;
    }
    else
      std::cout << "Please enter a number for the term" << std::endl;
  }

  return result;
}

double get_interest_rate()
{
  bool is_valid_number = false;
  bool is_number = false;

  double result = 0.0;

  std::string input = "";

  while (!is_valid_number)
  {
    clear_screen();

    std::cout << "Enter an annual interest rate from 1% to 1,000%: ";
    std::cin >> input;

    is_number = regex_match(input, std::regex("[0-9]+"));
    if (is_number)
    {
      result = std::stod(input);

      if (result > 0 && result < 1000001)
      {
        is_valid_number = true;
      }
      else
        std::cout << "Please enter an annual interest rate in the correct range";
    }
    else
      std::cout << "Please enter a valid number for the annual interest rate";
  }

  return result / 100;
}

// Meat & potatoes definitions

double calculate_payment(double &loan_amount, int &term, double &interest_rate)
{
  double annual_rate = interest_rate / 12;
  double annual_term = term * 12;
  double power = pow(1 + annual_rate, annual_term);

  return loan_amount * annual_rate * power / (power - 1);
}

// Show output definitions

void show_output(int &month_count, double &loan_amount, int &term, double &interest_rate, double &payment)
{
  report_header(loan_amount, term, interest_rate);
  column_header();
  details(month_count, loan_amount, term, interest_rate, payment);
}

void report_header(double &loan_amount, int &term, double &interest_rate)
{
  std::cout << "Loan Amount: $" << loan_amount << std::endl
            << std::endl;
  std::cout << "Term: " << term << " Years" << std::endl
            << std::endl;
  std::cout << "Interest Rate: " << interest_rate * 100 << "%" << std::endl
            << std::endl;
}

void column_header()
{
  std::cout << "Month"
            << "\t";
  std::cout << "Payment"
            << "\t";
  std::cout << "Interest"
            << "\t";
  std::cout << "Principal"
            << "\t";
  std::cout << "Balance"
            << "\t";
  std::cout << std::endl
            << std::endl;
}

void details(int &month_count, double &loan_amount, int &term, double &interest_rate, double &payment)
{
  double balance = loan_amount;
  double annual_interest = interest_rate / 12;
  int annual_term = term * 12;

  // for (int month_count = 1; month_count <= annual_term; month_count++)
  {
    double interest = balance * annual_interest;
    double principal = payment - interest;

    balance = balance - principal;

    std::cout << month_count << "\t";
    std::cout << payment << "\t";
    std::cout << interest << "\t";
    std::cout << principal << "\t";
    std::cout << balance << "\t";
    std::cout << std::endl;
  }

  month_count++;

  if (month_count <= annual_term)
    details(month_count, balance, term, interest_rate, payment);

  return;
}
